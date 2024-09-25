/**
 * @file PCM5252.cpp
 * @author l.heywang
 *
 */

// Header file
#include "PCM5252.hpp"

// Cpp modules
#include <cstdint>

// =====================
// CONSTRUCTORS
// =====================

PCM5252::PCM5252(int address)
{
    this->address = (uint8_t)address;
    return;
}

// =====================
// DESTRUCTORS
// =====================

PCM5252::~PCM5252()
{
    return;
}