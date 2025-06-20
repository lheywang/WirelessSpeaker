/**
 * @file DS1882.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source of the DS1882 functions
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

// Header file
#include "drivers/devices/DS1882.hpp"

// Drivers
#include "drivers/peripherals/i2c.hpp"

// STD
#include <cstdint>
#include <stdio.h>

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================
constexpr int CONFIG = 0x80;

// =====================
// CONSTRUCTORS
// =====================

DS1882::DS1882(const I2C_Bus* I2C, const LOG_POTI address)
{
    this->address = (uint8_t)address;
    this->I2C = *I2C;
    this->b_PotiConfig = false;
    return;
}

// =====================
// DESTRUCTORS
// =====================

DS1882::~DS1882()
{
    return;
}

// =====================
// FUNCTIONS
// =====================
int DS1882::WriteWiper(const LOG_WIPER wiper, const int value)
{
    if(value > (this->b_PotiConfig ? 0x3F : 0x1F))
        return -2;

    // Cast and AND the last to bits to write the wiper settings.
    uint8_t Register = (uint8_t)value;
    Register &= 0x3F;
    Register |= (int)wiper;

    int buf = 0;
    int res = I2C_Write(&this->I2C, this->address, Register, &buf, 0);

    if(res != 0)
        return -3;

    return 0;
}

int DS1882::ReadWipers(LOG_WIPER* const wiper0, LOG_WIPER* const wiper1)
{
    // init a memory buffer
    int buf[3] = {0};

    // perform the read operation.
    int res = I2C_Read(&this->I2C, this->address, 0x00, buf, 0x03);

    // copy the data and output it correctly.
    *wiper0 = LOG_WIPER{buf[0]};
    *wiper1 = LOG_WIPER{buf[1]};

    if(res < 0)
        return -1;

    return 0;
}

int DS1882::ConfigurePoti(const int Volatile, const int ZeroCrossing, const int PotiConfig)
{
    // Store this setting onto the class.
    this->b_PotiConfig = !(bool)PotiConfig; // Command is inverted here.

    // Second, compute the command value:
    uint8_t TempRegister = 0;

    // Shift the rights settings
    TempRegister |= (bool)Volatile;
    TempRegister = (TempRegister << 1) | (bool)ZeroCrossing;
    TempRegister = (TempRegister << 1) | this->b_PotiConfig;

    // Write the correct Config selection bits
    TempRegister |= 0x80;

    int buf = 0;
    int res = I2C_Write(&this->I2C, this->address, TempRegister, &buf, 0);

    if(res < 0)
        return -1;

    return 0;
}