/**
 * @file GPIO.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define standard constants for the GPIO part of the speaker.
 * @version 0.1
 * @date 2024-10-03
 *
 * @copyright Copyright (c) 2024
 *
 */
// ==============================================================================
// INCLUDES
// ==============================================================================
#include "GPIO_Engine.hpp"

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