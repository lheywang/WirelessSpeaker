/**
 * @file MCP23009.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source for the MCP23009 class.
 * @version 0.1
 * @date 2024-10-02
 *
 * @copyright Copyright (c) 2024
 *
 * @remark Class was tested successfully on 07/10/2024.
 *
 */

// Header file
#include "MCP23009.hpp"

// Cpp modules
#include "../../I2C/I2C.hpp"
#include <cstdint>
#include <stdio.h>

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

constexpr int IODIR = 0x00;
constexpr int IPOL = 0x01;
constexpr int INTEN = 0x02;
constexpr int DEFVAL = 0x03;
constexpr int INTCON = 0x04;
constexpr int IOCON = 0x05;
constexpr int GPPU = 0x06;
constexpr int INTF = 0x07;
constexpr int INTCAP = 0x08;
constexpr int GPIO = 0x09;
constexpr int OLAT = 0x0A;

// =====================
// CONSTRUCTORS
// =====================

MCP23009::MCP23009(const I2C_Bus* I2C, const GPIO_EXPANDER address)
{
    this->address = (uint8_t)address;
    this->I2C = *I2C;
    return;
}

// =====================
// DESTRUCTORS
// =====================

MCP23009::~MCP23009()
{
    return;
}

// =====================
// FUNCTIONS
// =====================

int MCP23009::ReadInterrupts(int* const INTFlags, int* const PortValue)
{
    int res = 0;
    int buf[2] = {0};

    res += I2C_Read(&this->I2C, this->address, INTCAP, &buf[0]);
    res += I2C_Read(&this->I2C, this->address, INTF, &buf[1]);

    if(res != 0)
        return -1;

    *INTFlags = buf[1];
    *PortValue = buf[0];

    return 0;
}

int MCP23009::ReadInputs(int* const Status)
{
    int res = 0;
    int buf = 0;

    res = I2C_Read(&this->I2C, this->address, GPIO, &buf);

    if(res != 0)
        return -1;

    *Status = buf;

    return 0;
}

int MCP23009::SetOutputs(const int Status)
{
    if((0 > Status) | (Status > 0xFF))
        return -1;

    int res = 0;
    int buf = 0;

    buf = Status;

    res += I2C_Write(&this->I2C, this->address, OLAT, &buf);

    if(res != 0)
        return -2;
    return 0;
}

int MCP23009::Configure(const int INTPinMode, const int INTPolarity)
{
    int res = 0;
    int buf = 0;

    buf = 0;
    buf = buf << 3 | (bool)INTPinMode;
    buf = buf << 1 | (bool)INTPolarity;
    buf = buf << 1 | 1;

    res += I2C_Write(&this->I2C, this->address, IOCON, &buf);

    if(res != 0)
        return -1;
    return 0;
}

int MCP23009::ConfigureGPIO(const int Direction,
                            const int Polarity,
                            const int EnablePullUps,
                            const int EnableInterrupts,
                            const int IOC,
                            const int DefaultValue)
{
    if((0 > Direction) | (Direction > 0xFF))
        return -1;
    if((0 > Polarity) | (Polarity > 0xFF))
        return -2;
    if((0 > EnablePullUps) | (EnablePullUps > 0xFF))
        return -3;
    if((0 > EnableInterrupts) | (EnableInterrupts > 0xFF))
        return -4;
    if((0 > IOC) | (IOC > 0xFF))
        return -5;
    if((0 > DefaultValue) | (DefaultValue > 0xFF))
        return -6;

    int res = 0;
    int buf[6] = {0};

    buf[0] = Direction;
    buf[1] = Polarity;
    buf[2] = EnablePullUps;
    buf[3] = EnableInterrupts;
    buf[4] = IOC;
    buf[5] = DefaultValue;

    res += I2C_Write(&this->I2C, this->address, IODIR, &buf[0]);
    res += I2C_Write(&this->I2C, this->address, IPOL, &buf[1]);
    res += I2C_Write(&this->I2C, this->address, GPPU, &buf[2]);
    res += I2C_Write(&this->I2C, this->address, INTEN, &buf[3]);
    res += I2C_Write(&this->I2C, this->address, INTCON, &buf[4]);
    res += I2C_Write(&this->I2C, this->address, DEFVAL, &buf[5]);

    if(res != 0)
        return -7;
    return 0;
}