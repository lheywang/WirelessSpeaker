/**
 * @file Audio_Struct.hpp
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
 * @var Trebbles::HP_Value Value of the potentiometer that is used to set the high pass point for the trebbles speaker.
 * @var Trebbles::Gain Value of the potentiometer that is used to set the gain on the trebbles specically.
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
 * @var Medium::LP_Value Value of the potentiometer that is used to set the low pass point for the mediums speaker.
 * @var Medium::HP_Value Value of the potentiometer that is used to set the high pass point for the mediums speaker.
 * @var Medium::Gain Value of the potentiometer that is used to set the gain on the mediums specically.
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
 * @var Bass::LP_Value Value of the potentiometer that is used to set the low pass point for the bass speaker.
 * @var Bass::Gain Value of the potentiometer that is used to set the gain on the bass specically
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
 * @var Global::Volume Analog gain for the volume. Used as master volume.
 * @var Global::RL_eq Difference of gain between channels. Used to compensate mismatchs on the analog chain.
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
 * @var DAC::Audio_44k Boolean that is set to True of the settings for the PLL need to be set to 44.1kHz playback. Will be overhiden by the 48k setting.
 * @var DAC::Audio_48k Boolean that is set to True of the settings for the PLL need to be set to 48kHz playback. Will overhide by the 48k setting.
 *
 * @var DAC::Automute_delay Delay of 0 to be shown at the I2S data input before triggering the Automute system, and thus reducing power draw.
 * @var DAC::Global_Volume Global Digital Volume. Shall always be near the maximum to exploit the biggest dynamic range.
 * @var DAC::Left_Volume Analog volume settings for the left channel. Used to balance both channels.
 * @var DAC::Right_Volume Analog volume settings for the rigth channel. Used to balance both channels.
 *
 * @var DAC::LeftDataPath Select the data that is used by the left DAC
 * @var DAC::RightDataPath Select the data that is used by the right DAC
 *
 * @var DAC::RampDownSpeed Select the speed when going in Digital Mute
 * @var DAC::RampUpSpeed Select the speed when going in Playback
 * @var DAC::EmergencyRampSpeed Select the speed when going in Mute in case of Power Loss
 * @var DAC::RampDownStep Select the step size (influe on speed) when going in Digital Mute
 * @var DAC::RampUpStep Select the step size (influe on speed) when going in Playback
 * @var DAC::EmergencyRampStep Select the step size (influe on speed) when going in Mute in case of Power Loss
 *
 * @var DAC::LeftAnalogAtten Enable a -6dB attenuation on the left side
 * @var DAC::RightAnalogAtten Enable a -6dB attenuation on the right side
 * @var DAC::LeftAnalogBoost Enable an analog boost on the left side
 * @var DAC::RightAnalogBoost Enable an analog boost on the right side.
 *
 * @var DAC::DSP_BufferA_values1 DSP Coefficients Buffer A values for program 1
 * @var DAC::DSP_BufferA_values2 DSP Coefficients Buffer A values for program 2
 * @var DAC::DSP_BufferA_values3 DSP Coefficients Buffer A values for program 3
 * @var DAC::DSP_BufferA_values4 DSP Coefficients Buffer A values for program 4
 * @var DAC::DSP_BufferA_values5 DSP Coefficients Buffer A values for program 5
 * @var DAC::DSP_BufferA_values6 DSP Coefficients Buffer A values for program 6
 *
 * @var DAC::DSP_BufferB_values1 DSP Coefficients Buffer B values for program 1
 * @var DAC::DSP_BufferB_values2 DSP Coefficients Buffer B values for program 2
 * @var DAC::DSP_BufferB_values3 DSP Coefficients Buffer B values for program 3
 * @var DAC::DSP_BufferB_values4 DSP Coefficients Buffer B values for program 4
 * @var DAC::DSP_BufferB_values5 DSP Coefficients Buffer B values for program 5
 * @var DAC::DSP_BufferB_values6 DSP Coefficients Buffer B values for program 6
 *
 * @var DAC::DSP_Intr_values1 DSP Instruction Buffer for program 1
 * @var DAC::DSP_Intr_values2 DSP Instruction Buffer for program 2
 * @var DAC::DSP_Intr_values3 DSP Instruction Buffer for program 3
 * @var DAC::DSP_Intr_values4 DSP Instruction Buffer for program 4
 * @var DAC::DSP_Intr_values5 DSP Instruction Buffer for program 5
 * @var DAC::DSP_Intr_values6 DSP Instruction Buffer for program 6
 */
struct DAC
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
 * @var AMP::PowerLimit Define the power limit for this AMP. Used to reduce current needs.
 */
struct AMP
{
    uint8_t PowerLimit;
};