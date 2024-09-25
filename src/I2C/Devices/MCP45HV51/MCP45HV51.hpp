/**
 * @file MCP45HV51.cpp
 * @brief Define basic functions for the MCP45HV51 Linear Digital Potentiometer.
 * @author l.heywang
 *
 */

// prevent multiple include
#pragma once

// type include
#include <cstdint>

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