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

// =====================
// CONSTRUCTORS
// =====================

AT42QT1070::AT42QT1070(const I2C_Bus *I2C, const int address)
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
}

int AT42QT1070::GetKeysStatus(int *const Calibration, int *const Overflow, int *const Touch, int *const Keys)
{
}

int AT42QT1070::GetKeySignals(const int Key, int *const Value)
{
}

int AT42QT1070::GetKeyReferenceSignal(const int Key, int *const Value)
{
}

int AT42QT1070::SetReferenceThreshold(const int Key, const int Value)
{
}

int AT42QT1070::GetReferenceThreshold(const int Key, int *const Value)
{
}

int AT42QT1070::SetAdjacentKeySuppresion(const int Key, const int Value)
{
}

int AT42QT1070::GetAdjacentKeySuppresion(const int Key, int *const Value)
{
}

int AT42QT1070::SetDetectionIntegrator(const int Key, const int Value)
{
}

int AT42QT1070::GetDetectionIntegrator(const int Key, int *const Value)
{
}

int AT42QT1070::ConfigureCapacitiveSensor(const int FastOut,
                                          const int MaxCal,
                                          const int GuardChannel,
                                          const int LowPower,
                                          const int MaxOnDuration,
                                          const int Calibrate,
                                          const int nRESET)
{
}
