/**
 * @file struct_audio_elements.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define audio structures subelements.
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
 * @struct Trebbles
 * @brief Define trebbles analog settings.
 *
 * @param Trebbles::HP_Value Value of the potentiometer that is used to set the high pass point for the trebbles speaker.
 * @param Trebbles::Gain Value of the potentiometer that is used to set the gain on the trebbles specically.
 */
struct Trebbles
{
    uint8_t HP_Value;
    uint8_t Gain;
};

/**
 * @struct Medium
 * @brief Define mediums analog settings.
 *
 * @param Medium::LP_Value Value of the potentiometer that is used to set the low pass point for the mediums speaker.
 * @param Medium::HP_Value Value of the potentiometer that is used to set the high pass point for the mediums speaker.
 * @param Medium::Gain Value of the potentiometer that is used to set the gain on the mediums specically.
 *
 */
struct Medium
{
    uint8_t LP_Value;
    uint8_t HP_Value;
    uint8_t Gain;
};

/**
 * @struct Bass
 * @brief Define BASS Related settings
 *
 * @param Bass::LP_Value Value of the potentiometer that is used to set the low pass point for the bass speaker.
 * @param Bass::Gain Value of the potentiometer that is used to set the gain on the bass specically
 */
struct Bass
{
    uint8_t LP_Value;
    uint8_t Gain;
};

/**
 * @struct Global
 * @brief Define Global Audio settings
 *
 * @param Global::Volume Analog gain for the volume. Used as master volume.
 * @param Global::RL_eq Difference of gain between channels. Used to compensate mismatchs on the analog chain.
 */
struct Global
{
    uint8_t Volume;
    uint8_t RL_eq;
};

#define MAX_COEFF 256
#define MAX_INSTR 1024

/**
 * @struct DAC
 * @brief Define DAC Settings
 *
 * @warning Buffers values remains stored on the system files since they'r e too big to a 256k EEPROM.
 *
 * @param DAC_Config::Audio_44k Boolean that is set to True of the settings for the PLL need to be set to 44.1kHz playback. Will be overhiden by the 48k setting.
 * @param DAC_Config::Audio_48k Boolean that is set to True of the settings for the PLL need to be set to 48kHz playback. Will overhide by the 48k setting.
 *
 * @param DAC_Config::Automute_delay Delay of 0 to be shown at the I2S data input before triggering the Automute system, and thus reducing power draw.
 * @param DAC_Config::Global_Volume Global Digital Volume. Shall always be near the maximum to exploit the biggest dynamic range.
 * @param DAC_Config::Left_Volume Analog volume settings for the left channel. Used to balance both channels.
 * @param DAC_Config::Right_Volume Analog volume settings for the rigth channel. Used to balance both channels.
 *
 * @param DAC_Config::LeftDataPath Select the data that is used by the left DAC
 * @param DAC_Config::RightDataPath Select the data that is used by the right DAC
 *
 * @param DAC_Config::RampDownSpeed Select the speed when going in Digital Mute
 * @param DAC_Config::RampUpSpeed Select the speed when going in Playback
 * @param DAC_Config::EmergencyRampSpeed Select the speed when going in Mute in case of Power Loss
 * @param DAC_Config::RampDownStep Select the step size (influe on speed) when going in Digital Mute
 * @param DAC_Config::RampUpStep Select the step size (influe on speed) when going in Playback
 * @param DAC_Config::EmergencyRampStep Select the step size (influe on speed) when going in Mute in case of Power Loss
 *
 * @param DAC_Config::LeftAnalogAtten Enable a -6dB attenuation on the left side
 * @param DAC_Config::RightAnalogAtten Enable a -6dB attenuation on the right side
 * @param DAC_Config::LeftAnalogBoost Enable an analog boost on the left side
 * @param DAC_Config::RightAnalogBoost Enable an analog boost on the right side.
 *
 * @param DAC_Config::DSP_BufferA_values1 DSP Coefficients Buffer A values for program 1
 * @param DAC_Config::DSP_BufferA_values2 DSP Coefficients Buffer A values for program 2
 * @param DAC_Config::DSP_BufferA_values3 DSP Coefficients Buffer A values for program 3
 * @param DAC_Config::DSP_BufferA_values4 DSP Coefficients Buffer A values for program 4
 * @param DAC_Config::DSP_BufferA_values5 DSP Coefficients Buffer A values for program 5
 * @param DAC_Config::DSP_BufferA_values6 DSP Coefficients Buffer A values for program 6
 *
 * @param DAC_Config::DSP_BufferB_values1 DSP Coefficients Buffer B values for program 1
 * @param DAC_Config::DSP_BufferB_values2 DSP Coefficients Buffer B values for program 2
 * @param DAC_Config::DSP_BufferB_values3 DSP Coefficients Buffer B values for program 3
 * @param DAC_Config::DSP_BufferB_values4 DSP Coefficients Buffer B values for program 4
 * @param DAC_Config::DSP_BufferB_values5 DSP Coefficients Buffer B values for program 5
 * @param DAC_Config::DSP_BufferB_values6 DSP Coefficients Buffer B values for program 6
 *
 * @param DAC_Config::DSP_Intr_values1 DSP Instruction Buffer for program 1
 * @param DAC_Config::DSP_Intr_values2 DSP Instruction Buffer for program 2
 * @param DAC_Config::DSP_Intr_values3 DSP Instruction Buffer for program 3
 * @param DAC_Config::DSP_Intr_values4 DSP Instruction Buffer for program 4
 * @param DAC_Config::DSP_Intr_values5 DSP Instruction Buffer for program 5
 * @param DAC_Config::DSP_Intr_values6 DSP Instruction Buffer for program 6
 */
