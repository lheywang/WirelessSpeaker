/**
 * @file MCP9808.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source of the functions for the MCP9808 Temperature Sensor.
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 * @remark Class was tested successfully on 01/10/2024.
 *
 */

// Header file
#include "MCP9808.hpp"

// Cpp modules
#include <cstdint>
#include <math.h>
#include "../../I2C/I2C.hpp"

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

// Register
constexpr int MCP9808_CONFIG = 0x01;
constexpr int UPPER_TEMP = 0x02;
constexpr int LOWER_TEMP = 0x03;
constexpr int CRIT_TEMP = 0x04;
constexpr int READ_TEMP = 0x05;
constexpr int MANUFACTURER = 0x06;
constexpr int DEVICEID = 0x07;
constexpr int TEMP_RESOLUTION_REG = 0x08;

// ==============================================================================
// MACROS
// ==============================================================================
// Define the way of passing commands to this IC
constexpr int REGISTER(int x) { return (x & 0x0F); }

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

static void FloatToInts(const float Input, int *const OutputBuf)
{
    int Sign = 0;
    if (Input < 0)
        Sign = 1; // We set to 1 the sign bit, since data is expressed as CPL2.

    // Compute the differents factors (rounding, then the float part)
    int IntegerPart = round(Input);
    int FloatPart = round((Input - IntegerPart) / 0.0625);
    IntegerPart &= 0xFF;

    *OutputBuf = 0;
    *OutputBuf = (Sign << 12) | (IntegerPart << 4) | (FloatPart & 0x0F);

    return;
}

// =====================
// FUNCTIONS
// =====================

int MCP9808::ConfigureResolution(const TEMP_RESOLUTION Resolution)
{
    int TResolution = SWAP_BYTES((int)Resolution);
    int res = I2C_Write(&this->I2C, this->address, REGISTER(TEMP_RESOLUTION_REG), &TResolution, 1, 1);

    if (res != 0)
        return -1;
    return 0;
}

int MCP9808::Configure(const TEMP_HYSTERESIS Hysteresis,
                       const int Mode,
                       const int Lock,
                       const int ClearInterrupt,
                       const int AlertStatus,
                       const int AlertControl,
                       const int AlertSelection,
                       const int AlertPolarity,
                       const int AlertMode)
{
    int buf = 0;

    // MSB
    buf = (int)Hysteresis;
    buf = (buf << 1) | (bool)Mode;

    // LSB
    buf = (buf << 1) | (bool)Lock;
    buf = (buf << 1) | (bool)Lock;
    buf = (buf << 1) | (bool)ClearInterrupt;
    buf = (buf << 1) | (bool)AlertStatus;
    buf = (buf << 1) | (bool)AlertControl;
    buf = (buf << 1) | (bool)AlertSelection;
    buf = (buf << 1) | (bool)AlertPolarity;
    buf = (buf << 1) | (bool)AlertMode;

    int res = 0;
    buf = SWAP_BYTES(buf);
    res = I2C_Write(&this->I2C, this->address, REGISTER(MCP9808_CONFIG), &buf, 1, 2);

    if (res != 0)
        return -1;
    return 0;
}

int MCP9808::GetIDs(int *const DeviceID, int *const DeviceRevision, int *const ManufacturerID)
{
    int res = 0;
    int buf = 0;
    res += I2C_Read(&this->I2C, this->address, REGISTER(DEVICEID), &buf, 1, 2);
    buf = SWAP_BYTES(buf);

    *DeviceID = buf & 0x00FF;
    *DeviceRevision = buf & 0xFF00;

    buf = 0;
    res += I2C_Read(&this->I2C, this->address, REGISTER(MANUFACTURER), &buf, 1, 2);
    buf = SWAP_BYTES(buf);
    *ManufacturerID = buf;

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

    int BufMin = 0;
    int BufMax = 0;
    int BufCrit = 0;

    // Don't need to swap bytes here, that's already done !
    FloatToInts(Minimal, &BufMin);
    FloatToInts(Maximal, &BufMax);
    FloatToInts(Critical, &BufCrit);

    BufMin = SWAP_BYTES(BufMin);
    BufMax = SWAP_BYTES(BufMax);
    BufCrit = SWAP_BYTES(BufCrit);

    int res = 0;
    res += I2C_Write(&this->I2C, this->address, REGISTER(UPPER_TEMP), &BufMax, 1, 2);
    res += I2C_Write(&this->I2C, this->address, REGISTER(LOWER_TEMP), &BufMin, 1, 2);
    res += I2C_Write(&this->I2C, this->address, REGISTER(CRIT_TEMP), &BufCrit, 1, 2);

    if (res != 0)
        return -4;
    return 0;
}

int MCP9808::ReadTemperature(float *const Temperature, int *const Status)
{
    int buf = 0;
    int res = I2C_Read(&this->I2C, this->address, REGISTER(READ_TEMP), &buf, 1, 2);
    buf = SWAP_BYTES(buf);

    if (res != 0)
        return -1;

    // Fetching in temp variables the correct values.
    *Status = (buf & 0xE000) >> 13;

    bool Sign = (bool)(buf & 0x1000);
    int INT = (buf & 0x0FF0) >> 4;
    int FLOAT = buf & 0x000F;

    if (Sign)
        *Temperature = -(INT + FLOAT * 0.0625);
    else
        *Temperature = (INT + FLOAT * 0.0625);
    return 0;
}