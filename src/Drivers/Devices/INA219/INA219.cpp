/**
 * @file INA219.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source for the INA219 class.
 * @version 0.1
 * @date 2024-10-02
 *
 * @copyright Copyright (c) 2024
 *
 */

// Header file
#include "INA219.hpp"

// Cpp modules
#include <cstdint>
#include <stdio.h>
#include <math.h>
#include "../../I2C/I2C.hpp"

// =====================
// REGISTERS
// =====================
constexpr int CONFIG = 0x00;
constexpr int SHUNTVOLTAGE = 0x01;
constexpr int BUSVOLTAGE = 0x02;
constexpr int POWER = 0x03;
constexpr int BUSCURRENT = 0x04;
constexpr int CALIBRATION = 0x05;

// =====================
// CONSTRUCTORS
// =====================

INA219::INA219(const I2C_Bus *I2C, const CURRENT_MONITOR address)
{
    this->address = (uint8_t)address;
    this->I2C = *I2C;

    this->PGASetting = 0x01;
    return;
}

// =====================
// DESTRUCTORS
// =====================

INA219::~INA219()
{
    return;
}

// =====================
// PRIVATES
// =====================
float INA219::ConvertIntToFloat(const int Value)
{
    int Sign;
    int ToFloat;

    switch (this->PGASetting)
    {
    case 1:
        Sign = Value & 0x8000;
        ToFloat = Value & 0x7FFF;
        break;
    case 2:
        Sign = Value & 0x4000;
        ToFloat = Value & 0x3FFF;
        break;
    case 3:
        Sign = Value & 0x2000;
        ToFloat = Value & 0x1FFF;
        break;
    case 4:
        Sign = Value & 0x1000;
        ToFloat = Value & 0x0FFF;
        break;
    }

    if (Sign == 1)
        ToFloat = !ToFloat + 1; // Auto cast isn't properlyconstexpr intd here, thus we apply it by hand.

    return Value / 100;
}

int INA219::ConvertFloatToInt(const float Value)
{
    float intermediate = round(Value * 100);
    int buf = -((int)intermediate);
    int Sign = (buf < 0) ? 1 : 0;

    switch (this->PGASetting)
    {
    case 1:
        return (Sign << 15) | (buf && 0x7FFFF);
        break;
    case 2:
        return (Sign << 15) | (Sign << 14) | (buf && 0x3FFFF);
        break;
    case 3:
        return (Sign << 15) | (Sign << 14) | (Sign << 13) | (buf && 0x1FFFF);
        break;
    case 4:
        return (Sign << 15) | (Sign << 14) | (Sign << 13) | (Sign << 12) | (buf && 0x0FFFF);
        break;
    }
    return -1;
}

// =====================
// FUNCTIONS
// =====================

int INA219::Configure(const int Reset, const int BusVoltageRange, const int SetPGAGain, const int BusVoltageADCResolution, const int BusCurrentADCResolution, const int OperatingMode)
{
    if ((0 > SetPGAGain) | (SetPGAGain > 0x03))
        return -1;
    if ((0 > BusVoltageADCResolution) | (BusVoltageADCResolution > 0x0F))
        return -2;
    if ((0 > BusCurrentADCResolution) | (BusCurrentADCResolution > 0x0F))
        return -3;
    if ((0 > OperatingMode) | (OperatingMode > 0x07))
        return -4;

    int res = 0;
    int buf = 0;

    buf = (bool)Reset;
    buf = buf << 2 | (bool)BusVoltageRange;
    buf = buf << 2 | SetPGAGain;
    buf = buf << 2 | BusVoltageADCResolution;
    buf = buf << 4 | BusCurrentADCResolution;
    buf = buf << 3 | OperatingMode;

    res += I2C_Write(&this->I2C, this->address, CONFIG, &buf, 1, 2);

    if (res != 0)
        return -5;

    this->PGASetting = 4 - SetPGAGain;
    return 0;
}

int INA219::ReadShuntVoltage(float *const Value)
{
    int res = 0;
    int buf = 0;

    res += I2C_Read(&this->I2C, this->address, SHUNTVOLTAGE, &buf, 1, 2);

    if (res != 0)
        return -1;

    *Value = this->ConvertIntToFloat(buf);

    return 0;
}

int INA219::ReadPower(float *const Value)
{
    int res = 0;
    int buf = 0;

    res += I2C_Read(&this->I2C, this->address, POWER, &buf, 1, 2);

    if (res != 0)
        return -1;

    *Value = this->ConvertIntToFloat(buf);

    return 0;
}

int INA219::ReadCurrent(float *const Value)
{
    int res = 0;
    int buf = 0;

    res += I2C_Read(&this->I2C, this->address, BUSCURRENT, &buf, 1, 2);

    if (res != 0)
        return -1;

    *Value = this->ConvertIntToFloat(buf);

    return 0;
}

int INA219::SetCalibration(const float Value)
{
    int res = 0;
    int buf = 0;

    buf = this->ConvertFloatToInt(Value);

    if (buf == -1)
        return -1;

    res += I2C_Write(&this->I2C, this->address, CALIBRATION, &buf, 1, 2);

    if (res != 0)
        return -2;
    return 0;
}

int INA219::ReadBusVoltage(float *const Value)
{
    int res = 0;
    int buf = 0;

    res += I2C_Read(&this->I2C, this->address, BUSVOLTAGE, &buf, 1, 2);

    if (res != 0)
        return -1;

    *Value = this->ConvertIntToFloat(buf);

    return 0;
}
