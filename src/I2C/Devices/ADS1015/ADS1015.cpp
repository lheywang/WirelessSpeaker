// ==============================================================================
//                              I2C/Devices/MCP9808/MCP9808.cpp
//                              Wrote by lheywang
//
// Define functions to interface with the IC
// ==============================================================================

// Header file
#include "ADS1015.hpp"

// Cpp modules
#include <cstdint>

// =====================
// CONSTRUCTORS
// =====================

ADS1015::ADS1015(int address)
{
    this->address = (uint8_t)address;
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

int ADS1015::Read_Voltage(int channel, float *value)
{
    // Checking if the channel is within values
    if (channel > CHANNEL_3)
        return -2;
    else if (channel < CHANNEL_0)
        return -1;

    // checking integrity of the output value
    if (value == nullptr)
        return -3;

    // Executing code now

    return 0;
}

int ADS1015::Configure_ADC(int channel, int gain, int mode, int sampling_frequency, int comparator_mode, int comparator_polarity, int comparator_latching, int comparator_queue)
{
    // Checking if the channel is within values
    if (channel > CHANNEL_3)
        return -2;
    if (channel < CHANNEL_0)
        return -1;

    // checking gain settings
    if (gain > GAIN_0V25)
        return -3;
    if (gain < GAIN_6V00)
        return -4;

    // checking sampling frequency
    if (sampling_frequency > SPS_3300)
        return -5;
    if (sampling_frequency < SPS_128)
        return -6;

    // Checking comparator settingd
    if (comparator_queue < 0x00)
        return -7;
    if (comparator_queue > 0x03)
        return -8;

    // All of the remaining settings are used as boolean, thus no security needed, the cast will do it's job by itself

    // Now do some code !
    return 0;
}
