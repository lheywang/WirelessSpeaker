/**
 * @file PCA9633.cpp
 * @author l.heywang
 *
 */

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