struct DAC_Config
{
    bool Audio_44k;
    bool Audio_48k;

    uint8_t Automute_delay;
    uint8_t Global_Volume;
    uint8_t Left_Volume;
    uint8_t Right_Volume;

    uint8_t LeftDataPath;
    uint8_t RightDataPath;

    uint8_t RampDownSpeed;
    uint8_t RampUpSpeed;
    uint8_t EmergencyRampSpeed;
    uint8_t RampDownStep;
    uint8_t RampUpStep;
    uint8_t EmergencyRampStep;

    bool LeftAnalogAtten;
    bool RightAnalogAtten;
    bool LeftAnalogBoost;
    bool RightAnalogBoost;

    uint32_t DSP_BufferA_values1[MAX_COEFF];
    uint32_t DSP_BufferB_values1[MAX_COEFF];
    uint32_t DSP_Intr_values1[MAX_INSTR];

    uint32_t DSP_BufferA_values2[MAX_COEFF];
    uint32_t DSP_BufferB_values2[MAX_COEFF];
    uint32_t DSP_Intr_values2[MAX_INSTR];

    uint32_t DSP_BufferA_values3[MAX_COEFF];
    uint32_t DSP_BufferB_values3[MAX_COEFF];
    uint32_t DSP_Intr_values3[MAX_INSTR];

    uint32_t DSP_BufferA_values4[MAX_COEFF];
    uint32_t DSP_BufferB_values4[MAX_COEFF];
    uint32_t DSP_Intr_values4[MAX_INSTR];

    uint32_t DSP_BufferA_values5[MAX_COEFF];
    uint32_t DSP_BufferB_values5[MAX_COEFF];
    uint32_t DSP_Intr_values5[MAX_INSTR];

    uint32_t DSP_BufferA_values6[MAX_COEFF];
    uint32_t DSP_BufferB_values6[MAX_COEFF];
    uint32_t DSP_Intr_values6[MAX_INSTR];
};

/**
 * @struct AMP
 * @brief Define amplifiers settings
 *
 * @param AMP::PowerLimit Define the power limit for this AMP. Used to reduce current needs.
 */
struct AMP
{
    uint8_t PowerLimit;
};