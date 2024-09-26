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
