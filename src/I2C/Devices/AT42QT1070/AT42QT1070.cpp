// ==============================================================================
//                              I2C/Devices/AT42QT1070/AT42QT1070.cpp
//                              Wrote by lheywang
//
// Define functions to interface with the IC
// ==============================================================================

// Header file
#include "AT42QT1070.hpp"

// Cpp modules
#include <cstdint>

// =====================
// CONSTRUCTORS
// =====================

AT42QT1070::AT42QT1070(int address)
{
    this->address = (uint8_t)AT42QT1070_ADDRESS;
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
