/**
 * @file MCP9808.cpp
 * @author l.heywang
 * @brief Source of the functions for the MCP9808 Temperature Sensor.
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
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
