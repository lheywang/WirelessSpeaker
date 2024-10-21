/**
 * @file ADS1015.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source for the ADS1015 ADC.
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 * @remark Class was tested successfully on 07/10/2024.
 *
 */
// Header file
#include "ADS1015.hpp"

// Cpp modules
#include <cstdint>
#include <math.h>
#include <unistd.h>

#include <iostream>

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

constexpr int CONVERSION_REGISTER = 0x00;
constexpr int CONFIG_REGISTER = 0x01;
constexpr int LOW_TRESHOLD_REGISTER = 0x02;
constexpr int HIGH_THRESHOLD_REGISTER = 0x03;

// =====================
// PRIVATES FUNCTIONS
// =====================

static constexpr float GetMutliplier(ADC_RANGE Input)
{
    switch(Input)
    {
    case ADC_RANGE::FS0V25:
        return 0.256000;
    case ADC_RANGE::FS0V50:
        return 0.512000;
    case ADC_RANGE::FS1V00:
        return 1.024000;
    case ADC_RANGE::FS2V00:
        return 2.048000;
    case ADC_RANGE::FS4V00:
        return 4.096000;
    case ADC_RANGE::FS6V00:
        return 6.144000;
    }
    return 0.0;
}

// =====================
// CONSTRUCTORS
// =====================

ADS1015::ADS1015(const I2C_Bus* I2C, const VOLTAGE_MONITOR address)
{
    this->address = (uint8_t)address;
    this->I2C = *I2C;

    this->LowThreshold = 0.0;
    this->ActualGain = ADC_RANGE::FS2V00;
    this->ActualMode = 0x01;
    this->ActualChannel = ADC_CHANNELS::CHANNEL_0;
    this->ActualSampling = ADC_SAMPLES::SPS_1600;
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

int ADS1015::Read_Voltage(const ADC_CHANNELS channel, float* const value)
{
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

    /*
    This block of code compute the delay to wait until the the delta-sigma has finished it's job.
    I'm using an empiric method to compute them since the original version didn't want (why ? We'll never know...)

    The idea is to divide with aconstexpr intd factor at each iteration to compute the right value.
    This factor is 1.7. It may be smaller, this does'nt affect the behavior. If greater, the faster settings won't match the data availability.

    The validity of this settings has been done on Microsoft Excel.
    The base setting assume of at least 2* margin from the minimal time reported to the waited time.
    */
    int microseconds = 15625;
    for(int i = 0; i < (int)this->ActualSampling; i++)
    {
        microseconds = round(microseconds / 1.7);
    }
    usleep(microseconds);

    res += I2C_Read(&this->I2C, this->address, CONVERSION_REGISTER, &buf, 1, 2);
    buf = SWAP_BYTES(buf);

    if(res != 0)
        return -1;

    float multiplier = GetMutliplier(this->ActualGain);

    // 2047 is the code for full range !
    *value = (float)(buf >> 4) / 2047.0 * multiplier;

    return 0;
}

int ADS1015::Configure_ADC(const int OS,
                           const ADC_CHANNELS channel,
                           const ADC_RANGE gain,
                           const int mode,
                           const ADC_SAMPLES sampling_frequency,
                           const int comparator_mode,
                           const int comparator_polarity,
                           const int comparator_latching,
                           const int comparator_queue)
{
    if((comparator_queue < 0x00) | (comparator_queue > 0x03))
        return -1;

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
    buf = (buf << 3) | (int)channel;
    buf = (buf << 3) | (int)gain;
    buf = (buf << 1) | (bool)mode;

    // LSB
    buf = (buf << 3) | (int)sampling_frequency;
    buf = (buf << 1) | (bool)comparator_mode;
    buf = (buf << 1) | (bool)comparator_polarity;
    buf = (buf << 1) | (bool)comparator_latching;
    buf = (buf << 2) | comparator_queue;

    buf = SWAP_BYTES(buf);
    res = I2C_Write(&this->I2C, this->address, CONFIG_REGISTER, &buf, 1, 2);

    if(res != 0)
        return -2;
    return 0;
}

int ADS1015::ConfigureLowThreshold(const float Value)
{
    if((Value < 0.0) | (Value > 3.300))
        return -1;
    if(Value > this->HighThreshold)
        return -1;

    this->LowThreshold = Value;

    int buf = 0;
    int res = 0;

    float multiplier = GetMutliplier(this->ActualGain);

    int temp = ((int)round((Value / multiplier) * 2047)) >> 4;
    buf = temp & 0xFFFF;

    buf = SWAP_BYTES(buf);
    res = I2C_Write(&this->I2C, this->address, LOW_TRESHOLD_REGISTER, &buf, 1, 2);

    if(res != 0)
        return -2;
    return 0;
}
int ADS1015::ConfigureHighThreshold(const float Value)
{
    if((Value < 0.0) | (Value > 3.300))
        return -1;
    if(Value < this->LowThreshold)
        return -1;

    this->HighThreshold = Value;

    int buf = 0;
    int res = 0;

    float multiplier = GetMutliplier(this->ActualGain);

    int temp = ((int)round((Value / multiplier) * 2047)) >> 4;
    buf = temp & 0xFFFF;

    buf = SWAP_BYTES(buf);
    res = I2C_Write(&this->I2C, this->address, HIGH_THRESHOLD_REGISTER, &buf, 1, 2);

    if(res != 0)
        return -2;
    return 0;
}
