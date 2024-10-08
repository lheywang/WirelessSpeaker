/**
 * @file ADS1015.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source for the ADS1015 ADC.
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */
// Header file
#include "ADS1015.hpp"

// Cpp modules
#include <cstdint>
#include <unistd.h>
#include <math.h>

#include <iostream>

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

#define CONVERSION_REGISTER 0x00
#define CONFIG_REGISTER 0x01
#define LOW_TRESHOLD_REGISTER 0x02
#define HIGH_THRESHOLD_REGISTER 0x03

// =====================
// CONSTRUCTORS
// =====================

ADS1015::ADS1015(const I2C_Bus *I2C, const int address)
{
    this->address = (uint8_t)address;
    this->I2C = *I2C;

    this->ReferenceVoltage = 3.30000000;
    this->HighThreshold = this->ReferenceVoltage;
    this->LowThreshold = 0.0;
    this->ActualGain = 0x02;
    this->ActualMode = 0x01;
    this->ActualChannel = 0x04;
    this->ActualSampling = 0x04;
    this->ActualComparator_mode = 0x00;
    this->ActualComparator_queue = 0x03;
    this->ActualComparator_polarity = 0x00;
    this->ActualComparator_latching = 0x00;
    return;
}

// =====================
// DESTRUCTORS
// =====================

ADS1015::~ADS1015()
{
    return;
}

// =====================
// FUNCTIONS
// =====================
int ADS1015::ConfigureVoltageReference(const float Reference)
{
    this->ReferenceVoltage = Reference;
    return 0;
}

int ADS1015::Read_Voltage(const int channel, float *const value)
{
    if ((channel > ADC_CHANNEL_3) | (channel < ADC_CHANNEL_0))
        return -1;

    int buf = 0;
    int res = 0;

    // Call to restore old settings.
    // We only configure the current channel and start a conversion.
    res += this->Configure_ADC(1,
                               channel,
                               this->ActualGain,
                               this->ActualMode,
                               this->ActualSampling,
                               this->ActualComparator_mode,
                               this->ActualComparator_polarity,
                               this->ActualComparator_latching,
                               this->ActualComparator_queue);

    int microseconds = 0;

    switch (this->ActualSampling)
    {
    case ADC_SPS_128:
        microseconds = (1 / 128) * 5 * 1000; // (1 / 128Hz) * 5 in microseconds.
        break;
    case ADC_SPS_250:
        microseconds = (1 / 250) * 5 * 1000; // (1 / 250Hz) * 5 in microseconds.
        break;
    case ADC_SPS_490:
        microseconds = (1 / 490) * 5 * 1000; // (1 / 490Hz) * 5 in microseconds.
        break;
    case ADC_SPS_920:
        microseconds = (1 / 920) * 5 * 1000; // (1 / 920Hz) * 5 in microseconds.
        break;
    case ADC_SPS_1600:
        microseconds = (1 / 1600) * 5 * 1000; // (1 / 1.6kHz) * 5 in microseconds.
        break;
    case ADC_SPS_2400:
        microseconds = (1 / 2400) * 5 * 1000; // (1 / 2.4kHz) * 5 in microseconds.
        break;
    case ADC_SPS_3300:
        microseconds = (1 / 3300) * 5 * 1000; // (1 / 3.3kHz) * 5 in microseconds.
        break;
    }

    // Wait until the conversion has finished.
    usleep(microseconds);

    res += I2C_Read(&this->I2C, this->address, CONVERSION_REGISTER, &buf, 1, 2);
    std::cout << std::hex << buf << std::endl;
    buf = SWAP_BYTES(buf);

    // 0V = 0d
    // Vref = 4095d
    // XV = 3102d (example) --> Code * 3.30000 / 4095

    std::cout << (buf >> 4) << std::endl;
    *value = (float)(buf >> 4) / 2047.0 * 4.096000;

    if (res != 0)
        return -2;

    return 0;
}

int ADS1015::Configure_ADC(const int OS,
                           const int channel,
                           const int gain,
                           const int mode,
                           const int sampling_frequency,
                           const int comparator_mode,
                           const int comparator_polarity,
                           const int comparator_latching,
                           const int comparator_queue)
{
    if ((channel > ADC_CHANNEL_3) | (channel < ADC_CHANNEL_0))
        return -1;
    if ((gain > ADC_GAIN_0V25) | (gain < ADC_GAIN_6V00))
        return -2;
    if ((sampling_frequency > ADC_SPS_3300) | (sampling_frequency < ADC_SPS_128))
        return -3;
    if ((comparator_queue < 0x00) | (comparator_queue > 0x03))
        return -4;

    // Copying the value for futures internals calls.
    this->ActualGain = gain;
    this->ActualMode = mode;
    this->ActualChannel = channel;
    this->ActualSampling = sampling_frequency;
    this->ActualComparator_mode = comparator_mode;
    this->ActualComparator_queue = comparator_queue;
    this->ActualComparator_polarity = comparator_polarity;
    this->ActualComparator_latching = comparator_latching;

    int buf = 0;
    int res = 0;

    // MSB
    buf = (bool)OS;
    buf = (buf << 3) | channel;
    buf = (buf << 3) | gain;
    buf = (buf << 1) | (bool)mode;

    // LSB
    buf = (buf << 3) | sampling_frequency;
    buf = (buf << 1) | (bool)comparator_mode;
    buf = (buf << 1) | (bool)comparator_polarity;
    buf = (buf << 1) | (bool)comparator_latching;
    buf = (buf << 2) | comparator_queue;

    res = I2C_Write(&this->I2C, this->address, CONFIG_REGISTER, &buf, 1, 2);

    if (res != 0)
        return -5;
    return 0;
}

int ADS1015::ConfigureLowThreshold(const float Value)
{
    if ((Value < 0.0) | (Value > this->ReferenceVoltage))
        return -1;
    if (Value > this->HighThreshold)
        return -1;

    this->LowThreshold = Value;

    int buf = 0;
    int res = 0;
    int temp = (int)floor((Value * 4095) / this->ReferenceVoltage) << 4;

    buf = temp & 0xFFFF;

    res = I2C_Write(&this->I2C, this->address, LOW_TRESHOLD_REGISTER, &buf, 1, 2);

    if (res != 0)
        return -2;
    return 0;
}
int ADS1015::ConfigureHighThreshold(const float Value)
{
    if ((Value < 0.0) | (Value > this->ReferenceVoltage))
        return -1;
    if (Value < this->LowThreshold)
        return -1;

    this->HighThreshold = Value;

    int buf = 0;
    int res = 0;
    int temp = (int)floor((Value * 4095) / this->ReferenceVoltage) << 4;

    buf = temp & 0xFFFF;

    res = I2C_Write(&this->I2C, this->address, HIGH_THRESHOLD_REGISTER, &buf, 1, 2);

    if (res != 0)
        return -2;
    return 0;
}
