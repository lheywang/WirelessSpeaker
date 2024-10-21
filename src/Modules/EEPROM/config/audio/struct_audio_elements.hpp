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
#include <cstdint>
#include <iostream>

/*! Define values that are stored on the EEPROM for the analog equalizer*/
struct EQ
{
    uint8_t BassGain; /*!< Analog equalizer gain for the BASS*/
    uint8_t MediumGainRight; /*!< Analog equalizer gain for the medium right*/
    uint8_t MediumGainLeft; /*!< Analog equalizer gain for the medium left*/
    uint8_t HighGainRight; /*!< Analog equalizer gain for the treblles right*/
    uint8_t HighGainLeft; /*!< Analog equalizer gain for the trebbles left*/

    // Digipoti values shouldn't be too much different between right or left
    // They remain differentiate to enable a high precision customisation to match the components tolerances.
    uint8_t LowPassValueLeft; /*!< Low pass digipoti value for the left channel*/
    uint8_t LowPassValueRight; /*!< Low pass digipoti value for the right channel*/
    uint8_t HighPassValueLeft; /*!< High pass digipoti value for the left channel*/
    uint8_t HighPassValueRight; /*!< High pass digipoti value for the right channel*/

    uint8_t RL_eq; /*!< Right /-/ Left analog equalization*/
};

/*! Define values that are stored on the EEPROM for the Amplifiers */
struct DAC_Config
{
    uint8_t Automute_delay; /*!< Value for the automute setting*/
    uint8_t Global_Volume; /*!< Value for the global digital volume*/
    uint8_t Left_Volume; /*!< Left specific volume*/
    uint8_t Right_Volume; /*!< Right specific volume*/

    uint8_t LeftDataPath; /*!< Left data input selection*/
    uint8_t RightDataPath; /*!< Right data input selection*/

    uint8_t LeftAnalogAtten; /*!< Enable -6dB of analog attenuation on the left*/
    uint8_t RightAnalogAtten; /*!< Enable -6dB of analog attenuation on the right*/
};

/*! Define values that are stored on the EEPROM for the Amplifiers */
struct AMP
{
    uint8_t PowerLimit; /*!< Potentiometer value that configure the amplifier power limit*/
};