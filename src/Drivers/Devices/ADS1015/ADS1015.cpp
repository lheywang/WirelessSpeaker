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
    if ((channel > CHANNEL_3) | (channel < CHANNEL_0))
        return -1;

    int buf[2] = {0};
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
    case SPS_128:
        microseconds = 15625; // (1 / 128Hz) * 2 in microseconds.
        break;
    case SPS_250:
        microseconds = 8000; // (1 / 250Hz) * 2 in microseconds.
        break;
    case SPS_490:
        microseconds = 4081; // (1 / 490Hz) * 2 in microseconds.
        break;
    case SPS_920:
        microseconds = 2173; // (1 / 920Hz) * 2 in microseconds.
        break;
    case SPS_1600:
        microseconds = 1250; // (1 / 1.6kHz) * 2 in microseconds.
        break;
    case SPS_2400:
        microseconds = 833; // (1 / 2.4kHz) * 2 in microseconds.
        break;
    case SPS_3300:
        microseconds = 606; // (1 / 3.3kHz) * 2 in microseconds.
        break;
    }

    // Wait until the conversion has finished (2* margin is already applied)
    usleep(microseconds);

    res += I2C_Read(&this->I2C, this->address, CONVERSION_REGISTER, buf, 2);

    int temp = (buf[0] << 4) | (buf[1] >> 4);
    // 0V = 0d
    // Vref = 4095d
    // XV = 3102d (example) --> Code * 3.30000 / 4095

    *value = (temp * this->ReferenceVoltage) / 4095;

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
    if ((channel > CHANNEL_3) | (channel < CHANNEL_0))
        return -1;
    if ((gain > GAIN_0V25) | (gain < GAIN_6V00))
        return -2;
    if ((sampling_frequency > SPS_3300) | (sampling_frequency < SPS_128))
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

    int buf[2] = {0};
    int res = 0;

    // MSB
    buf[0] = (bool)OS;
    buf[0] = (buf[0] << 1) | channel;
    buf[0] = (buf[0] << 3) | gain;
    buf[0] = (buf[0] << 3) | (bool)mode;

    // LSB
    buf[1] = sampling_frequency;
    buf[1] = (buf[1] << 3) | (bool)comparator_mode;
    buf[1] = (buf[1] << 1) | (bool)comparator_polarity;
    buf[1] = (buf[1] << 1) | (bool)comparator_latching;
    buf[1] = (buf[1] << 2) | comparator_queue;

    res = I2C_Write(&this->I2C, this->address, CONFIG_REGISTER, buf, 2);

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

    int buf[2] = {0};
    int res = 0;
    int temp = (int)floor((Value * 4095) / this->ReferenceVoltage) << 4;

    buf[0] = temp & 0xFF00;
    buf[1] = temp & 0x00F0;

    res = I2C_Write(&this->I2C, this->address, LOW_TRESHOLD_REGISTER, buf, 2);

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

    int buf[2] = {0};
    int res = 0;
    int temp = (int)floor((Value * 4095) / this->ReferenceVoltage) << 4;

    buf[0] = temp & 0xFF00;
    buf[1] = temp & 0x00F0;

    res = I2C_Write(&this->I2C, this->address, HIGH_THRESHOLD_REGISTER, buf, 2);

    if (res != 0)
        return -2;
    return 0;
}
