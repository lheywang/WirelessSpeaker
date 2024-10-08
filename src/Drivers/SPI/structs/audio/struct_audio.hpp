/**
 * @file Audio.hpp
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
 * @var Audio::Trebbles Analog configuration for the trebbles
 * @var Audio::Medium Analog configuration for the mediums
 * @var Audio::Bass Analog cofnfiguration for the bass
 *
 * @var Audio::DAC Digital to analog conversion settings.
 *
 * @var Audio::Global Global volume en RL equalization settings
 *
 * @var Audio::BassAmp Settings for the bass amp
 * @var Audio::LeftAmp Settings for the left amp
 * @var Audio::RightAmp Settings for the right amp
 *
 */
struct Audio
{
    struct Trebbles Trebbles;
    struct Medium Mediums;
    struct Bass Bass;

    struct Global Global;

    struct DAC DAC;

    struct AMP BassAmp;
    struct AMP LeftAmp;
    struct AMP RightAmp;
};