/**
 * @file PCA9633.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source of the functions for the PCA9633 Leds Drivers
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 * @remark Class was tested successfully on 07/10/2024.
 *
 */
// Header file
#include "drivers/devices/PCA9633.hpp"

// Cpp modules
#include "drivers/peripherals/i2c.hpp"

// STD
#include <cstdint>
#include <iostream>

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

constexpr int MODE1 = 0x00;
constexpr int MODE2 = 0x01;
constexpr int PWM0 = 0x02;
constexpr int PWM1 = 0x03;
constexpr int PWM2 = 0x04;
constexpr int PWM3 = 0x05;
constexpr int GRPPPWM = 0x06;
constexpr int GRPFREQ = 0x07;
constexpr int LEDOUT = 0x08;
constexpr int SUBADDR1 = 0x09;
constexpr int SUBADDR2 = 0x0A;
constexpr int SUBADDR3 = 0x0B;
constexpr int ALLCALLADR = 0x0C;

// ==============================================================================
// MACROS
// ==============================================================================
// constexpr int the way to pass commands to this IC
constexpr int REGISTER_WITHOUT_INCREMENT(int x)
{
    return ((x & 0x0F) | 0x00);
}
constexpr int REGISTER_WITH_INCREMENT_ALL(int x)
{
    return ((x & 0x0F) | 0x80);
}
constexpr int REGISTER_WITH_INCREMENT_LEDS(int x)
{
    return ((x & 0x0F) | 0xA0);
}
constexpr int REGISTER_WITH_INCREMENT_CTRL(int x)
{
    return ((x & 0x0F) | 0xC0);
}
constexpr int REGISTER_WITH_INCREMENT_LEDS_CTRL(int x)
{
    return ((x & 0x0F) | 0xE0);
}

// =====================
// CONSTRUCTORS
// =====================

PCA9633::PCA9633(const I2C_Bus* I2C, const LED_DRIVERS address)
{
    this->address = (uint8_t)address;
    this->I2C = *I2C;
    return;
}

// =====================
// DESTRUCTORS
// =====================

PCA9633::~PCA9633()
{
    return;
}

// =====================
// FUNCTIONS
// =====================

int PCA9633::Configure(const int Mode,
                       const int SubAddr1Response,
                       const int SubAddr2Response,
                       const int SubAddr3Response,
                       const int AllAddrResponse,
                       const int Dimming,
                       const int Inverter,
                       const int Change,
                       const int OutputDriver,
                       const LED_MODES OEStatus)
{

    int buf[2] = {0};

    // MODE 1
    buf[0] = (!(bool)Mode);
    buf[0] = buf[0] << 1 | (bool)SubAddr1Response;
    buf[0] = buf[0] << 1 | (bool)SubAddr2Response;
    buf[0] = buf[0] << 1 | (bool)SubAddr3Response;
    buf[0] = buf[0] << 1 | (bool)AllAddrResponse;

    // MODE 2
    buf[1] = ((bool)Dimming);
    buf[1] = buf[1] << 1 | (bool)Inverter;
    buf[1] = buf[1] << 1 | (bool)Change;
    buf[1] = buf[1] << 1 | (bool)OutputDriver;
    buf[1] = buf[1] << 2 | (int)OEStatus;

    int res = I2C_Write(&this->I2C, this->address, REGISTER_WITH_INCREMENT_ALL(MODE1), buf, 2);
    if(res != 0)
        return -1;

    return 0;
}

int PCA9633::ConfigureDutyCycle(const LED_CHANNELS FirstChannel,
                                int* const Value,
                                const int AutoIncrement)
{
    if(((int)FirstChannel + AutoIncrement) > ((int)LED_CHANNELS::CHANNEL3 + 1))
        return -1;
    if(AutoIncrement == 0)
        return -1;

    // Let's create a copy to prevent from running out of memory if too short array is provided.
    int buf[4] = {0};
    for(int i = 0; i < AutoIncrement; i++)
        buf[i] = Value[i];

    int Tregister = 0;
    switch(FirstChannel)
    {
    case LED_CHANNELS::CHANNEL0:
        Tregister = PWM0;
        break;
    case LED_CHANNELS::CHANNEL1:
        Tregister = PWM1;
        break;
    case LED_CHANNELS::CHANNEL2:
        Tregister = PWM2;
        break;
    case LED_CHANNELS::CHANNEL3:
        Tregister = PWM3;
        break;
    }

    if(AutoIncrement == 1)
        Tregister = REGISTER_WITHOUT_INCREMENT(Tregister);
    else
        Tregister = REGISTER_WITH_INCREMENT_LEDS(Tregister);

    // Write the number of channels we want.
    int res = I2C_Write(&this->I2C, this->address, Tregister, buf, AutoIncrement);
    if(res != 0)
        return -2;

    return 0;
}

int PCA9633::ConfigureGlobalDimming(const int DutyCycle, const int Period)
{
    if((DutyCycle < 0) | (DutyCycle > 99))
        return -1;
    if((Period < 0x00) | (Period > 0xFF))
        return -2;

    int TempDuty = (DutyCycle * 2.56);
    int buf[2] = {0};

    buf[0] = TempDuty;
    buf[1] = Period;

    int res = I2C_Write(&this->I2C, this->address, REGISTER_WITH_INCREMENT_CTRL(GRPPPWM), buf, 2);
    if(res != 0)
        return -3;

    return 0;
}
int PCA9633::SetLedStatus(const LED_CHANNELS LED1,
                          const LED_CHANNELS LED2,
                          const LED_CHANNELS LED3,
                          const LED_CHANNELS LED4)
{
    int buf = ((int)LED4 << 6) | ((int)LED3 << 4) | ((int)LED2 << 2) | (int)LED1;
    int res = I2C_Write(&this->I2C, this->address, REGISTER_WITHOUT_INCREMENT(LEDOUT), &buf);
    if(res != 0)
        return -1;

    return 0;
}
int PCA9633::ConfigureSubAddress(const LED_ADDRESS SUBADDR, const int address)
{
    if((address < 0x00) | (address > 0xFF))
        return -1;

    int buf = address << 1;
    int res = I2C_Write(&this->I2C, this->address, REGISTER_WITHOUT_INCREMENT((int)SUBADDR), &buf);
    if(res != 0)
        return -2;

    return 0;
}
