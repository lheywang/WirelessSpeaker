/**
 * @file struct_audio.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define the main audio struct
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

#include "struct_audio_elements.hpp"

/*! Create the abstraction layer that handle all of the audio configuration */
struct Audio
{
    struct EQ EQ;          /*!< Analog equializer configuration */
    struct DAC_Config DAC; /*!< DAC Config*/

    uint8_t __padding1 = 0x00; /*!< MEMORY PADDING. DO NOT TOUCH*/

    struct AMP BassAmp;  /*!< Bass amplifier settings*/
    struct AMP LeftAmp;  /*!< Left amplifier settings*/
    struct AMP RightAmp; /*!< Right amplifier settings*/
};