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

/**
 * @struct Config
 * @brief Store all of the configuration settings into a user accessible struct, stored on a local EEPROM.
 *
 * @param Config::Speaker_Name Store the speaker friendly name
 *
 * @param Config::LedsBack Store the leds at the back configuration.
 * @param Config::LedsTop1 Store the leds at the top configuration for first bank.
 * @param Config::LedsTop2 Store the leds at the top configuration for second bank.
 * @param Config::LedsTop3 Store the leds at the top configuration for third bank.
 *
 * @param Config::Capacitive Store the touch sensor parameters
 *
 * @param Config::TemperatureAmpBass Store the settings for the bass amplifier temperature sensor.
 * @param Config::TemperatureAmpRight Store the settings for the right amplifier temperature sensor.
 * @param Config::TemperatureAmpLeft Store the settings for the left amplifier temperature sensor.
 * @param Config::TemperatureDac Store the settings for the DAC temperature sensor.
 * @param Config::TemperatureAnalog Store the settings for the Analog filters temperature sensor.
 * @param Config::TemperaturePowerInput Store the settings for the power input area temperature sensor.
 * @param Config::TemperatureMainBuck Store the settings for the main supply temperature sensor.
 * @param Config::TemperatureAuxBuck Store the settings for the auxialliary supply temperature sensor.
 *
 * @param Config::MainMonitor Store the settings for the main supply voltage monitor
 * @param Config::AnalogSupplyMonitor Store the settings for the aux. supply voltage monitor
 *
 * @param Config::PDProfile1 Store the settings for the first power delivery profile
 * @param Config::PDProfile2 Store the settings for the second power delivery profile
 * @param Config::PDProfile3 Store the settings for the third power delivery profile
 *
 */
struct Config
{
    std::string Speaker_Name;

    struct Audio Audio;

    struct LEDS LedsBack;
    struct LEDS LedsTop1;
    struct LEDS LedsTop2;
    struct LEDS LedsTop3;

    struct Capacitive Capacitive;

    struct Temperature TemperatureAmpBass;
    struct Temperature TemperatureAmpRight;
    struct Temperature TemperatureAmpLeft;
    struct Temperature TemperatureDac;
    struct Temperature TemperatureAnalog;
    struct Temperature TemperaturePowerInput;
    struct Temperature TemperatureMainBuck;
    struct Temperature TemperatureAuxBuck;

    struct VoltageMonitor MainMonitor;
    struct VoltageMonitor AnalogSupplyMonitor;

    struct BasicPDO PDProfile1;
    struct BasicPDO PDProfile2;
    struct BasicPDO PDProfile3;
};