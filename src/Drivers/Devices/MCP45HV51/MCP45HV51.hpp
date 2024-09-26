/**
 * @file MCP45HV51.hpp
 * @author l.heywang
 * @brief Define a class and functions for the MCP45HV51 linear digital potentiometer.
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */
// prevent multiple include
#pragma once

// type include
#include <cstdint>
#include "../../I2C/I2C.hpp"

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

#define MCP45HV51_DATA_SIZE 8 // 8b register here

// Registers
#define TCON0 0x04
#define WIPER_0 0x00

#define WRITE_DATA 0x00
#define INCREMENT 0x01
#define DECREMENT 0x02
#define READ_DATA 0x03

// ==============================================================================
// IC CLASS FUNCTIONS
// ==============================================================================

/**
 * @brief Base class to exploit the functionnality of this linear potentiometer.
 *
 */
class MCP45HV51
{
private:
    uint8_t address = 0x00;

public:
    /**
     * @brief Construct a new MCP45HV51 object
     *
     * @param[in] address (int) : The address of the IC on the I2C bus.
     */
    MCP45HV51(int address);

    /**
     * @brief Destroy the MCP45HV51 object
     *
     */
    ~MCP45HV51();
};