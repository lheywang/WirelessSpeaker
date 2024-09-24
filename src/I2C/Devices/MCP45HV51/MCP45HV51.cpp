// ==============================================================================
//                              I2C/Devices/MCP9808/MCP9808.cpp
//                              Wrote by lheywang
//
// Define functions to interface with the IC
// ==============================================================================

// Header file
#include "MCP45HV51.hpp"

// Cpp modules
#include <cstdint>

// =====================
// CONSTRUCTORS
// =====================

MCP45HV51::MCP45HV51(int address)
{
    this->address = (uint8_t)address;
    return;
}

// =====================
// DESTRUCTORS
// =====================

MCP45HV51::~MCP45HV51()
{
    return;
}
