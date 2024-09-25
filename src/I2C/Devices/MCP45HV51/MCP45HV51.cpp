/**
 * @file MCP45HV51.cpp
 * @author l.heywang
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
