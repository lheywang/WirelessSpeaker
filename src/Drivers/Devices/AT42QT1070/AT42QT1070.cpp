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
