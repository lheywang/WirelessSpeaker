// ==============================================================================
//                              I2C/Devices/MCP9808/MCP9808.cpp
//                              Wrote by lheywang
//
// Define functions to interface with the IC
// ==============================================================================

// Header file
#include "PCA9633.hpp"

// Cpp modules
#include <cstdint>

// =====================
// CONSTRUCTORS
// =====================

PCA9633::PCA9633(int address)
{
    this->address = (uint8_t)address;
    return;
}

// =====================
// DESTRUCTORS
// =====================

PCA9633::~PCA9633()
{
    return;
}

// =====================
// FUNCTIONS
// =====================
