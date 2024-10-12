/**
 * @file Struct.hpp
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

#include "audio/struct_audio.hpp"
#include "interfaces/struct_user_interfaces.hpp"
#include "interfaces/struct_internal.hpp"
#include "interfaces/struct_automated_interfaces.hpp"

/*! Define values that are stored on the EEPROM for the overall speaker configuration */
struct Config
{
    std::string Speaker_Name; /*!< Configure the speaker friendly name*/

    struct Audio Audio; /*!< Configure all of the audio related settings*/

    struct LEDS LedsBack; /*!< Configure the leds placed at the back of the speaker*/
    struct LEDS LedsTop1; /*!< Configure the leds placed at the top 1*/
    struct LEDS LedsTop2; /*!< Configure the leds placed at the top 2*/
    struct LEDS LedsTop3; /*!< Configure the leds placed at the top 3*/

    struct Capacitive Capacitive; /*!< Configure the capacitive touch sensor*/

    struct Temperature TemperatureAmpBass;    /*!< Configure the response for the bass amplifier temperature sensor*/
    struct Temperature TemperatureAmpRight;   /*!< Configure the response for the right amplifier temperature sensor*/
    struct Temperature TemperatureAmpLeft;    /*!< Configure the response for the left amplifier temperature sensor*/
    struct Temperature TemperatureDac;        /*!< Configure the response for the DAC temperature sensor*/
    struct Temperature TemperatureAnalog;     /*!< Configure the response for the Analog filters amplifier temperature sensor*/
    struct Temperature TemperaturePowerInput; /*!< Configure the response for the Power input stage amplifier temperature sensor*/
    struct Temperature TemperatureMainBuck;   /*!< Configure the response for the Main SMPS amplifier temperature sensor*/
    struct Temperature TemperatureAuxBuck;    /*!< Configure the response for the Secondary SMPS amplifier temperature sensor*/

    struct VoltageMonitor MainMonitor;         /*!< Configure the main ADC to monitor voltages*/
    struct VoltageMonitor AnalogSupplyMonitor; /*!< Configure the second ADC to monitor analog voltages*/

    struct BasicPDO PDProfile1; /*!< Store the usb-c user defined profile 1*/
    struct BasicPDO PDProfile2; /*!< Store the usb-c user defined profile 2*/
};