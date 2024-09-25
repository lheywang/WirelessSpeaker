/**
 * @file I2C.hpp
 * @author l.heywang
 * @brief Define Basic I2C parameters on the project.
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

// Only included one time
#pragma once

// ==============================================================================
// IC ADDRESSES
// ==============================================================================

// Define temperature sensor adresses
// MCP9808
#define TEMPSENSOR_0 0x18
#define TEMPSENSOR_1 0x19
#define TEMPSENSOR_2 0x1A
#define TEMPSENSOR_3 0x1B
#define TEMPSENSOR_4 0x1C
#define TEMPSENSOR_5 0x1D
#define TEMPSENSOR_6 0x1E
#define TEMPSENSOR_7 0x1F

// Digital to Analog Converter
// PCM5252
#define DAC_0 0x4C

// Capacitive touch sensor
// AT42QT1070
#define TOUCHSENSOR_0 0x1B

// Voltage monitor
// ADS1015
#define VMON_0 0x90
#define VMON_1 0x91
#define VMON_2 0x92
#define VMON_3 0x93

// Logarithmic potentiometer
// DS1882B
#define LOG_POTI_0 0x28
#define LOG_POTI_1 0x29
#define LOG_POTI_2 0x2A
#define LOG_POTI_3 0x2B
#define LOG_POTI_4 0x2C
#define LOG_POTI_5 0x2D
#define LOG_POTI_6 0x2E
#define LOG_POTI_7 0x2F

// Linear potentiometer
// MCP45HV51
#define LIN_POTI_0 0X78
#define LIN_POTI_1 0x79
#define LIN_POTI_2 0x7A
#define LIN_POTI_3 0x7B

// Leds drivers
// PCA9633
#define LED_DRIVER_0 0xC2
#define LED_DRIVER_1 0xC3
#define LED_DRIVER_2 0xC4
#define LED_DRIVER_3 0xC5
#define LED_DRIVER_4 0xC6
#define LED_DRIVER_5 0xC7
#define LED_DRIVER_6 0xC8
#define LED_DRIVER_7 0xC9
// Theses chips can be addressed by any addresses, since all 7 bits are available. We won't expose all of thems