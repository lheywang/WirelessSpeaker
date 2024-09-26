/**
 * @file PCA9633.cpp
 * @author l.heywang
 * @brief Source of the functions for the PCA9633 Leds Drivers
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
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
