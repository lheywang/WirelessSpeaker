/**
 * @file AT42QT1070.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source for the AT42QT1070 functions
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 * @remark Class was tested successfully on 02/10/2024.
 *
 */

// Header file
#include "AT42QT1070.hpp"

// Cpp modules
#include <cstdint>
#include "../../I2C/I2C.hpp"

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

#define CHIP_ID 0x00
#define FIRMWARE_VERSION 0x01
#define DETECTION_STATUS 0x02
#define KEY_STATUS 0x03
#define FASTOUT_MAXCAL_GUARD 0x35
#define LOW_POWER_MODE 0x36
#define MAX_ON_DURATION 0x37
#define CALIBRATE 0x38
#define TOUCH_RESET 0x39

// KEY SIGNALS
#define KEY_SIGNAL_0 0x04
#define KEY_SIGNAL_1 0x06
#define KEY_SIGNAL_2 0x08
#define KEY_SIGNAL_3 0x0A
#define KEY_SIGNAL_4 0x0C
#define KEY_SIGNAL_5 0x0E
#define KEY_SIGNAL_6 0x10

// REFERENCE DATA
#define REFERENCE_DATA_0 0x12
#define REFERENCE_DATA_1 0x14
#define REFERENCE_DATA_2 0x16
#define REFERENCE_DATA_3 0x18
#define REFERENCE_DATA_4 0x1A
#define REFERENCE_DATA_5 0x1C
#define REFERENCE_DATA_6 0x1E

// NEGATIVE THRESHOLD
#define NEGATIVE_THRESHOLD_KEY_0 0x20
#define NEGATIVE_THRESHOLD_KEY_1 0x21
#define NEGATIVE_THRESHOLD_KEY_2 0x22
#define NEGATIVE_THRESHOLD_KEY_3 0x23
#define NEGATIVE_THRESHOLD_KEY_4 0x24
#define NEGATIVE_THRESHOLD_KEY_5 0x25
#define NEGATIVE_THRESHOLD_KEY_6 0x26

// ADJACENT KEY SUPPRESION LEVEL
#define ADJACENT_SUPPRESSION_LEVEL_KEY_0 0x27
#define ADJACENT_SUPPRESSION_LEVEL_KEY_1 0x28
#define ADJACENT_SUPPRESSION_LEVEL_KEY_2 0x29
#define ADJACENT_SUPPRESSION_LEVEL_KEY_3 0x2A
#define ADJACENT_SUPPRESSION_LEVEL_KEY_4 0x2B
#define ADJACENT_SUPPRESSION_LEVEL_KEY_5 0x2C
#define ADJACENT_SUPPRESSION_LEVEL_KEY_6 0x2D

// DETECTION INTEGRATOR COUNTER
#define DETECTION_INTEGRATOR_COUNTER_KEY_0 0x2E
#define DETECTION_INTEGRATOR_COUNTER_KEY_1 0x2F
#define DETECTION_INTEGRATOR_COUNTER_KEY_2 0x30
#define DETECTION_INTEGRATOR_COUNTER_KEY_3 0x31
#define DETECTION_INTEGRATOR_COUNTER_KEY_4 0x32
#define DETECTION_INTEGRATOR_COUNTER_KEY_5 0x33
#define DETECTION_INTEGRATOR_COUNTER_KEY_6 0x34

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
    int res = 0;

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
    if ((Key < KEY0) | (Key > KEY7))
        return -1;

    int buf[2] = {0};
    int res = 0;

    // register are 16b, thus the *2 + offset.
    res += I2C_Read(&this->I2C, this->address, (2 * Key + KEY_SIGNAL_0), &buf[0]);
    res += I2C_Read(&this->I2C, this->address, ((2 * Key + KEY_SIGNAL_0) + 1), &buf[1]);

    *Value = (buf[0] << 8) | buf[1];

    if (res != 0)
        return -2;
    return 0;
}

int AT42QT1070::GetKeyReferenceSignal(const int Key, int *const Value)
{
    if (!(Key & 0x01)) // prevent from accessing to LSByte directly.
        return -1;
    if ((Key < KEY0) | (Key > KEY7))
        return -1;

    int buf[2] = {0};
    int res = 0;

    // register are 16b, thus the *2 + offset.
    res += I2C_Read(&this->I2C, this->address, (2 * Key + REFERENCE_DATA_0), &buf[0]);
    res += I2C_Read(&this->I2C, this->address, ((2 * Key + REFERENCE_DATA_0) + 1), &buf[1]);

    *Value = (buf[0] << 8) | buf[1];

    if (res != 0)
        return -2;
    return 0;
}

int AT42QT1070::SetReferenceThreshold(const int Key, const int Value)
{
    if ((Key < KEY0) | (Key > KEY7))
        return -1;

    int buf = Value;
    int res = 0;

    // Offset from key to make the call easier.
    res = I2C_Write(&this->I2C, this->address, (Key + NEGATIVE_THRESHOLD_KEY_0), &buf);

    if (res != 0)
        return -2;
    return 0;
}

int AT42QT1070::GetReferenceThreshold(const int Key, int *const Value)
{
    if ((Key < KEY0) | (Key > KEY7))
        return -1;

    int res = 0;
    int buf = 0;

    // Offset from key to make the call easier.
    res = I2C_Read(&this->I2C, this->address, (Key + NEGATIVE_THRESHOLD_KEY_0), &buf);

    *Value = buf;

    if (res != 0)
        return -2;
    return 0;
}

int AT42QT1070::SetAdjacentKeySuppresion(const int Key, const int Value)
{
    if ((Key < KEY0) | (Key > KEY7))
        return -1;

    int buf = Value;
    int res = 0;

    // Offset from key to make the call easier.
    res = I2C_Write(&this->I2C, this->address, (Key + ADJACENT_SUPPRESSION_LEVEL_KEY_0), &buf);

    if (res != 0)
        return -2;
    return 0;
}

int AT42QT1070::GetAdjacentKeySuppresion(const int Key, int *const Value)
{
    if ((Key < KEY0) | (Key > KEY7))
        return -1;

    int res = 0;
    int buf = 0;

    // Offset from key to make the call easier.
    res = I2C_Read(&this->I2C, this->address, (Key + ADJACENT_SUPPRESSION_LEVEL_KEY_0), &buf);

    *Value = buf;

    if (res != 0)
        return -2;
    return 0;
}

int AT42QT1070::SetDetectionIntegrator(const int Key, const int Value)
{
    if ((Key < KEY0) | (Key > KEY7))
        return -1;

    int buf = Value;
    int res = 0;

    // Offset from key to make the call easier.
    res = I2C_Write(&this->I2C, this->address, (Key + DETECTION_INTEGRATOR_COUNTER_KEY_0), &buf);

    if (res != 0)
        return -2;
    return 0;
}

int AT42QT1070::GetDetectionIntegrator(const int Key, int *const Value)
{
    if ((Key < KEY0) | (Key > KEY7))
        return -1;

    int res = 0;
    int buf = 0;

    // Offset from key to make the call easier.
    res = I2C_Read(&this->I2C, this->address, (Key + DETECTION_INTEGRATOR_COUNTER_KEY_0), &buf);

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
