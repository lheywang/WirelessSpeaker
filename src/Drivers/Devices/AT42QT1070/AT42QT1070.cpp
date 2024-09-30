/**
 * @file AT42QT1070.cpp
 * @author l.heywang
 * @brief Source for the AT42QT1070 functions
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

// Header file
#include "AT42QT1070.hpp"

// Cpp modules
#include <cstdint>
#include "../../I2C/I2C.hpp"

#include <iostream>

// =====================
// CONSTRUCTORS
// =====================

AT42QT1070::AT42QT1070(const I2C_Bus *I2C)
{
    this->address = (uint8_t)AT42QT1070_ADDRESS;
    this->I2C = *I2C;
    return;
}

// =====================
// DESTRUCTORS
// =====================

AT42QT1070::~AT42QT1070()
{
    return;
};

// =====================
// FUNCTIONS
// =====================

int AT42QT1070::GetIDs(int *const ID, int *const FirmwareRevision)
{
    int buf[2] = {0};
    int res = 0;

    res += I2C_Read(&this->I2C, this->address, CHIP_ID, &buf[0]);
    res += I2C_Read(&this->I2C, this->address, FIRMWARE_VERSION, &buf[1]);

    *ID = buf[0];
    *FirmwareRevision = buf[1];

    if (res != 0)
        return -1;
    return 0;
}

int AT42QT1070::GetKeysStatus(int *const Calibration, int *const Overflow, int *const Touch, int *const Keys)
{
    int buf[2] = {0};
    int res;

    res += I2C_Read(&this->I2C, this->address, DETECTION_STATUS, &buf[0]);
    res += I2C_Read(&this->I2C, this->address, KEY_STATUS, &buf[1]);

    // buf 0
    *Calibration = buf[0] >> 7;
    *Overflow = (buf[0] & 0x40) >> 6;
    *Touch = (buf[0] & 0x01);
    *Keys = buf[1];

    if (res != 0)
        return -1;
    return 0;
}

int AT42QT1070::GetKeySignals(const int Key, int *const Value)
{
    if (!(Key & 0x01)) // prevent from accessing to LSByte directly.
        return -1;
    if ((Key < KEY_SIGNAL_0) | (Key > KEY_SIGNAL_6))
        return -1;

    int buf[2] = {0};
    int res = 0;

    res += I2C_Read(&this->I2C, this->address, Key, &buf[0]);
    res += I2C_Read(&this->I2C, this->address, Key + 1, &buf[1]);

    *Value = (buf[0] << 8) | buf[1];

    if (res != 0)
        return -2;
    return 0;
}

int AT42QT1070::GetKeyReferenceSignal(const int Key, int *const Value)
{
    if (!(Key & 0x01)) // prevent from accessing to LSByte directly.
        return -1;
    if ((Key < REFERENCE_DATA_0) | (Key > REFERENCE_DATA_6))
        return -1;

    int buf[2] = {0};
    int res = 0;

    res += I2C_Read(&this->I2C, this->address, Key, &buf[0]);
    res += I2C_Read(&this->I2C, this->address, Key + 1, &buf[1]);

    *Value = (buf[0] << 8) | buf[1];

    if (res != 0)
        return -2;
    return 0;
}

int AT42QT1070::SetReferenceThreshold(const int Key, const int Value)
{
    if ((Key < NEGATIVE_THRESHOLD_KEY_0) | (Key > NEGATIVE_THRESHOLD_KEY_6))
        return -1;

    int buf = Value;
    int res = 0;

    res = I2C_Write(&this->I2C, this->address, Key, &buf);

    if (res != 0)
        return -2;
    return 0;
}

int AT42QT1070::GetReferenceThreshold(const int Key, int *const Value)
{
    if ((Key < NEGATIVE_THRESHOLD_KEY_0) | (Key > NEGATIVE_THRESHOLD_KEY_6))
        return -1;

    int res = 0;
    int buf = 0;

    res = I2C_Read(&this->I2C, this->address, Key, &buf);

    *Value = buf;

    if (res != 0)
        return -2;
    return 0;
}

int AT42QT1070::SetAdjacentKeySuppresion(const int Key, const int Value)
{
    if ((Key < ADJACENT_SUPPRESSION_LEVEL_KEY_0) | (Key > ADJACENT_SUPPRESSION_LEVEL_KEY_6))
        return -1;

    int buf = Value;
    int res = 0;

    res = I2C_Write(&this->I2C, this->address, Key, &buf);

    if (res != 0)
        return -2;
    return 0;
}

int AT42QT1070::GetAdjacentKeySuppresion(const int Key, int *const Value)
{
    if ((Key < ADJACENT_SUPPRESSION_LEVEL_KEY_0) | (Key > ADJACENT_SUPPRESSION_LEVEL_KEY_6))
        return -1;

    int res = 0;
    int buf = 0;

    res = I2C_Read(&this->I2C, this->address, Key, &buf);

    *Value = buf;

    if (res != 0)
        return -2;
    return 0;
}

int AT42QT1070::SetDetectionIntegrator(const int Key, const int Value)
{
    if ((Key < DETECTION_INTEGRATOR_COUNTER_KEY_0) | (Key > DETECTION_INTEGRATOR_COUNTER_KEY_6))
        return -1;

    int buf = Value;
    int res = 0;

    res = I2C_Write(&this->I2C, this->address, Key, &buf);

    if (res != 0)
        return -2;
    return 0;
}

int AT42QT1070::GetDetectionIntegrator(const int Key, int *const Value)
{
    if ((Key < DETECTION_INTEGRATOR_COUNTER_KEY_0) | (Key > DETECTION_INTEGRATOR_COUNTER_KEY_6))
        return -1;

    int res = 0;
    int buf = 0;

    res = I2C_Read(&this->I2C, this->address, Key, &buf);

    *Value = buf;

    if (res != 0)
        return -2;
    return 0;
}

int AT42QT1070::ConfigureCapacitiveSensor(const int FastOut,
                                          const int MaxCal,
                                          const int GuardChannel,
                                          const int LowPower,
                                          const int MaxOnDuration,
                                          const int Calibrate,
                                          const int nRESET)
{

    if ((GuardChannel < 0) | (GuardChannel > 0x0F))
        return -1;
    if ((LowPower < 0) | (LowPower > 0xFF))
        return -2;
    if ((MaxOnDuration < 0) | (MaxOnDuration > 0xFF))
        return -3;

    int buf = 0;
    buf = ((bool)FastOut) << 1;
    buf = ((bool)MaxCal) << 4;
    buf |= GuardChannel;

    int res = 0;

    res += I2C_Write(&this->I2C, this->address, FASTOUT_MAXCAL_GUARD, &buf);

    buf = LowPower;
    res += I2C_Write(&this->I2C, this->address, LOW_POWER_MODE, &buf);

    buf = MaxOnDuration;
    res += I2C_Write(&this->I2C, this->address, FASTOUT_MAXCAL_GUARD, &buf);

    buf = Calibrate;
    res += I2C_Write(&this->I2C, this->address, FASTOUT_MAXCAL_GUARD, &buf);

    buf = nRESET;
    res += I2C_Write(&this->I2C, this->address, FASTOUT_MAXCAL_GUARD, &buf);

    if (res != 0)
        return -4;
    return 0;
}
