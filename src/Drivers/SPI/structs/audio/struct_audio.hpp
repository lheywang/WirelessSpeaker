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

/**
 * @struct Audio
 * @brief Structure that contain all of the Audio settings.
 *
 * @param Audio::Trebbles Analog configuration for the trebbles
 * @param Audio::Medium Analog configuration for the mediums
 * @param Audio::Bass Analog cofnfiguration for the bass
 *
 * @param Audio::DAC Digital to analog conversion settings.
 *
 * @param Audio::Global Global volume en RL equalization settings
 *
 * @param Audio::BassAmp Settings for the bass amp
 * @param Audio::LeftAmp Settings for the left amp
 * @param Audio::RightAmp Settings for the right amp
 *
 */
struct Audio
{
    struct Trebbles Trebbles;
    struct Medium Mediums;
    struct Bass Bass;

    struct Global Global;

    struct DAC_Config DAC;

    struct AMP BassAmp;
    struct AMP LeftAmp;
    struct AMP RightAmp;
};