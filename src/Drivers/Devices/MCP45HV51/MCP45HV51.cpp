/**
 * @file MCP45HV51.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source of the functions of the MCP45HV51.
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */
// Header file
#include "MCP45HV51.hpp"

// Cpp modules
#include <cstdint>
#include "../../I2C/I2C.hpp"

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

// Registers
constexpr int TCON0 = 0x04;
constexpr int WIPER_0 = 0x00;

// ==============================================================================
// MACROS
// ==============================================================================
// constexpr int the way of passing commands to this IC
constexpr int REGISTER_WRITE(int x) { return (((x & 0xF0) << 4) | 0x00); }
constexpr int REGISTER_INCREMENT(int x) { return (((x & 0xF0) << 4) | 0x40); }
constexpr int REGISTER_DECREMENT(int x) { return (((x & 0xF0) << 4) | 0x80); }
constexpr int REGISTER_READ(int x) { return (((x & 0xF0) << 4) | 0xC0); }

// =====================
// CONSTRUCTORS
// =====================

MCP45HV51::MCP45HV51(const I2C_Bus *I2C, const int address)
{
    this->address = (uint8_t)address;
    this->I2C = *I2C;
    return;
}

// =====================
// DESTRUCTORS
// =====================

MCP45HV51::~MCP45HV51()
{
    return;
}

// =====================
// FUNCTIONS
// =====================

int MCP45HV51::ConfigurePotentiometer(const int HardwareShutdownMode,
                                      const int R0A,
                                      const int R0W,
                                      const int R0B)
{
    int buf = 0XFF;
    buf = buf & (bool)HardwareShutdownMode;
    buf = (buf << 1) & (bool)R0A;
    buf = (buf << 1) & (bool)R0W;
    buf = (buf << 1) & (bool)R0B;

    int res = I2C_Write(&this->I2C, this->address, REGISTER_WRITE(TCON0), &buf);

    if (res != 0)
        return -1;
    return 0;
}

int MCP45HV51::WriteWiper(const int Value)
{
    if ((Value < 0x00) | (Value > 0xFF))
        return -1;

    int buf = Value;

    int res = I2C_Write(&this->I2C, this->address, REGISTER_WRITE(WIPER_0), &buf);

    if (res != 0)
        return -2;
    return 0;
}

int MCP45HV51::ReadWiper(int *const Value)
{
    int res = I2C_Read(&this->I2C, this->address, REGISTER_READ(WIPER_0), Value);

    if (res != 0)
        return -1;
    return 0;
}

int MCP45HV51::IncrementWiper()
{
    int buf = 0;
    int res = I2C_Write(&this->I2C, this->address, REGISTER_INCREMENT(WIPER_0), &buf, 0);

    if (res != 0)
        return -1;
    return 0;
}

int MCP45HV51::DecrementWiper()
{
    int buf = 0;
    int res = I2C_Write(&this->I2C, this->address, REGISTER_DECREMENT(WIPER_0), &buf, 0);

    if (res != 0)
        return -1;
    return 0;
}
