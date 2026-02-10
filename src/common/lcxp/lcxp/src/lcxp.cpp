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

/* *******************************************************************
 * CONSTRUCTORS AND DESTRUCTORS
 * *******************************************************************/
lcxp::LCxP::LCxP() 
{

}

lcxp::LCxP::LCxP(uint8_t buffer[MAX_BUFFER_SIZE], uint32_t size) 
{

}

lcxp::LCxP::~LCxP() 
{

}

/* *******************************************************************
 * FUNCTIONS
 * *******************************************************************/
uint32_t lcxp::LCxP::register_command(uint8_t opcode, uint32_t (*parser)(struct LCxP_parser_struct *arg)) 
{

}

uint32_t lcxp::LCxP::remove_command(uint8_t opcode)
{

}

uint32_t lcxp::LCxP::clear_buffers()
{

}

uint32_t lcxp::LCxP::add_byte(uint8_t byte)
{

}

uint32_t lcxp::LCxP::add_Nbyte(uint8_t *byte, uint8_t number)
{

}

uint32_t lcxp::LCxP::parse_buffer()
{

}

/* *******************************************************************
 * PRIVATE FUNCTIONS
 * *******************************************************************/
uint8_t lcxp::LCxP::get_checksum(uint8_t dev_id, uint8_t seq_id, uint8_t cmd, uint8_t len, uint8_t *payload)
{
    /*
     * First, perform the sum of the payload.
     * Since 255 * 255 = 16 025, we can use a 16 bit variable here.
    */
    uint16_t sum = 0;
    for (uint8_t k = len; k > 0; k--)
        sum += payload[k];

    // Compute the checksum with the described function.
    return dev_id ^ seq_id ^ cmd ^ len ^ (sum & 0xFF);
}

