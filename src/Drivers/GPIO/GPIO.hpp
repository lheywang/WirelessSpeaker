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
// ==============================================================================
// INCLUDES
// ==============================================================================
#include "GPIO_Engine.hpp"
#include "includes/clk.hpp"

// ==============================================================================
// PUBLIC DEFINES
// ==============================================================================
#define DEV_NAME "/dev/gpiochip0"

// Amplifiers status
#define AMP1_FAULT 17
#define AMP2_FAULT 27
#define AMP3_FAULT 22

// Power subsystem interrupt pin.
#define POWER_INT 16

// aRGB
#define aRGB_TOP 6
#define aRGB_FRONT 13

// GPIO Expander Interrupts
#define EXT_INT 5

// Touch sensor Interrupt
#define TOUCH_INT 26

// Battery
#define BATTERY_INT 25

// SMPS Int
#define POWER_INT 16
