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
    uint8_t address;
    I2C_Bus I2C;

    int ActualSampling;
    int ActualChannel;
    int ActualGain;
    int ActualMode;
    int ActualComparator_mode;
    int ActualComparator_polarity;
    int ActualComparator_latching;
    int ActualComparator_queue;

    float ReferenceVoltage;
    float HighThreshold;
    float LowThreshold;

public:
    /**
     * @brief Construct a new ADS1015 object
     *
     * @param[in] I2C A pointer to the I2C struct that is used to handle IO operation on this bus.
     * @param[in] address The address of the IC on the I2C bus
     */
    ADS1015(const I2C_Bus *I2C, const int address);

    /**
     * @brief Destroy the ADS1015 object
     *
     */
    ~ADS1015();

    /**
     * @brief Define the upper reference of voltage used to compute the real value.
     *        Ideally, this value shall be measured with a DMM.
     *        By default to 3.300000V.
     *
     * @param Reference The value.
     *
     * @return  0 : OK
     */
    int ConfigureVoltageReference(const float Reference);

    /**
     * @brief Read back the seen value on the selected input.
     *        Warning : This function is blocking the software for a period of 2/Fsampling to ensure that the data is ready.
     *
     * @param[in] channel The selected channel
     * @param[out] value The value converted in volts.
     *
     * @return  0 : OK
     * @return -1 : Invalid Channel
     * @return -2 : IOCTL error.
     */
    int Read_Voltage(const int channel, float *const value);

    /**
     * @brief Configure the operation mode of the ADC.
     *
     * @param[in] OS Status of the conversion. Write a 1 to start conversion.
     * @param[in] channel Selection of the channel (0-3)
     * @param[in] gain Selection of the gain (0-7)
     * @param[in] mode Selection of the mode (1 for single shot, 0 for continous.)
     * @param[in] sampling_frequency Selection of the sampling frequency(0-7 -> See datasheet)
     * @param[in] comparator_mode Mode of the comparator (0 : Classic, 1 : windowed)
     * @param[in] comparator_polarity Polarity of the alert pin. (1 : Active high, 0 : active low)
     * @param[in] comparator_latching Does an alert need to be cleared by software ?(1 to enable)
     * @param[in] comparator_queue Number of assersions before triggering a flag.
     *
     * @return  0 : OK
     * @return -1 : Invalid Channel
     * @return -2 : Invalid Gain
     * @return -3 : Invalid sampling frequency
     * @return -4 : Invalid Comparator Queue
     * @return -5 : IOCTL error.
     *
     */
    int Configure_ADC(const int OS,
                      const int channel,
                      const int gain,
                      const int mode,
                      const int sampling_frequency,
                      const int comparator_mode,
                      const int comparator_polarity,
                      const int comparator_latching,
                      const int comparator_queue);

    /**
     * @brief Configure the low threshold value to trigger an interrupt.
     *
     * @param Value The value to trigger in volts.
     *              Warning : This value is relative to the PGA settings and the input.
     *
     * @return  0 : OK
     * @return -1 : Invalid Value.
     * @return -2 : IOCTL error.
     *
     */
    int ConfigureLowThreshold(const float Value);

    /**
     * @brief Configure the low threshold value to trigger an interrupt.
     *
     * @param Value The value to trigger in volts.
     *              Warning : This value is relative to the PGA settings and the input.
     *
     * @return  0 : OK
     * @return -1 : Invalid Value.
     * @return -2 : IOCTL error.
     *
     */
    int ConfigureHighThreshold(const float Value);
};