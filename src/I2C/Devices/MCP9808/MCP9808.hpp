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

class MCP9808
{
private:
    uint8_t address;

public:
    // Constructor
    MCP9808(int address);

    // Destructor
    ~MCP9808();
};