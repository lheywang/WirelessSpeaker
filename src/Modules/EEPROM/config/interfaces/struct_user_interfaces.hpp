/**
 * @file struct_user_interfaces.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define User accessible interfaces behavior.
 * @version 0.1
 * @date 2024-10-08
 *
 * @copyright Copyright (c) 2024
 *
 */

// Only included one time
#pragma once

// Libs
#include <iostream>
#include <cstdint>

/*! Define values that are stored on the EEPROM for the leds drivers */
struct LEDS
{
    uint8_t Brightness;        /*!< Define brightness value*/
    uint8_t MaximalBrightness; /*!< Define the maximal brightness value*/
};

/*! Define values that are stored on the EEPROM for the capacitive touch sensor*/
struct Capacitive
{
    uint8_t Threshold; /*!< Define the threshold value to trigger a touch*/
    uint8_t Sensivity; /*!< Define the sensivity of the sensor*/
};