/**
 * @file    lcxp.cpp
 * @author  lheywang (leonard.heywang@proton.me)
 * @brief   Base implementation of the LCxP parser class. Could not really be used standalone.
 * @version 0.1
 * @date    2026-02-10
 *
 * @copyright Copyright (c) 2026
 *
 */

/* *******************************************************************
 * INCLUDE
 * *******************************************************************/
// Header
#include "lcxp.h"

// STD
#include <iostream>
#include <cstdint>
#include <cstdlib>
#include <cstring>

/* *******************************************************************
 * CONSTRUCTORS AND DESTRUCTORS
 * *******************************************************************/
lcxp::LCxP::LCxP()
{
    // Clear the buffers
    this->clear_buffers();

    // Clear any callbacks structs that may exist.
    this->registeredCallbacks = 0;
    memset((void *)callbacks_structs, 0x00, (size_t)sizeof(callbacks_structs));

    return;
}

lcxp::LCxP::LCxP(uint8_t buffer[MAX_BUFFER_SIZE], uint32_t size)
{
    // Clear the buffers and full it with the passed number of bytes.
    this->clear_buffers();
    this->add_Nbyte(buffer, size);

    // Clear any callbacks structs that may exist.
    this->registeredCallbacks = 0;
    memset((void *)callbacks_structs, 0x00, (size_t)sizeof(callbacks_structs));

    // Append the registered commands :
    this->register_command(opcodes::SYS_ACK, &LCxP::sys_ack);

    return;
}

lcxp::LCxP::~LCxP()
{
    // No dynamic memory to clear.
    return;
}

/* *******************************************************************
 * FUNCTIONS
 * *******************************************************************/
uint32_t lcxp::LCxP::remove_command(uint8_t opcode)
{
    /*
     * Check if the opcode is known
     */
    uint8_t pos = 0xFF;
    for (int i = 0; i < MAX_PARSER_CALLBACKS; i++)
    {
        if (this->callbacks_structs[i].opcode == opcode)
            pos = i;
    }

    if (pos == 0xFF)
        return 1;

    // Clear the associated data
    this->callbacks_structs[pos].parser = nullptr;
    this->callbacks_structs[pos].opcode = 0x00;

    // Decrement the registerd counter
    this->registeredCallbacks -= 1;

    return 0;
}

uint32_t lcxp::LCxP::clear_buffers()
{
    // Clear the previously parsed data
    memset((void *)&this->result, 0x00, (size_t)sizeof(this->result));

    // Clear the buffer with a default value to 0xFF.
    memset((void *)this->buffer, 0xFF, (size_t)MAX_BUFFER_SIZE);
    this->buffer_size = 0;
    return 0;
}

uint32_t lcxp::LCxP::add_byte(uint8_t byte)
{
    if (this->buffer_size >= MAX_BUFFER_SIZE) // Will error once we've written the MAX_BUFFER_SIZE - 1 byte.
        return 1;

    // Copy the data and increment the pointer
    this->buffer[this->buffer_size] = byte;
    this->buffer_size += 1;

    return 0;
}

uint32_t lcxp::LCxP::add_Nbyte(uint8_t *byte, uint8_t number)
{
    // Recursively add bytes, one by one.
    if (this->buffer_size >= (MAX_BUFFER_SIZE - number))
        return 1;

    // This enable a faster loop, may be usefull on smallest MCUs.
    memcpy((void *)&this->buffer[this->buffer_size], (void *)byte, (size_t)number);
    return 0;
}

uint32_t lcxp::LCxP::parse()
{
    /*
     * First, split the buffer into their respective positions :
     */
    if (this->buffer[0] != 0x55)
        return 1;

    this->result.dev_id = this->buffer[1];
    this->result.seq_id = this->buffer[2];
    this->result.cmd = this->buffer[3];
    this->result.len = this->buffer[4];
    memcpy((void *)this->result.payload, (void *)&this->buffer[5], (size_t)this->result.len);
    this->result.checksum = this->buffer[5 + this->result.len + 1];

    /*
     * Then, check the message checksum :
     */
    uint8_t chksm = this->get_checksum();

    if (chksm != this->result.checksum)
        return 2;

    /*
     * Finally, call the associated parser for the data message :
     */
    // search for the designated opcode :
    for (int k = MAX_PARSER_CALLBACKS; k > 0; k--)
    {
        if ((this->callbacks_structs[k].opcode == this->result.cmd) &&
            (this->callbacks_structs[k].parser != nullptr))
        {
            // Call the associated function
            (this->*callbacks_structs[k].parser)(&this->result);
            break;
        }
    }

    return 0;
}

