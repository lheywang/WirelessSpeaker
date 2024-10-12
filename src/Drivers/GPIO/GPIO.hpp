/**
 * @file GPIO_Engine.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Header for custom GPIO functions, that rely on the linux kernel functions.
 * @version 1.0
 * @date 2024-10-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
// ==============================================================================
// INCLUDES
// ==============================================================================

#include "includes/clk.hpp"
#include <string>
#include <linux/gpio.h>

// ==============================================================================
// PUBLIC DEFINES
// ==============================================================================
static constexpr const char *DEV_NAME = "/dev/gpiochip0";

/**
 * @brief Define GPIO values that are used on the PCB design, thus preventing usage of unwanted GPIOS.
 *
 * @enumvalue PINS::AMP1_FAULT Amplifier 1 fault signal
 * @enumvalue PINS::AMP2_FAULT Amplifier 2 fault signal
 * @enumvalue PINS::AMP3_FAULT Amplifier 3 fault signal
 *
 * @enumvalue PINS::POWER_INT Active low interrupt signal from the power subsystem.
 *
 * @enumvalue PINS::aRGB_TOP ARGB Output for WS2812 leds on top
 * @enumvalue PINS::aRGB_FRONT ARGB Output for SW2812 leds on front
 *
 * @enumvalue PINS::EXT_INT Active low interrupt signal from the ext ??
 *
 * @enumvalue PINS::TOUCH_INT Active low interrupt signal from the touch sensor.
 *
 */
enum class PINS
{
    AMP1_FAULT = 17,
    AMP2_FAULT = 27,
    AMP3_FAULT = 22,

    POWER_INT = 16,

    aRGB_TOP = 6,
    aRGB_FRONT = 13,

    EXT_INT = 5,

    TOUCH_INT = 26,
};

/**
 * @brief Define operating modes of the GPIO
 *
 * @enumvalue GPMODES::INPUT Input mode
 * @enumvalue GPMODES::Output Output mode
 */
enum class GPMODES
{
    INPUT = 0x00,
    OUTPUT = 0x01,
};

/**
 * @struct GPIO
 * @brief GPIO struct, used as base handle for GPIO manipulations.
 *        This is custom struct for our needs.
 *
 * @param GPIO::PinNumber The number of the GPIO that is used. WARNING : This is BCM Convention and not RPi one.
 *
 * @param GPIO::Mode A mode indicator, used to block incorrects requests.
 * @param GPIO::FuncName A custom string to describe to which function this GPIO is used.
 * @param GPIO::InOut Boolean that store the direction of this GPIO. Take True if set as Output.
 * @param GPIO::Polarity Boolean to store the polarity of the GPIO. Take True if active low.
 * @param GPIO::Type Integer that take different values depending on the type of the electrical type. (1 if Open-Drain, 2 if Open-Source, 0 if neither)
 * @param GPIO::Kernel Integer set to 1 if the Linux kernel is using it.
 * @param GPIO::Used A boolean to identify which GPIO are used by another code. Is filled by any definition functions.
 * @param GPIO::FuncName A string that store the function identifier that is currently linked to.
 */
struct GPIO
{
    unsigned int PinNumber;

    int Mode;
    bool InOut;
    bool Polarity;
    int Type;
    int Kernel;

    char Name[GPIO_MAX_NAME_SIZE];
    char FuncName[GPIO_MAX_NAME_SIZE];

    bool Used;
};

// ==============================================================================
// FUNCTIONS
// ==============================================================================

/**
 * @brief Return the informations of a specific GPIO Pin.
 *
 * @param[in] info A GPIOs enum member to designate a pin
 * @param[in] Mode A GPMODES enum member to designate the mode
 *
 * @return GPIO struct for further operations.
 */
GPIO GPIO_GetInfos(const PINS Pin, const GPMODES Mode);

/**
 * @brief Read the status of a GPIO.
 *
 * @warning Define the GPIO as Input, thus at High-Z state.
 *
 * @param[inout] info A GPIO struct that contain at least the GPIO number.
 * @param[out] status Pointer to an int that store the GPIO read value.
 *
 * @return  0 : OK
 * @return -1 : Failed to open the dev file
 * @return -2 : Failed to read the dev file
 * @return -3 : Failed to read the state of the GPIO
 */
int ReadGPIO(GPIO *info, int *const status);

/**
 * @brief Write the status to a GPIO.
 *
 * @warning Define the GPIO as Output, with active LOW by default.
 *
 * @param[inout] info A GPIO struct that contain at least the GPIO number.
 * @param[in] Status An integer to set the value. 0 = OFF_STATE, anything other will be ON_STATE.
 *
 * @return  0 : OK
 * @return -1 : Failed to open the dev file
 * @return -2 : Failed to read the dev file
 * @return -3 : Failed to write the state of the GPIO
 */
int WriteGPIO(GPIO *info, const int Status);
