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
uint32_t lcxp::LCxP::register_command(uint8_t opcode, uint32_t (*parser)(struct parser_result *arg)) 
{
    // Exit rapidly if none are available.
    if (this->registeredCallbacks >= MAX_PARSER_CALLBACKS)
        return 1;

    /*
     * First, seek for the first available structure. There's one since there's at least one slot available.
     */
    uint8_t pos = 0;
    for (int i = 0; i < MAX_PARSER_CALLBACKS; i++)
    {
        if (this->callbacks_structs[i].parser == nullptr)
        {
            pos = i;
            break;
        }
    }

    /*
     * Check if the opcode isn't already registered
     */
    for (int i = 0; i < MAX_PARSER_CALLBACKS; i++)
    {
        if (this->callbacks_structs[i].opcode == opcode)
            return 2;
    }

    /*
     * Fill the structure and return
     */
    this->callbacks_structs[pos].opcode = opcode;
    this->callbacks_structs[pos].parser = parser;

    // Increment the registered counter by one.
    this->registeredCallbacks += 1;
    return 0;
}

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
    this->result.payload = &this->buffer[5];
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
    for (int k = MAX_PARSER_CALLBACKS; k > 0 ; k--)
    {
        if (this->callbacks_structs[k].opcode == this->result.cmd)
        {
            // Call the associated function
            this->callbacks_structs[k].parser(&this->result);
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

/* *******************************************************************
 * PRIVATE FUNCTIONS
 * *******************************************************************/
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
    return (((this->result.dev_id ^ this->result.seq_id) ^ this->result.cmd) ^this->result. len) ^ (sum & 0xFF);
}