uint8_t *lcxp::LCxP::build()
{
    // First, clean the buffers
    memset((void *)this->buffer, 0x00, (size_t)MAX_BUFFER_SIZE);
    this->buffer_size = 0;

    // Then, rebuild it from scratch, using the latest elements :
    // This is valid since bytes are continous into the source struct -> we can copy the bare 4 bytes.
    this->add_byte(0x55);
    this->add_Nbyte(&this->result.dev_id, 4);

    // Add the final value
    this->add_Nbyte(this->result.payload, this->result.len);

    // Append the checksum
    this->add_byte(this->get_checksum());

    // Finally, clear the buffers :
    memset((void *)&this->result, 0x00, (size_t)sizeof(this->result));

    // Return a pointer to the buffer
    return this->buffer;
}

uint8_t lcxp::LCxP::get_checksum()
{
    /*
     * First, perform the sum of the payload.
     * Since 255 * 255 = 16 025, we can use a 16 bit variable here.
     */
    uint16_t sum = 0;
    for (uint8_t k = this->result.len; k > 0; k--)
        sum += this->result.payload[k];

    // Compute the checksum with the described function.
    return (((this->result.dev_id ^ this->result.seq_id) ^ this->result.cmd) ^ this->result.len) ^ (sum & 0xFF);
}

uint32_t lcxp::LCxP::send()
{
    std::cout << "Sending buffer : 0x" << std::hex << this->buffer << std::endl;
    return 0;
}

/*
 *  We've received theses commands. How are we handling it ?
 *  Theses functions provide only a basic way of handling them, and an overide if perhaps needed.
 */
uint32_t lcxp::LCxP::sys_ping(struct parser_result *arg)
{
    // Cast to nothing the arg, just because we don't use it.
    (void)(arg);

    // In case of ping, we just send back the same message.
    // We don't even need to build it.
    this->send();
    return 0;
}

uint32_t lcxp::LCxP::sys_ack(struct parser_result *arg)
{
    // Cast to nothing the arg, just because we don't use it.
    (void)(arg);

    // We've received an acknowledge, which is automatic. We don't answer that much here...
    return 0;
}

uint32_t lcxp::LCxP::sys_nack(struct parser_result *arg)
{
    // Cast to nothing the arg, just because we don't use it.
    (void)(arg);

    // We've received an error here. How to handle that ? That's to the child class to do it...
    return 0;
}

uint32_t lcxp::LCxP::sys_reset(struct parser_result *arg)
{
    // Cast to nothing the arg, just because we don't use it.
    (void)(arg);

    // Nothing to be done on the base class. That's to the child class to do it...
    return 0;
}

uint32_t lcxp::LCxP::sys_ready(struct parser_result *arg)
{
    // Cast to nothing the arg, just because we don't use it.
    (void)(arg);

    // Nothing to be done on the base class. That's to the child class to do it...
    return 0;
}

uint32_t lcxp::LCxP::sys_info_get(struct parser_result *arg)
{
    // Cast to nothing the arg, just because we don't use it.
    (void)(arg);

    // Since the sender want us to know the hardware details, return it :
    memcpy((void *)this->result.payload, (void *)&this->hwid, (size_t)sizeof(this->hwid));
    this->result.cmd = lcxp::opcodes::SYS_INFO_RET;
    this->result.checksum = this->get_checksum();

    // Build the buffer before returning.
    // This enable us to get the response without ever calling a thing manually...
    this->build();
    this->send();
    return 0;
}

uint32_t lcxp::LCxP::sys_info_ret(struct parser_result *arg)
{
    // Cast to nothing the arg, just because we don't use it.
    (void)(arg);

    // Nothing to be done on the base class. That's to the child class to do it...
    return 0;
}

uint32_t lcxp::LCxP::sys_uuid_get(struct parser_result *arg)
{
    // Cast to nothing the arg, just because we don't use it.
    (void)(arg);

    // Since the sender want us to know the hardware details, return it :
    memcpy((void *)this->result.payload, (void *)&this->uuid, (size_t)sizeof(this->uuid));
    this->result.cmd = lcxp::opcodes::SYS_INFO_RET;
    this->result.checksum = this->get_checksum();

    // Build the buffer before returning.
    // This enable us to get the response without ever calling a thing manually...
    this->build();
    this->send();
    return 0;
}

uint32_t lcxp::LCxP::sys_uuid_ret(struct parser_result *arg)
{
    // Cast to nothing the arg, just because we don't use it.
    (void)(arg);

    // Nothing to be done on the base class. That's to the child class to do it...
    return 0;
}

uint64_t lcxp::LCxP::get_uuid()
{
    return this->uuid;
}
uint64_t lcxp::LCxP::get_hwid()
{
    return this->hwid;
}
uint32_t lcxp::LCxP::set_uuid(uint64_t uuid)
{
    this->uuid = uuid;
    return 0;
}
uint32_t lcxp::LCxP::set_hwid(uint64_t hwid)
{
    this->hwid = hwid;
    return 0;
}
