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
#include "../../I2C/I2C.hpp"
#include <cstdint>

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

constexpr int CHIP_ID = 0x00;
constexpr int FIRMWARE_VERSION = 0x01;
constexpr int DETECTION_STATUS = 0x02;
constexpr int KEY_STATUS = 0x03;
constexpr int FASTOUT_MAXCAL_GUARD = 0x35;
constexpr int LOW_POWER_MODE = 0x36;
constexpr int MAX_ON_DURATION = 0x37;
constexpr int CALIBRATE = 0x38;
constexpr int TOUCH_RESET = 0x39;

// KEY SIGNALS
constexpr int KEY_SIGNAL_0 = 0x04;
constexpr int KEY_SIGNAL_1 = 0x06;
constexpr int KEY_SIGNAL_2 = 0x08;
constexpr int KEY_SIGNAL_3 = 0x0A;
constexpr int KEY_SIGNAL_4 = 0x0C;
constexpr int KEY_SIGNAL_5 = 0x0E;
constexpr int KEY_SIGNAL_6 = 0x10;

// REFERENCE DATA
constexpr int REFERENCE_DATA_0 = 0x12;
constexpr int REFERENCE_DATA_1 = 0x14;
constexpr int REFERENCE_DATA_2 = 0x16;
constexpr int REFERENCE_DATA_3 = 0x18;
constexpr int REFERENCE_DATA_4 = 0x1A;
constexpr int REFERENCE_DATA_5 = 0x1C;
constexpr int REFERENCE_DATA_6 = 0x1E;

// NEGATIVE THRESHOLD
constexpr int NEGATIVE_THRESHOLD_KEY_0 = 0x20;
constexpr int NEGATIVE_THRESHOLD_KEY_1 = 0x21;
constexpr int NEGATIVE_THRESHOLD_KEY_2 = 0x22;
constexpr int NEGATIVE_THRESHOLD_KEY_3 = 0x23;
constexpr int NEGATIVE_THRESHOLD_KEY_4 = 0x24;
constexpr int NEGATIVE_THRESHOLD_KEY_5 = 0x25;
constexpr int NEGATIVE_THRESHOLD_KEY_6 = 0x26;

// ADJACENT KEY SUPPRESION LEVEL
constexpr int ADJACENT_SUPPRESSION_LEVEL_KEY_0 = 0x27;
constexpr int ADJACENT_SUPPRESSION_LEVEL_KEY_1 = 0x28;
constexpr int ADJACENT_SUPPRESSION_LEVEL_KEY_2 = 0x29;
constexpr int ADJACENT_SUPPRESSION_LEVEL_KEY_3 = 0x2A;
constexpr int ADJACENT_SUPPRESSION_LEVEL_KEY_4 = 0x2B;
constexpr int ADJACENT_SUPPRESSION_LEVEL_KEY_5 = 0x2C;
constexpr int ADJACENT_SUPPRESSION_LEVEL_KEY_6 = 0x2D;

// DETECTION INTEGRATOR COUNTER
constexpr int DETECTION_INTEGRATOR_COUNTER_KEY_0 = 0x2E;
constexpr int DETECTION_INTEGRATOR_COUNTER_KEY_1 = 0x2F;
constexpr int DETECTION_INTEGRATOR_COUNTER_KEY_2 = 0x30;
constexpr int DETECTION_INTEGRATOR_COUNTER_KEY_3 = 0x31;
constexpr int DETECTION_INTEGRATOR_COUNTER_KEY_4 = 0x32;
constexpr int DETECTION_INTEGRATOR_COUNTER_KEY_5 = 0x33;
constexpr int DETECTION_INTEGRATOR_COUNTER_KEY_6 = 0x34;

// =====================
// CONSTRUCTORS
// =====================

AT42QT1070::AT42QT1070(const I2C_Bus* I2C)
{
    this->address = (uint8_t)TOUCHSENSOR::TOUCH_0;
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

int AT42QT1070::GetIDs(int* const ID, int* const FirmwareRevision)
{
    int buf[2] = {0};
    int res = 0;

    res += I2C_Read(&this->I2C, this->address, CHIP_ID, &buf[0]);
    res += I2C_Read(&this->I2C, this->address, FIRMWARE_VERSION, &buf[1]);

    *ID = buf[0];
    *FirmwareRevision = buf[1];

    if(res != 0)
        return -1;
    return 0;
}

int AT42QT1070::GetKeysStatus(int* const Calibration,
                              int* const Overflow,
                              int* const Touch,
                              int* const Keys)
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

    if(res != 0)
        return -1;
    return 0;
}

