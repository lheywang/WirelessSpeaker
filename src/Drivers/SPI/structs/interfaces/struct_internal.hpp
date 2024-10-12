/**
 * @file struct_internal.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define internal behaviors of the speaker
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

/*! Define values that are stored on the EEPROM for the temperature sensor */
struct Temperature
{
    uint16_t Maximal_Temperature; /*!< Define maximal temperature before triggering an interrupt*/
    uint16_t Minimal_Temperature; /*!< Define minimal temperature before triggering an interrupt*/
};

/*! Define values that are stored on the EEPROM for the voltage monitoring ADC */
struct VoltageMonitor
{
    uint8_t GainChannelA; /*!< Define the gain applied to the channel 1*/
    uint8_t GainChannelB; /*!< Define the gain applied to the channel 2*/
    uint8_t GainChannelC; /*!< Define the gain applied to the channel 3*/
    uint8_t GainChannelD; /*!< Define the gain applied to the channel 4*/

    uint16_t ChannelANominal; /*!< Define the nominal value for the channel 1*/
    uint16_t ChannelBNominal; /*!< Define the nominal value for the channel 2*/
    uint16_t ChannelCNominal; /*!< Define the nominal value for the channel 3*/
    uint16_t ChannelDNominal; /*!< Define the nominal value for the channel 4*/

    uint8_t Tolerance; /*!< Define the % of tolerance for each value before creating an exception*/
};