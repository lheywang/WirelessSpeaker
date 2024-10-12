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

/*! Define values that are stored on the EEPROM for the trebbles analog part */
struct Trebbles
{
    uint8_t HP_Value; /*!< The value of the potentiometer that configure the cut point of the high pass filter*/
    uint8_t Gain;     /*!< The value of the potentiometer that configure the gain for the trebbles*/
};

/*! Define values that are stored on the EEPROM for the medium analog part */
struct Medium
{
    uint8_t LP_Value; /*!< The value of the potentiometer that configure the cut point of the low pass filter*/
    uint8_t HP_Value; /*!< The value of the potentiometer that configure the cut point of the high pass filter*/
    uint8_t Gain;     /*!< The value of the potentiometer that configure the gain for the mediums*/
};

/*! Define values that are stored on the EEPROM for the Amplifiers */
struct Bass
{
    uint8_t LP_Value; /*!< The value of the potentiometer that configure the cut point of the low pass filter*/
    uint8_t Gain;     /*!< The value of the potentiometer that configure the gain for the bass*/
};

/*! Define values that are stored on the EEPROM for the overall analog configuration */
struct Global
{
    uint8_t Volume; /*!< Global analog volume*/
    uint8_t RL_eq;  /*!< Right /-/ Left analog equalization*/
};

constexpr int MAX_COEFF = 256;       /*!< Maximal number of coefficients for the DSP*/
constexpr int MAX_INSTR = 1024;      /*!< Maximal number of instructions for the DSP*/
constexpr int MAX_PROFILE_CHAR = 50; /*!< Maximal number of characters in the name of a DSP profile*/

/*! Define values that are stored on the EEPROM for the Amplifiers */
struct DAC_Config
{
    bool Audio_44k; /*!< Take true if playback was a multiple of 44.1 kHz*/
    bool Audio_48k; /*!< Take true if playback was a multiple of 48 kHz*/

    uint8_t Automute_delay; /*!< Value for the automute setting*/
    uint8_t Global_Volume;  /*!< Value for the global digital volume*/
    uint8_t Left_Volume;    /*!< Left specific volume*/
    uint8_t Right_Volume;   /*!< Right specific volume*/

    uint8_t LeftDataPath;  /*!< Left data input selection*/
    uint8_t RightDataPath; /*!< Right data input selection*/

    uint8_t RampDownSpeed;      /*!< Speed to go on mute on automute*/
    uint8_t RampUpSpeed;        /*!< Speed to leaving mute after automute*/
    uint8_t EmergencyRampSpeed; /*!< Speed to go on mute on mute in case of emergency*/
    uint8_t RampDownStep;       /*!< Step size to go on mute on automute*/
    uint8_t RampUpStep;         /*!< Step size to leave mute after automute*/
    uint8_t EmergencyRampStep;  /*!< Step size to go on mute in case of emergency*/

    bool LeftAnalogAtten;  /*!< Enable -6dB of analog attenuation on the left*/
    bool RightAnalogAtten; /*!< Enable -6dB of analog attenuation on the right*/

    bool LeftAnalogBoost;  /*!< Enable an analog +0.5dB of boost on the left*/
    bool RightAnalogBoost; /*!< Enable an analog +0.5dB of boost on the right*/

    char DSP_Profile1[MAX_PROFILE_CHAR];     /*!< Name of the DSP Profile 1*/
    uint32_t DSP_BufferA_values1[MAX_COEFF]; /*!< Buffer A values for the DSP Profile 1*/
    uint32_t DSP_BufferB_values1[MAX_COEFF]; /*!< Buffer B values for the DSP Profile 1*/
    uint32_t DSP_Intr_values1[MAX_INSTR];    /*!< Instruction buffer for the DSP Profile 1*/

    char DSP_Profile2[MAX_PROFILE_CHAR];     /*!< Name of the DSP Profile 2*/
    uint32_t DSP_BufferA_values2[MAX_COEFF]; /*!< Buffer A values for the DSP Profile 2*/
    uint32_t DSP_BufferB_values2[MAX_COEFF]; /*!< Buffer B values for the DSP Profile 2*/
    uint32_t DSP_Intr_values2[MAX_INSTR];    /*!< Instruction buffer for the DSP Profile 2*/

    char DSP_Profile3[MAX_PROFILE_CHAR];     /*!< Name of the DSP Profile 3*/
    uint32_t DSP_BufferA_values3[MAX_COEFF]; /*!< Buffer A values for the DSP Profile 3*/
    uint32_t DSP_BufferB_values3[MAX_COEFF]; /*!< Buffer B values for the DSP Profile 3*/
    uint32_t DSP_Intr_values3[MAX_INSTR];    /*!< Instruction buffer for the DSP Profile 3*/

    char DSP_Profile4[MAX_PROFILE_CHAR];     /*!< Name of the DSP Profile 4*/
    uint32_t DSP_BufferA_values4[MAX_COEFF]; /*!< Buffer A values for the DSP Profile 4*/
    uint32_t DSP_BufferB_values4[MAX_COEFF]; /*!< Buffer B values for the DSP Profile 4*/
    uint32_t DSP_Intr_values4[MAX_INSTR];    /*!< Instruction buffer for the DSP Profile 4*/

    char DSP_Profile5[MAX_PROFILE_CHAR];     /*!< Name of the DSP Profile 5*/
    uint32_t DSP_BufferA_values5[MAX_COEFF]; /*!< Buffer A values for the DSP Profile 5*/
    uint32_t DSP_BufferB_values5[MAX_COEFF]; /*!< Buffer B values for the DSP Profile 5*/
    uint32_t DSP_Intr_values5[MAX_INSTR];    /*!< Instruction buffer for the DSP Profile 5*/
};

/*! Define values that are stored on the EEPROM for the Amplifiers */
struct AMP
{
    uint8_t PowerLimit; /*!< Potentiometer value that configure the amplifier power limit*/
};