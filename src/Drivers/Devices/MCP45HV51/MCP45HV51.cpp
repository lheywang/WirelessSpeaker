/**
 * @file MCP45HV51.cpp
 * @author l.heywang
 * @brief Source of the functions of the MCP45HV51.
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */
// Header file
#include "MCP45HV51.hpp"

// Cpp modules
#include <cstdint>
#include "../../I2C/I2C.hpp"

// =====================
// CONSTRUCTORS
// =====================

MCP45HV51::MCP45HV51(const I2C_Bus *I2C, const int address)
{
    this->address = (uint8_t)address;
    this->I2C = *I2C;
    return;
}

// =====================
// DESTRUCTORS
// =====================

MCP45HV51::~MCP45HV51()
{
    return;
}
