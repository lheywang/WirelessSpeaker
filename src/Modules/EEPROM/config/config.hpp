/**
 * @file config.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define the global structure that store all of our settings on the eeprom.
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

// Sub Structs
#include "audio/struct_audio.hpp"
#include "interfaces/struct_automated_interfaces.hpp"
#include "interfaces/struct_user_interfaces.hpp"

constexpr int MAX_CHAR_SPEAKER_NAME =
    32; /*!< Define the maximal lengh allowed for the Speaker friendly name*/

/*! Define values that are stored on the EEPROM for the overall speaker configuration */
struct CONFIG_V1
{
    struct Audio Audio; /*!< Configure all of the audio related settings*/

    struct LEDS LedsBack; /*!< Configure the leds placed at the back of the speaker*/
    struct LEDS LedsTop1; /*!< Configure the leds placed at the top 1*/
    struct LEDS LedsTop2; /*!< Configure the leds placed at the top 2*/
    struct LEDS LedsTop3; /*!< Configure the leds placed at the top 3*/

    struct Capacitive Capacitive; /*!< Configure the capacitive touch sensor*/

    struct BasicPDO PDProfile1; /*!< Store the usb-c user defined profile 1*/
    struct BasicPDO PDProfile2; /*!< Store the usb-c user defined profile 2*/

    uint8_t __padding1[22] = {0x00}; /*!< MEMORY PADDING. DO NOT TOUCH*/

    // End of first page

    char SpeakerName[MAX_CHAR_SPEAKER_NAME * 2] = {
        0x00}; /*!< Configure the speaker friendly name. UTF16 Accepted !*/

    // End of second page

    uint8_t __padding2[128] = {0x00}; /*!< MEMORY PADDING. DO NOT TOUCH*/

    // End of fourth page
};
