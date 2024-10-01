/**
 * @file PCA9633.cpp
 * @author l.heywang
 * @brief Source of the functions for the PCA9633 Leds Drivers
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */
// Header file
#include "PCA9633.hpp"

// Cpp modules
#include <cstdint>
#include "../../I2C/I2C.hpp"

// ==============================================================================
// MACROS
// ==============================================================================
// Define the way to pass commands to this IC
#define REGISTER_WITHOUT_INCREMENT(x) ((x & 0x0F) | 0x00)
#define REGISTER_WITH_INCREMENT_ALL(x) ((x & 0x0F) | 0x80)
#define REGISTER_WITH_INCREMENT_LEDS(x) ((x & 0x0F) | 0xA0)
#define REGISTER_WITH_INCREMENT_CTRL(x) ((x & 0x0F) | 0xC0)
#define REGISTER_WITH_INCREMENT_LEDS_CTRL(x) ((x & 0x0F) | 0xE0)

// =====================
// CONSTRUCTORS
// =====================

PCA9633::PCA9633(const I2C_Bus *I2C, const int address)
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
                       const int OEStatus)
{
    if ((OEStatus > LED_IN) | (OEStatus < LED_OFF))
        return -1;

    int buf[2] = {0};

    // MODE 1
    buf[0] = ((bool)Mode) << 4;
    buf[0] |= ((bool)SubAddr1Response) << 3;
    buf[0] |= ((bool)SubAddr2Response) << 2;
    buf[0] |= ((bool)SubAddr3Response) << 1;
    buf[0] |= ((bool)AllAddrResponse);

    // MODE 2
    buf[1] = ((bool)Dimming) << 5;
    buf[1] = ((bool)Inverter) << 4;
    buf[1] = ((bool)Change) << 3;
    buf[1] = ((bool)OutputDriver) << 2;
    buf[1] = ((bool)OEStatus);

    int res = I2C_Write(&this->I2C, this->address, REGISTER_WITH_INCREMENT_ALL(MODE1), buf, 2);
    if (res != 0)
        return -2;

    return 0;
}

int PCA9633::ConfigureDutyCycle(const int FirstChannel, int *const Value, const int AutoIncrement)
{
    if ((FirstChannel > PWM3) | (FirstChannel < PWM0))
        return -1;
    if ((FirstChannel + AutoIncrement) > PWM3)
        return -2;
    if (AutoIncrement == 0)
        return -2;

    // Let's create a copy to prevent from running out of memory if too short array is provided.
    int buf[4] = {0};
    for (int i = 0; i < AutoIncrement; i++)
        buf[i] = Value[i];

    int Tregister = 0;
    if (AutoIncrement == 1)
        Tregister = REGISTER_WITHOUT_INCREMENT(FirstChannel);
    else
        Tregister = REGISTER_WITH_INCREMENT_LEDS(FirstChannel);

    // Write the number of channels we want.
    int res = I2C_Write(&this->I2C, this->address, Tregister, buf, AutoIncrement);
    if (res != 0)
        return -3;

    return 0;
}

int PCA9633::ConfigureGlobalDimming(const int DutyCycle, const int Period)
{
    if ((DutyCycle < 0) | (DutyCycle > 99))
        return -1;
    if ((Period < 0x00) | (Period > 0xFF))
        return -2;

    int TempDuty = ((DutyCycle * 2.56) / 100);
    int buf[2] = {TempDuty, Period};

    int res = I2C_Write(&this->I2C, this->address, REGISTER_WITH_INCREMENT_CTRL(GRPPPWM), buf, 2);
    if (res != 0)
        return -3;

    return 0;
}
int PCA9633::SetLedStatus(const int LED1, const int LED2, const int LED3, const int LED4)
{
    if ((LED1 > LED_PWM_GLOB) | (LED1 < LED_OFF))
        return -1;
    if ((LED2 > LED_PWM_GLOB) | (LED2 < LED_OFF))
        return -1;
    if ((LED3 > LED_PWM_GLOB) | (LED3 < LED_OFF))
        return -1;
    if ((LED4 > LED_PWM_GLOB) | (LED4 < LED_OFF))
        return -1;

    int buf = (LED4 << 6) | (LED3 << 4) | (LED2 << 2) | LED1;
    int res = I2C_Write(&this->I2C, this->address, REGISTER_WITHOUT_INCREMENT(LEDOUT), &buf);
    if (res != 0)
        return -2;

    return 0;
}
int PCA9633::ConfigureSubAddress(const int SUBADDR, const int address)
{
    if ((SUBADDR > ALLCALLADR) | (SUBADDR < SUBADDR1))
        return -1;
    if ((address < 0x00) | (address > 0xFF))
        return -2;

    int buf = address << 1;
    int res = I2C_Write(&this->I2C, this->address, REGISTER_WITHOUT_INCREMENT(SUBADDR), &buf);
    if (res != 0)
        return -3;

    return 0;
}
