// ==============================================================================
//                              GPIO/GPIO.hpp
//                              Wrote by lheywang
//
// Define our basic I2C settings on the boards, such as :
// - Pins usage
// ==============================================================================

// Only included one time
#pragma once

#include <linux/gpio.h>

// ==============================================================================
// STANDARD USAGES
// ==============================================================================

// Amplifiers status
#define AMP1_FAULT 17
#define AMP2_FAULT 27
#define AMP3_FAULT 22

// Pozer subsystem interrupt pin.
#define POWER_INT 16