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

    uint8_t Address1; /*!< Configure it's subaddress 1*/
    uint8_t Address2; /*!< Configure it's subaddress 2*/
    uint8_t Address3; /*!< Configure it's subaddress 3*/
    uint8_t Global;   /*!< Configure it's subaddress 4 (global)*/

    bool Address1Response; /*!< Enable the sub-address 1 response*/
    bool Address2Response; /*!< Enable the sub-address 2 response*/
    bool Address3Response; /*!< Enable the sub-address 3 response*/
    bool GlobalResponse;   /*!< Enable the sub-address 4 (global) response*/
};

/*! Define values that are stored on the EEPROM for the capacitive touch sensor*/
struct Capacitive
{
    uint8_t Threshold; /*!< Define the threshold value to trigger a touch*/
    uint8_t Sensivity; /*!< Define the sensivity of the sensor*/
};