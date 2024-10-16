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

// Values arent the maximum ones, since there is a little to no case the are able to use them. Passed 48 kHz instruction are capped to 512.
// For some low sampling frequencies, you can always combine both of the parameters.
// And there is always the option to load some DSP profiles externaly, by software on the SD card.
constexpr int MAX_COEFF = 128;       /*!< Maximal number of coefficients for the DSP*/
constexpr int MAX_INSTR = 512;       /*!< Maximal number of instructions for the DSP*/
constexpr int MAX_PROFILE_CHAR = 30; /*!< Maximal number of characters in the name of a DSP profile*/

/*! Define values that are stored on the EEPROM for the Amplifiers */
struct DAC_Config
{
    uint8_t Automute_delay; /*!< Value for the automute setting*/
    uint8_t Global_Volume;  /*!< Value for the global digital volume*/
    uint8_t Left_Volume;    /*!< Left specific volume*/
    uint8_t Right_Volume;   /*!< Right specific volume*/

    uint8_t LeftDataPath;  /*!< Left data input selection*/
    uint8_t RightDataPath; /*!< Right data input selection*/

    bool LeftAnalogAtten;  /*!< Enable -6dB of analog attenuation on the left*/
    bool RightAnalogAtten; /*!< Enable -6dB of analog attenuation on the right*/

    uint8_t DSP_Profile1[MAX_PROFILE_CHAR];     /*!< Name of the DSP Profile 1*/
    uint8_t DSP_BufferA_values1[MAX_COEFF * 3]; /*!< Buffer A values for the DSP Profile 1*/
    uint8_t DSP_BufferB_values1[MAX_COEFF * 3]; /*!< Buffer B values for the DSP Profile 1*/
    uint8_t DSP_Intr_values1[MAX_INSTR * 4];    /*!< Instruction buffer for the DSP Profile 1*/

    uint8_t DSP_Profile2[MAX_PROFILE_CHAR];     /*!< Name of the DSP Profile 2*/
    uint8_t DSP_BufferA_values2[MAX_COEFF * 3]; /*!< Buffer A values for the DSP Profile 2*/
    uint8_t DSP_BufferB_values2[MAX_COEFF * 3]; /*!< Buffer B values for the DSP Profile 2*/
    uint8_t DSP_Intr_values2[MAX_INSTR * 4];    /*!< Instruction buffer for the DSP Profile 2*/
};

/*! Define values that are stored on the EEPROM for the Amplifiers */
struct AMP
{
    uint8_t PowerLimit; /*!< Potentiometer value that configure the amplifier power limit*/
};