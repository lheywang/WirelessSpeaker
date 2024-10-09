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

/**
 * @struct Temperature
 * @brief Structure that contain all of the Temperature monitoring settings,
 *        and more precisely the values of the Interrupts at which an action shall be triggered (overheat ?)
 *
 * @param Temperature::Maximal_Temperature Maximal Temperature that is accepted.
 * @param Temperature::Minimal_Temperature Minimal Temperature that is accepted.
 *
 */
struct Temperature
{
    uint16_t Maximal_Temperature;
    uint16_t Minimal_Temperature;
};

/**
 * @struct VoltageMonitor
 * @brief Define voltage monitor settings.
 *
 * @param VoltageMonitor::GainChannelA Gain for channel A
 * @param VoltageMonitor::GainChannelB Gain for channel B
 * @param VoltageMonitor::GainChannelC Gain for channel C
 * @param VoltageMonitor::GainChannelD Gain for channel D
 *
 * @param VoltageMonitor::ChannelANominal Standard value for channel A
 * @param VoltageMonitor::ChannelBNominal Standard value for channel B
 * @param VoltageMonitor::ChannelCNominal Standard value for channel C
 * @param VoltageMonitor::ChannelDNominal Standard value for channel D
 *
 * @param VoltageMonitor::Tolerance Tolerance in % of excursion before triggering a failure.
 *
 */
struct VoltageMonitor
{
    uint8_t GainChannelA;
    uint8_t GainChannelB;
    uint8_t GainChannelC;
    uint8_t GainChannelD;

    uint16_t ChannelANominal;
    uint16_t ChannelBNominal;
    uint16_t ChannelCNominal;
    uint16_t ChannelDNominal;

    uint8_t Tolerance;
};