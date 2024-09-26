/**
 * @file ADS1015.hpp
 * @author l.heywang
 * @brief Define a class and functions to exploit the ADS1015 ADC.
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

// prevent multiple include
#pragma once

// type include
#include <cstdint>
#include "../../I2C/I2C.hpp"

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

#define DS1882_DATA_SIZE 8 // 8b register here

#define CONVERSION_REGISTER 0x00
#define CONFIG_REGISTER 0x01
#define LOW_TRESHOLD_REGISTER 0x02
#define HIGH_THRESHOLD_REGISTER 0x03

// ==============================================================================
// IC VARIOUS DEFINE
// ==============================================================================
// Single ended channels, as we're using them
#define CHANNEL_0 0x04
#define CHANNEL_1 0x05
#define CHANNEL_2 0x06
#define CHANNEL_3 0x07

#define GAIN_6V00 0x00
#define GAIN_4V00 0x01
#define GAIN_2V00 0x02
#define GAIN_1V00 0x03
#define GAIN_0V50 0x04
#define GAIN_0V25 0x07

#define SPS_128 0x00
#define SPS_250 0x01
#define SPS_490 0x02
#define SPS_920 0x03
#define SPS_1600 0x04
#define SPS_2400 0x05
#define SPS_3300 0x07

// ==============================================================================
// IC CLASS FUNCTIONS
// ==============================================================================

/**
 * @brief Class for exploiting the ADS1015 ADC from Texas Instruments connected to the I2C Bus.
 *
 */
class ADS1015
{
private:
    uint8_t address = 0x00;

public:
    /**
     * @brief Construct a new ADS1015 object
     *
     * @param[in] int &address The address of the IC on the I2C bus
     */
    ADS1015(int address);

    /**
     * @brief Destroy the ADS1015 object
     *
     */
    ~ADS1015();

    // Methods
    /**
     * @brief Return the value in volt for the selected channel. This function take a bit of time to execute.
     *
     * @param[in] int channel (int) : The channel selected.
     * @param[out] value (float*) : A pointer to a float to store the output value
     *
     * @return (int) : 0 : Everything went fine !
     * @return (int) : -1 : Channel set is under the minimum value
     * @return (int) : -2 : Channel set is over the maximum value
     * @return (int) : -3 : value pointer incorrect
     */
    int Read_Voltage(int channel, float *value);

    /**
     * @brief Configure the ADC operation mode
     *
     * @param[in] channel (int) : Selected channel. Will be overwritten by reading functions
     * @param[in] gain  (int) : Gain of the PGA
     * @param[in] mode (int) : Operation mode
     * @param[in] sampling_frequency (int)
     * @param[in] comparator_mode (int)
     * @param[in] comparator_polarity (int)
     * @param[in] comparator_latching (int)
     * @param[in] comparator_queue (int)
     *
     * @return (int) : 0 if everything went fine, <0 otherwise.
     */
    int Configure_ADC(int channel = CHANNEL_0, int gain = GAIN_4V00, int mode = 1, int sampling_frequency = SPS_920, int comparator_mode = 0, int comparator_polarity = 1, int comparator_latching = 1, int comparator_queue = 0);
};