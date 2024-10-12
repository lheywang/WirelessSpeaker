/**
 * @file I2C.hpp
 * @author l.heywang
 * @brief Define Basic I2C parameters on the project.
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 * @remark Class was tested successfully on 01/10/2024.
 *
 */

// Only included one time
#pragma once
#include "I2C_Engine.hpp"

// ==============================================================================
// IC ADDRESSES
// ==============================================================================

inline constexpr int I2C_BUS_NUMBER = 1; /*!< Define the used bus on the RPi.*/

/*! Define I2C addresses for MCP9808 temperature sensor */
enum class TEMP_SENSOR
{
    TEMP_0 = 0x18, /*!< Sensor 0*/
    TEMP_1 = 0x19, /*!< Sensor 1*/
    TEMP_2 = 0x1A, /*!< Sensor 2*/
    TEMP_3 = 0x1B, /*!< Sensor 3*/
    TEMP_4 = 0x1C, /*!< Sensor 4*/
    TEMP_5 = 0x1D, /*!< Sensor 5*/
    TEMP_6 = 0x1E, /*!< Sensor 6*/
    TEMP_7 = 0x1F, /*!< Sensor 7*/
};

/*! Define I2C addresses for PCM5252 DAC */
enum class DAC
{
    DAC_0 = 0x4C, /*!< DAC 0*/
};

/*! Define I2C addresses for AT42QT1070 Touch sensor*/
enum class TOUCHSENSOR
{
    TOUCH_0 = 0x1B, /*!< Sensor 0*/
};

/*! Define I2C addresses for ADS1015 ADC */
enum class VOLTAGE_MONITOR
{
    ADC_0 = 0x90, /*!< ADC 0*/
    ADC_1 = 0x91, /*!< ADC 0*/
    ADC_2 = 0x92, /*!< ADC 0*/
    ADC_3 = 0x93, /*!< ADC 0*/
};

/*! Define I2C addresses for DS1882 logarithmic potentiometer*/
enum class LOG_POTI
{
    POTI_0 = 0x28, /*!< Poti 0*/
    POTI_1 = 0x29, /*!< Poti 1*/
    POTI_2 = 0x2A, /*!< Poti 2*/
    POTI_3 = 0x2B, /*!< Poti 3*/
    POTI_4 = 0x2C, /*!< Poti 4*/
    POTI_5 = 0x2D, /*!< Poti 5*/
    POTI_6 = 0x2E, /*!< Poti 6*/
    POTI_7 = 0x2F, /*!< Poti 7*/
};

/*! Define I2C addresses for MCP45HV51 linear potentiometer*/
enum class LIN_POTI
{
    POTI_0 = 0X78, /*!< Poti 1*/
    POTI_1 = 0x79, /*!< Poti 2*/
    POTI_2 = 0x7A, /*!< Poti 3*/
    POTI_3 = 0x7B, /*!< Poti 4*/
};

/*! Define I2C addresses for PCA9633 leds drivers IC*/
enum class LED_DRIVERS
{
    DRIVER_0 = 0xC2, /*!< Adress 0*/
    DRIVER_1 = 0xC3, /*!< Adress 0*/
    DRIVER_2 = 0xC4, /*!< Adress 0*/
    DRIVER_3 = 0xC5, /*!< Adress 0*/
};

/*! Define I2C addresses for STUSB4500 Power delivery management IC*/
enum class USB_PD
{
    PD_0 = 0x28, /*!< IC 0*/
};

/*! Define I2C addresses for MCP23009 GPIO expander*/
enum class GPIO_EXPANDER
{
    GPIO_0 = 0x20, /*!< GPIO Expander 0*/
    GPIO_1 = 0x21, /*!< GPIO Expander 1*/
    GPIO_2 = 0x22, /*!< GPIO Expander 2*/
    GPIO_3 = 0x23, /*!< GPIO Expander 3*/
    GPIO_4 = 0x24, /*!< GPIO Expander 4*/
    GPIO_5 = 0x25, /*!< GPIO Expander 5*/
    GPIO_6 = 0x26, /*!< GPIO Expander 6*/
    GPIO_7 = 0x27, /*!< GPIO Expander 7*/
};

/*! Define I2C addresses for INA219 Current monitor */
enum class CURRENT_MONITOR
{
    SHUNT_0 = 0x40, /*!< Current monitor 0*/
    SHUNT_1 = 0x41, /*!< Current monitor 1*/
    SHUNT_2 = 0x42, /*!< Current monitor 2*/
    SHUNT_3 = 0x43, /*!< Current monitor 3*/
};