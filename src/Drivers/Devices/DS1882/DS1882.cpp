/**
 * @file DS1882.cpp
 * @author l.heywang
 * @brief Source of the DS1882 functions
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

// Header file
#include "DS1882.hpp"

// Cpp modules
#include <cstdint>
#include <stdio.h>
#include "../../I2C/I2C.hpp"

// =====================
// CONSTRUCTORS
// =====================

DS1882::DS1882(I2C_Bus *I2C, int address)
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
int DS1882::WriteWiper(int wiper, int value)
{
    if ((wiper != WIPER_0) && (wiper != WIPER_1))
        return -1;

    if (value > 0x3F)
        return -2;

    // Cast and AND the last to bits to write the wiper settings.
    uint8_t Register = (uint8_t)value;
    Register &= 0x3F;
    Register |= wiper;

    int buf = 0;
    int res = I2C_Write(&this->I2C, this->address, Register, &buf, 0);

    if (res != 0)
        return -3;

    return 0;
}

int DS1882::ReadWipers(int *wiper0, int *wiper1)
{
    // init a memory buffer
    int buf[3] = {0};

    // perform the read operation.
    // This need to be tested, since a command byte (0x00) is sent, I don't know of the DS1882 will accept it !
    int res = I2C_Read(&this->I2C, this->address, 0x00, buf, 0x03);

    // copy the data and output it correctly.
    *wiper0 = buf[0];
    *wiper1 = buf[1];

    if (res < 0)
        return -1;

    return 0;
}

int DS1882::ConfigurePoti(int Volatile, int ZeroCrossing, int PotiConfig)
{
    // First, cast to 0 or 1 the values.
    bool b_Volatile = (bool)Volatile;
    bool b_ZeroCrossing = (bool)ZeroCrossing;
    this->b_PotiConfig = !(bool)PotiConfig; // Command is inverted here.

    // Second, compute the command value:
    uint8_t TempRegister = 0;

    // Shift the rights settings
    TempRegister |= b_Volatile;
    TempRegister = (TempRegister << 1) | b_ZeroCrossing;
    TempRegister = (TempRegister << 1) | this->b_PotiConfig;

    // Write the correct Config selection bits
    TempRegister |= 0x80;

    int buf = 0;
    int res = I2C_Write(&this->I2C, this->address, TempRegister, &buf, 0);

    if (res < 0)
        return -1;

    return 0;
}