int AT42QT1070::GetKeySignals(const TOUCH_KEYS Key, int* const Value)
{
    int buf[2] = {0};
    int res = 0;

    // register are 16b, thus the *2 + offset.
    res += I2C_Read(&this->I2C, this->address, (2 * (int)Key + KEY_SIGNAL_0), &buf[0]);
    res += I2C_Read(&this->I2C, this->address, ((2 * (int)Key + KEY_SIGNAL_0) + 1), &buf[1]);

    *Value = (buf[0] << 8) | buf[1];

    if(res != 0)
        return -1;
    return 0;
}

int AT42QT1070::GetKeyReferenceSignal(const TOUCH_KEYS Key, int* const Value)
{
    int buf[2] = {0};
    int res = 0;

    // register are 16b, thus the *2 + offset.
    res += I2C_Read(&this->I2C, this->address, (2 * (int)Key + REFERENCE_DATA_0), &buf[0]);
    res += I2C_Read(&this->I2C, this->address, ((2 * (int)Key + REFERENCE_DATA_0) + 1), &buf[1]);

    *Value = (buf[0] << 8) | buf[1];

    if(res != 0)
        return -1;
    return 0;
}

int AT42QT1070::SetReferenceThreshold(const TOUCH_KEYS Key, const int Value)
{
    int buf = Value;
    int res = 0;

    // Offset from key to make the call easier.
    res = I2C_Write(&this->I2C, this->address, ((int)Key + NEGATIVE_THRESHOLD_KEY_0), &buf);

    if(res != 0)
        return -1;
    return 0;
}

int AT42QT1070::GetReferenceThreshold(const TOUCH_KEYS Key, int* const Value)
{
    int res = 0;
    int buf = 0;

    // Offset from key to make the call easier.
    res = I2C_Read(&this->I2C, this->address, ((int)Key + NEGATIVE_THRESHOLD_KEY_0), &buf);

    *Value = buf;

    if(res != 0)
        return -1;
    return 0;
}

int AT42QT1070::SetAdjacentKeySuppresion(const TOUCH_KEYS Key, const int Value)
{
    int buf = Value;
    int res = 0;

    // Offset from key to make the call easier.
    res = I2C_Write(&this->I2C, this->address, ((int)Key + ADJACENT_SUPPRESSION_LEVEL_KEY_0), &buf);

    if(res != 0)
        return -1;
    return 0;
}

int AT42QT1070::GetAdjacentKeySuppresion(const TOUCH_KEYS Key, int* const Value)
{
    int res = 0;
    int buf = 0;

    // Offset from key to make the call easier.
    res = I2C_Read(&this->I2C, this->address, ((int)Key + ADJACENT_SUPPRESSION_LEVEL_KEY_0), &buf);

    *Value = buf;

    if(res != 0)
        return -1;
    return 0;
}

int AT42QT1070::SetDetectionIntegrator(const TOUCH_KEYS Key, const int Value)
{
    int buf = Value;
    int res = 0;

    // Offset from key to make the call easier.
    res =
        I2C_Write(&this->I2C, this->address, ((int)Key + DETECTION_INTEGRATOR_COUNTER_KEY_0), &buf);

    if(res != 0)
        return -1;
    return 0;
}

int AT42QT1070::GetDetectionIntegrator(const TOUCH_KEYS Key, int* const Value)
{
    int res = 0;
    int buf = 0;

    // Offset from key to make the call easier.
    res =
        I2C_Read(&this->I2C, this->address, ((int)Key + DETECTION_INTEGRATOR_COUNTER_KEY_0), &buf);

    *Value = buf;

    if(res != 0)
        return -1;
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

    if((GuardChannel < 0) | (GuardChannel > 0x0F))
        return -1;
    if((LowPower < 0) | (LowPower > 0xFF))
        return -2;
    if((MaxOnDuration < 0) | (MaxOnDuration > 0xFF))
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

    if(res != 0)
        return -4;
    return 0;
}
