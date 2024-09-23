// ==============================================================================
//                              I2C/Devices/MCP45HV51/MCP45HV51.hpp
//                              Wrote by lheywang
//
// Define our basic I2C settings on the boards, such as :
// - Register Addresses
// ==============================================================================

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

class MCP45HV51
{
private:
    uint8_t address = 0x00;

public:
    // Constructors
    MCP45HV51(int address);

    // Destructors
    ~MCP45HV51();
};