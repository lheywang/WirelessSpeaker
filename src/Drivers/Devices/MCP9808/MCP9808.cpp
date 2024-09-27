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

// ==============================================================================
// MACROS
// ==============================================================================
// Define the way of passing commands to this IC
#define REGISTER(x) (x & 0x0F)

// =====================
// CONSTRUCTORS
// =====================

MCP9808::MCP9808(const I2C_Bus *I2C, const int address)
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
static void FloatToInts(const float Input, int *const OutputBuf)
{
    bool Sign = false;
    if (Input < 0)
        Sign = true; // We set to 1 the sign bit, since data is expressed as CPL2.

    int IntegerPart = (int)floor(Input);
    int FloatPart = (int)round((Input - (float)IntegerPart) / 0.0625);

    OutputBuf[0] = 0;
    OutputBuf[1] = 0;
    OutputBuf[0] = (((int)Sign * -1) << 4) | ((IntegerPart & 0xF0) >> 4);
    OutputBuf[1] = ((IntegerPart & 0x0F) << 4) | ((FloatPart & 0x0F));

    return;
}

// =====================
// FUNCTIONS
// =====================

int MCP9808::ConfigureResolution(const int Resolution)
{
    if ((Resolution > C0_0625) & (Resolution < C0_5))
        return -1;

    int TResolution = Resolution;
    int res = I2C_Write(&this->I2C, this->address, REGISTER(TEMP_RESOLUTION), &TResolution);

    if (res != 0)
        return -2;

    return 0;
}

int MCP9808::Configure(const int Hysteresis,
                       const int Mode,
                       const int Lock,
                       const int ClearInterrupt,
                       const int AlertStatus,
                       const int AlertControl,
                       const int AlertSelection,
                       const int AlertPolarity,
                       const int AlertMode)
{
    if ((Hysteresis > HYST_6) & (Hysteresis < HYST_0))
        return -1;

    int buf[2] = {0};

    // MSB
    buf[0] = Hysteresis;
    buf[0] = (buf[0] << 1) | (bool)Mode;

    // LSB
    buf[1] = (bool)Lock;
    buf[1] = (buf[1] << 1) | (bool)Lock;
    buf[1] = (buf[1] << 1) | (bool)ClearInterrupt;
    buf[1] = (buf[1] << 1) | (bool)AlertStatus;
    buf[1] = (buf[1] << 1) | (bool)AlertControl;
    buf[1] = (buf[1] << 1) | (bool)AlertSelection;
    buf[1] = (buf[1] << 1) | (bool)AlertPolarity;
    buf[1] = (buf[1] << 1) | (bool)AlertMode;

    int res = 0;
    res = I2C_Write(&this->I2C, this->address, REGISTER(MCP9808_CONFIG), buf, 2);

    if (res != 0)
        return -2;

    return 0;
}

int MCP9808::GetIDs(int *const DeviceID, int *const DeviceRevision, int *const ManufacturerID)
{
    int res = 0;
    int buf[2] = {0};
    res += I2C_Read(&this->I2C, this->address, REGISTER(DEVICEID), buf, 2);

    *DeviceID = buf[0];
    *DeviceRevision = buf[1];

    res += I2C_Read(&this->I2C, this->address, REGISTER(MANUFACTURER), buf, 2);
    *ManufacturerID = (buf[0] << 8) | buf[1];

    if (res != 0)
        return -1;

    return 0;
}

int MCP9808::SetAlertTemperatures(const float Minimal, const float Maximal, const float Critical)
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

int MCP9808::ReadTemperature(float *const Temperature, int *const Status)
{
    int buf[2] = {0};
    int res = I2C_Read(&this->I2C, this->address, REGISTER(READ_TEMP), buf, 2);

    if (res != 0)
        return -1;

    // Fetching in temp variables the correct values.
    *Status = (buf[0] & 0xE0) >> 5;
    bool Sign = (bool)(buf[0] & 0x10);
    uint8_t IntTemp = (uint8_t)((buf[1] >> 4) | (buf[0]) << 4);
    uint8_t FloatTemp = (uint8_t)(buf[1] & 0x0F);

    // Computing the temperature.
    *Temperature = (float)((Sign * (-1)) + IntTemp + (FloatTemp * 0.0625));
    return 0;
}