/**
 * @file struct_leds.hpp
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

/**
 * @struct LEDS
 * @brief Structure that contain all of the LEDS setings.
 *        Store the brightness values.
 *        Store the group configuration values.
 *
 * @var LEDS::Brightness The maximal brightness of the leds. Some inferior levels will be indexed from it.
 * @var LEDS::MaximalBrightness THe maximal brighness settings for the leds.
 *
 * @var LEDS::Address1 The I2C sub address 1
 * @var LEDS::Address2 The I2C sub address 2
 * @var LEDS::Address3 The I2C sub address 3
 * @var LEDS::Global The I2C global sub address
 *
 * @var LEDS::Address1Response The I2C sub address 1 enable boolean
 * @var LEDS::Address2Response The I2C sub address 2 enable boolean
 * @var LEDS::Address3Response The I2C sub address 3 enable boolean
 * @var LEDS::GlobalResponse The I2C global sub address enable boolean
 *
 */
struct LEDS
{
    uint8_t Brightness;
    uint8_t MaximalBrightness;

    uint8_t Address1;
    uint8_t Address2;
    uint8_t Address3;
    uint8_t Global;

    bool Address1Response;
    bool Address2Response;
    bool Address3Response;
    bool GlobalResponse;
};

/**
 * @struct Capacitive
 * @brief Structure that contain all of the Capacitive Sensor Settings such as the sensivity or the threshold values.
 *
 * @var Capacitive::Threshold Contain the value of the peak that need to be measured to be considered as a touch.
 * @var Capacitive::Sensivity Contain the value of the number of consecutive touch to be measured before considering the touch valid.
 *
 */
struct Capacitive
{
    uint8_t Threshold;
    uint8_t Sensivity;
};