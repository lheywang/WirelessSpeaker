/**
 * @file ADS1015.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define a class and functions to exploit the ADS1015 ADC.
 * @version 1.0
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
// IC VARIOUS DEFINE
// ==============================================================================

/*! Define values for the ADC channels */
enum class ADC_CHANNELS
{
    CHANNEL_0 = 0x04, /*!< First single ended channel*/
    CHANNEL_1 = 0x05, /*!< Second single ended channel */
    CHANNEL_2 = 0x06, /*!< Third single ended channel */
    CHANNEL_3 = 0x07, /*!< Fourth single ended channel */
};

/*! Define values for the ADC Ranges */
enum class ADC_RANGE
{
    FS6V00 = 0x00, /*!< +-6.144 V range*/
    FS4V00 = 0x01, /*!< +-4.096 V range*/
    FS2V00 = 0x02, /*!< +-2.048 V range*/
    FS1V00 = 0x03, /*!< +-1.024 V range*/
    FS0V50 = 0x04, /*!< +-0.512 V range*/
    FS0V25 = 0x07, /*!< +-0.256 V range*/
};

/*! Define values for the ADC sampling frequency*/
enum class ADC_SAMPLES
{
    SPS_128 = 0x00,  /*!< 128  samples per second*/
    SPS_250 = 0x01,  /*!< 250  samples per second*/
    SPS_490 = 0x02,  /*!< 490  samples per second*/
    SPS_920 = 0x03,  /*!< 920  samples per second*/
    SPS_1600 = 0x04, /*!< 1600 samples per second*/
    SPS_2400 = 0x05, /*!< 2400 samples per second*/
    SPS_3300 = 0x06, /*!< 3300 samples per second*/
};

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

    ADC_SAMPLES ActualSampling;
    ADC_CHANNELS ActualChannel;
    ADC_RANGE ActualGain;
    int ActualMode;
    int ActualComparator_mode;
    int ActualComparator_polarity;
    int ActualComparator_latching;
    int ActualComparator_queue;

    float HighThreshold;
    float LowThreshold;

public:
    /**
     * @brief Construct a new ADS1015 object
     *
     * @param[in] I2C A pointer to the I2C struct that is used to handle IO operation on this bus.
     * @param[in] address The address of the IC on the I2C bus
     */
    ADS1015(const I2C_Bus *I2C, const VOLTAGE_MONITOR address);

    /**
     * @brief Destroy the ADS1015 object
     *
     */
    ~ADS1015();

    /**
     * @brief Read back the seen value on the selected input.
     * @warning This function block the code execution for a 2/Fsampling (between 60us and 15ms, depending on the settings).
     * @warning The function use float computation, and thus return a number which may be very long. From experience, after the second (or maybe third) value, the number may be signifiant anymore.
     *
     * @param[in] channel The selected channel
     * @param[out] value The value converted in volts.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int Read_Voltage(const ADC_CHANNELS channel, float *const value);

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
     * @param[in] comparator_queue Number of assersions before triggering a flag. (0 - 3)
     *
     * @return  0 : OK
     * @return -1 : Invalid Comparator Queue
     * @return -2 : IOCTL error.
     *
     */
    int Configure_ADC(const int OS,
                      const ADC_CHANNELS channel,
                      const ADC_RANGE gain,
                      const int mode,
                      const ADC_SAMPLES sampling_frequency,
                      const int comparator_mode,
                      const int comparator_polarity,
                      const int comparator_latching,
                      const int comparator_queue);

    /**
     * @brief Configure the low threshold value to trigger an interrupt.
     *
     * @param Value The value to trigger in volts.
     * @warning The configured value is relative to the seen binary code.
     *          When PGA settings are modified, this value shall be also edited.
     *
     * @return  0 : OK
     * @return -1 : Invalid Value.
     * @return -2 : IOCTL error.
     */
    int ConfigureLowThreshold(const float Value);

    /**
     * @brief Configure the low threshold value to trigger an interrupt.
     * @warning The configured value is relative to the seen binary code.
     *          When PGA settings are modified, this value shall be also edited.
     *
     * @param Value The value to trigger in volts.
     *
     * @return  0 : OK
     * @return -1 : Invalid Value.
     * @return -2 : IOCTL error.
     *
     */
    int ConfigureHighThreshold(const float Value);
};