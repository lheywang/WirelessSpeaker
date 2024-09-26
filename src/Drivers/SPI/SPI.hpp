/**
 * @file SPI.hpp
 * @brief Define the SPI Class, which is only used to store paramters onto the EEPROM.
 * @author l.heywang
 *
 */

// Only included one time
#pragma once

// Libs
#include <iostream>
#include <cstdint>

/**
 * @brief This struct store all of the elements to be configured once, and restored after each POR event.
 *        Values that are immutable arent stored here.
 *        All of theses settings are saved onto an SPI EEPROM.
 *
 */
struct Config
{
    std::string Speaker_Name;   /*!< The Name of the Speaker. Used as simple identifier.*/
    std::string Board_Revision; /*!< Field that cannot be edited. Contain the board revision indication.*/
    std::string Board_Variant;  /*!< Field that cannot be edited. Contain the board minor variants (BOM).*/

    /**
     * @brief Structure that contain all of the Audio settings.
     *
     * @struct Config::Audio::Trebbles
     *         Structure that contain all of the settings relative to the Trebbles.
     *         Configure the cutdown frequency for the low cutoff frequency played on theses speakers.
     *         Configure the gain for this frequency range.
     *         Thus, both can be used as a mixer.
     * @struct Config::Audio::Medium
     *         Structure that contain all of the settings relative to the Mediums.
     *         Configure the cutdown frequency for the low and high cutoff frequencies played on theses speakers.
     *         Configure the gain for this frequency range.
     *         Thus, both can be used as a mixer.
     * @struct Config::Audio::Bass
     *         Structure that contain all of the settings relative to the Bass.
     *         Configure the cutdown frequency for the high cutoff frequency played on theses speakers.
     *         Configure the gain for this frequency range.
     *         Thus, both can be used as a mixer.
     * @struct Config::Audio::DAC
     *         Structure that contain all of the settings relative to the Digital to Analog Conversion.
     *         Configure paramters such as the frequency base played (44.1 kHz or 48 kHz).
     *         Configure user selectable settings such as automute or independant volume control per channel.
     * @struct Config::Audio::Global
     *         Structure that contain all of the settings relative to the Global Analog Audio domain.
     *         Store parameters that are global to the audio chain, such as the R-L balance or Analog Volume 2
     *
     */
    struct Audio
    {
        /**
         * @var Config::Audio::Trebbles::HP_Value
         *      Value of the potentiometer that is used to set the high pass point for the trebbles speaker.
         * @var Config::Audio::Trebbles::Gain
         *      Value of the potentiometer that is used to set the gain on the trebbles specically.
         *
         */
        struct Trebbles
        {
            uint8_t HP_Value;
            uint8_t Gain;
        } Trebbles;

        /**
         * @var Config::Audio::Medium::LP_Value
         *      Value of the potentiometer that is used to set the low pass point for the mediums speaker.
         * @var Config::Audio::Medium::HP_Value
         *      Value of the potentiometer that is used to set the high pass point for the mediums speaker.
         * @var Config::Audio::Medium::Gain
         *      Value of the potentiometer that is used to set the gain on the mediums specically.
         *
         */
        struct Medium
        {
            uint8_t LP_Value;
            uint8_t HP_Value;
            uint8_t Gain;
        } Medium;

        /**
         * @var Config::Audio::Bass::LP_Value
         *      Value of the potentiometer that is used to set the low pass point for the bass speaker.
         * @var Config::Audio::Bass::Gain
         *      Value of the potentiometer that is used to set the gain on the bass specically.
         *
         */
        struct Bass
        {
            uint8_t LP_Value;
            uint8_t Gain;
        } Bass;

        /**
         * @var Config::Audio::Global::Volume
         *      Analog gain for the volume. Used as master volume.
         *
         */
        struct Global
        {
            uint8_t Volume;
        } Global;

        /**
         * @var Config::Audio::DAC::Audio_44k
         *      Boolean that is set to True of the settings for the PLL need to be set to 44.1kHz playback. Will be overhiden by the 48k setting.
         * @var Config::Audio::DAC::Audio_48k
         *      Boolean that is set to True of the settings for the PLL need to be set to 48kHz playback. Will overhide by the 48k setting.
         * @var Config::Audio::DAC::Automute_delay
         *      Delay of 0 to be shown at the I2S data input before triggering the Automute system, and thus reducing power draw.
         * @var Config::Audio::DAC::Global_Volume
         *      Global Digital Volume. Shall always be near the maximum to exploit the biggest dynamic range.
         * @var Config::Audio::DAC::Left_Volume
         *      Analog volume settings for the left channel. Used to balance both channels.
         * @var Config::Audio::DAC::Right_Volume
         *      Analog volume settings for the rigth channel. Used to balance both channels.
         */
        struct DAC
        {
            bool Audio_44k;
            bool Audio_48k;

            uint8_t Automute_delay;
            uint8_t Global_Volume;
            uint8_t Left_Volume;
            uint8_t Right_Volume;
        } DAC;

    } Audio;

    /**
     * @brief Structure that contain all of the LEDS setings.
     *        Store the brightness values.
     *        Store the group configuration values.
     *
     * @var Config::LEDS::Brightness
     *      The maximal brightness of the leds. Some inferior levels will be indexed from it.
     *
     */
    struct LEDS
    {
        uint8_t Brightness;
    } LEDS;

    /**
     *  @brief Structure that contain all of the Capacitive Sensor Settings such as the sensivity or the threshold values.
     *
     * @var Config::Capacitive::Threshold
     *      Contain the value of the peak that need to be measured to be considered as a touch.
     * @var Config::Capacitive::Sensivity
     *      Contain the value of the number of consecutive touch to be measured before considering the touch valid.
     *
     */
    struct Capacitive
    {
        uint8_t Threshold;
        uint8_t Sensivity;

    } Capacitive;

    /**
     * @brief Structure that contain all of the Temperature monitoring settings,
     *        and more precisely the values of the Interrupts at which an action shall be triggered (overheat ?)
     *
     * @var Config::Temperature::Maximal_Temperature
     *      Maximal Temperature that is accepted.
     * @var Config::Temperature::Minimal_Temperature
     *      Minimal Temperature that is accepted.
     *
     */
    struct Temperature
    {
        uint16_t Maximal_Temperature;
        uint16_t Minimal_Temperature;
    } Temperature;
};
