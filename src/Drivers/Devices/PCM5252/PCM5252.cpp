/**
 * @file PCM5252.cpp
 * @author l.heywang
 * @brief Source of basic functions for the PCM5252 Audio DAC.
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

// Header file
#include "PCM5252.hpp"

// Cpp modules
#include <cstdint>
#include "../../I2C/I2C.hpp"

// =====================
// CONSTRUCTORS
// =====================

PCM5252::PCM5252(const I2C_Bus *I2C, const int address)
{
    this->address = (uint8_t)address;
    this->I2C = *I2C;
    return;
}

// =====================
// DESTRUCTORS
// =====================

PCM5252::~PCM5252()
{
    return;
}