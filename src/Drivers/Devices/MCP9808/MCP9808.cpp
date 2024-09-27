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
#include <math.h>
#include "../../I2C/I2C.hpp"

// =====================
// CONSTRUCTORS
// =====================

MCP9808::MCP9808(I2C_Bus *I2C, int address)
{
    this->address = (uint8_t)address;
    this->I2C = *I2C;
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
// STATIC FUNCTIONS
// =====================

// This function is private, thus we assume OutputBuf is a list of 2 elements of 8 bits
inline static void FloatToInts(float Input, int *OutputBuf)
{
    bool Sign = false;
    if (Input < 0)
        Sign = true; // We set to 1 the sign bit, since data is expressed as CPL2.

    int IntegerPart = (int)round(Input);
    int FloatPart = (int)round((Input - (float)IntegerPart) * 256);

    OutputBuf[0] = 0;
    OutputBuf[1] = 0;
    OutputBuf[0] = (((int)Sign * -1) << 4) | ((IntegerPart & 0xF0) >> 4);
    OutputBuf[1] = ((IntegerPart & 0x0F) << 4) | ((FloatPart & 0x0F));

    return;
}

// =====================
// FUNCTIONS
// =====================

int MCP9808::ConfigureResolution(int Resolution)
{
}

int MCP9808::ConfigureThermometer(int Hysteresis, int Mode, int Lock, int ClearInterrupt, int AlertStatus, int AlterControl, int AlterSelection, int AlterPolarity, int AltertMode)
{
}

int MCP9808::GetIDs(int *DeviceID, int *DeviceRevision, int *ManufacturerID)
{
}

int MCP9808::SetAlertTemperatures(float Minimal, float Maximal, float Critical)
{
    if ((Minimal < -128) | (Minimal > 128))
        return -1;
    if ((Maximal < -128) | (Maximal > 128))
        return -2;
    if ((Critical < -128) | (Critical > 128))
        return -3;

    int BufMin[2] = {0};
    int BufMax[2] = {0};
    int BufCrit[2] = {0};

    FloatToInts(Minimal, BufMin);
    FloatToInts(Maximal, BufMax);
    FloatToInts(Critical, BufCrit);

    int res = 0;
    res += I2C_Write(&this->I2C, this->address, REGISTER(LOWER_TEMP), BufMin, 2);
    res += I2C_Write(&this->I2C, this->address, REGISTER(UPPER_TEMP), BufMax, 2);
    res += I2C_Write(&this->I2C, this->address, REGISTER(CRIT_TEMP), BufCrit, 2);

    if (res != 0)
        return -4;
    return 0;
}

int MCP9808::ReadTemperature(float *Temperature, int *Status)
{
    if (&Temperature == NULL)
        return -1;
    if (&Status == NULL)
        return -2;

    int buf[2] = {0};
    int res = I2C_Read(&this->I2C, this->address, REGISTER(READ_TEMP), buf, 2);

    if (res < 0)
        return -3;

    // Fetching in temp variables the correct values.
    *Status = (buf[0] & 0xE0) >> 5;
    bool Sign = (bool)((buf[0] & 0x10) >> 4);
    uint8_t IntTemp = (uint8_t)((buf[1] >> 4) | (buf[0]) << 4);
    uint8_t FloatTemp = (uint8_t)(buf[1] & 0x0F);

    // Computing the temperature.
    *Temperature = INT_TO_FLOAT(Sign, IntTemp, FloatTemp);
    return 0;
}

// Integer conversion :
/*
 * bit 16:14 : Status (opt)
 * bit 15 : Sign
 * bit 14: 2^7
 * bit 13: 2^6
 * ...
 * bit 5 : 2^0
 * bit 4 : 2^-1
 * ...
 * bit 1 : 2^-4
 *
 *
 * bit 15 * (-1) + Integer + Float * 0.0625
 */