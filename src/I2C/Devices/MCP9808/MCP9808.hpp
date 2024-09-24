// ==============================================================================
//                              I2C/Devices/MCP9808/MCP9808.hpp
//                              Wrote by lheywang
//
// Define functions to interface with the IC
// ==============================================================================

// prevent multiple include
#pragma once

// type include
#include <cstdint>

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

#define MCP9808_DATA_SIZE 16 // 16b register here
#define MCP9808_CONFIG 0x01
#define UPPER_TEMP 0x02
#define LOWER_TEMP 0x03
#define CRIT_TEMP 0x04
#define READ_TEMP 0x05
#define MANUFACTURER 0x06

// ==============================================================================
// IC CLASS FUNCTIONS
// ==============================================================================

/**
 * @brief Base class of the MCP808 Temp sensor. Contain functions to execute actions on it.
 *
 */
class MCP9808
{
private:
    uint8_t address;

public:
    /**
     * @brief Construct a new MCP9808 object
     *
     * @param[in] address The address of the IC on the I2C Bus.
     */
    MCP9808(int address);

    /**
     * @brief Destroy the MCP9808 object
     *
     */
    ~MCP9808();
};