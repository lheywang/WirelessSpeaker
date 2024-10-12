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

inline constexpr int I2C_BUS_NUMBER = 1;

/**
 * @brief Define MCP9808 Temperature sensor addresses
 *
 * @enumvalue TEMP_SENSOR:TEMP_0 Device temperature sensor 0
 * @enumvalue TEMP_SENSOR:TEMP_1 Device temperature sensor 1
 * @enumvalue TEMP_SENSOR:TEMP_2 Device temperature sensor 2
 * @enumvalue TEMP_SENSOR:TEMP_3 Device temperature sensor 3
 * @enumvalue TEMP_SENSOR:TEMP_4 Device temperature sensor 4
 * @enumvalue TEMP_SENSOR:TEMP_5 Device temperature sensor 5
 * @enumvalue TEMP_SENSOR:TEMP_6 Device temperature sensor 6
 * @enumvalue TEMP_SENSOR:TEMP_7 Device temperature sensor 7
 */
enum class TEMP_SENSOR
{
    TEMP_0 = 0x18,
    TEMP_1 = 0x19,
    TEMP_2 = 0x1A,
    TEMP_3 = 0x1B,
    TEMP_4 = 0x1C,
    TEMP_5 = 0x1D,
    TEMP_6 = 0x1E,
    TEMP_7 = 0x1F,
};

/**
 * @brief Define PCM5252 Adresses
 *
 * @enumvalue DAC::DAC_0 Define the address of the DAC.
 */
enum class DAC
{
    DAC_0 = 0x4C,
};

/**
 * @brief Define Touch sensor addresses
 *
 * @enumvalue TOUCHSENSOR::TOUCH_0 Address for the first touch sensor.
 */
enum class TOUCHSENSOR
{
    TOUCH_0 = 0x1B,
};

/**
 * @brief Define address for the ADS1015 ADC
 *
 * @enumvalue VOLTAGE_MONITOR::ADC_0 ADS1015 Address for IC 0
 * @enumvalue VOLTAGE_MONITOR::ADC_1 ADS1015 Address for IC 1
 * @enumvalue VOLTAGE_MONITOR::ADC_2 ADS1015 Address for IC 2
 * @enumvalue VOLTAGE_MONITOR::ADC_3 ADS1015 Address for IC 3
 */
enum class VOLTAGE_MONITOR
{
    ADC_0 = 0x90,
    ADC_1 = 0x91,
    ADC_2 = 0x92,
    ADC_3 = 0x93,
};

/**
 * @brief Define Logarithmic potentiometer address, used for analog configuration.
 *
 * @enumvalue LOG_POTI::POTI_0 Address of potentiometer 0
 * @enumvalue LOG_POTI::POTI_1 Address of potentiometer 1
 * @enumvalue LOG_POTI::POTI_2 Address of potentiometer 2
 * @enumvalue LOG_POTI::POTI_3 Address of potentiometer 3
 * @enumvalue LOG_POTI::POTI_4 Address of potentiometer 4
 * @enumvalue LOG_POTI::POTI_5 Address of potentiometer 5
 * @enumvalue LOG_POTI::POTI_6 Address of potentiometer 6
 * @enumvalue LOG_POTI::POTI_7 Address of potentiometer 7
 */
enum class LOG_POTI
{
    POTI_0 = 0x28,
    POTI_1 = 0x29,
    POTI_2 = 0x2A,
    POTI_3 = 0x2B,
    POTI_4 = 0x2C,
    POTI_5 = 0x2D,
    POTI_6 = 0x2E,
    POTI_7 = 0x2F,
};

/**
 * @brief Define address for MCP45HV51 addresses
 *
 * @enumvalue LIN_POTI::POTI_0 Address for linear potentiometer 0
 * @enumvalue LIN_POTI::POTI_1 Address for linear potentiometer 1
 * @enumvalue LIN_POTI::POTI_2 Address for linear potentiometer 2
 * @enumvalue LIN_POTI::POTI_3 Address for linear potentiometer 3
 */
enum class LIN_POTI
{
    POTI_0 = 0X78,
    POTI_1 = 0x79,
    POTI_2 = 0x7A,
    POTI_3 = 0x7B,
};

/**
 * @brief Define I2C Address for PCA9633 ICs.
 *
 * @enumvalue LED_DRIVERS::DRIVER_0 Address for PCA9633 0
 * @enumvalue LED_DRIVERS::DRIVER_1 Address for PCA9633 1
 * @enumvalue LED_DRIVERS::DRIVER_2 Address for PCA9633 2
 * @enumvalue LED_DRIVERS::DRIVER_3 Address for PCA9633 3
 */
enum class LED_DRIVERS
{
    DRIVER_0 = 0xC2,
    DRIVER_1 = 0xC3,
    DRIVER_2 = 0xC4,
    DRIVER_3 = 0xC5,
};

/**
 * @brief Define I2C_Adresses for the STUSB4500 IC
 *
 * @enumvalue USB_PD::PD_0 Define the address of the first interface.
 */
enum class USB_PD
{
    PD_0 = 0x28,
};

/**
 * @brief Define I2C Address for the GPIO Expanders
 *
 * @enumvalue GPIO_EXPANDER::GPIO_0 I2C Address for the GPIO Expander 0
 * @enumvalue GPIO_EXPANDER::GPIO_1 I2C Address for the GPIO Expander 1
 * @enumvalue GPIO_EXPANDER::GPIO_2 I2C Address for the GPIO Expander 2
 * @enumvalue GPIO_EXPANDER::GPIO_3 I2C Address for the GPIO Expander 3
 * @enumvalue GPIO_EXPANDER::GPIO_4 I2C Address for the GPIO Expander 4
 * @enumvalue GPIO_EXPANDER::GPIO_5 I2C Address for the GPIO Expander 5
 * @enumvalue GPIO_EXPANDER::GPIO_6 I2C Address for the GPIO Expander 6
 * @enumvalue GPIO_EXPANDER::GPIO_7 I2C Address for the GPIO Expander 7
 */
enum class GPIO_EXPANDER
{
    GPIO_0 = 0x20,
    GPIO_1 = 0x21,
    GPIO_2 = 0x22,
    GPIO_3 = 0x23,
    GPIO_4 = 0x24,
    GPIO_5 = 0x25,
    GPIO_6 = 0x26,
    GPIO_7 = 0x27,
};

/**
 * @brief Define INA219 Current monitor addresses
 *
 * @enumvalue CURRENT_MONITOR::SHUNT_0 I2C Address for INA219 0
 * @enumvalue CURRENT_MONITOR::SHUNT_1 I2C Address for INA219 1
 * @enumvalue CURRENT_MONITOR::SHUNT_2 I2C Address for INA219 2
 * @enumvalue CURRENT_MONITOR::SHUNT_3 I2C Address for INA219 3
 */
enum class CURRENT_MONITOR
{
    SHUNT_0 = 0x40,
    SHUNT_1 = 0x41,
    SHUNT_2 = 0x42,
    SHUNT_3 = 0x43,
};