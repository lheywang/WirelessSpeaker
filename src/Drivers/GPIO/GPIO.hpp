/**
 * @file GPIO.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define standard constants for the GPIO part of the speaker.
 * @version 1.0
 * @date 2024-10-03
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
// ==============================================================================
// INCLUDES
// ==============================================================================
#include "GPIO_Engine.hpp"
#include "includes/clk.hpp"

#include <string>

// ==============================================================================
// PUBLIC DEFINES
// ==============================================================================
static constexpr const char *DEV_NAME = "/dev/gpiochip0";

/**
 * @brief Define GPIO values that are used on the PCB design, thus preventing usage of unwanted GPIOS.
 *
 * @enumvalue GPIOS::AMP1_FAULT Amplifier 1 fault signal
 * @enumvalue GPIOS::AMP2_FAULT Amplifier 2 fault signal
 * @enumvalue GPIOS::AMP3_FAULT Amplifier 3 fault signal
 *
 * @enumvalue GPIOS::POWER_INT Active low interrupt signal from the power subsystem.
 *
 * @enumvalue GPIOS::aRGB_TOP ARGB Output for WS2812 leds on top
 * @enumvalue GPIOS::aRGB_FRONT ARGB Output for SW2812 leds on front
 *
 * @enumvalue GPIOS::EXT_INT Active low interrupt signal from the ext ??
 *
 * @enumvalue GPIOS::TOUCH_INT Active low interrupt signal from the touch sensor.
 *
 */
enum class GPIOS
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
