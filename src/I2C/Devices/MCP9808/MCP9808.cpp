/**
 * @file MCP9808.cpp
 * @author l.heywang
 *
 */

// Header file
#include "MCP9808.hpp"

// Cpp modules
#include <cstdint>

// =====================
// CONSTRUCTORS
// =====================

MCP9808::MCP9808(int address)
{
    this->address = (uint8_t)address;
    return;
}

// =====================
// DESTRUCTORS
// =====================

MCP9808::~MCP9808()
{
    return;
}

// =====================
// FUNCTIONS
// =====================
