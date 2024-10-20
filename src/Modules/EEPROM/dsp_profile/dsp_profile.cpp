/**
 * @file dsp_profile.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source for the DSP Profile class
 * @version 0.1
 * @date 2024-10-20
 *
 * @copyright Copyright (c) 2024
 *
 */

// ==============================================================================
// INCLUDES
// ==============================================================================
#include "dsp_profile.hpp"

#include <iostream>
#include <stdexcept>
#include <math.h>

// ==============================================================================
// CONSTANTS
// ==============================================================================

// ==============================================================================
// CONSTRUCTORS
// ==============================================================================

DSP_PROFILE::DSP_PROFILE(char name[MAX_PROFILE_CHAR])
{
    return;
}
DSP_PROFILE::DSP_PROFILE(char name[MAX_PROFILE_CHAR], const DSP_PROFILE_SIZE len)
{
    return;
}

// ==============================================================================
// DESTRUCTORS
// ==============================================================================
DSP_PROFILE::~DSP_PROFILE()
{
    return;
}

// ==============================================================================
// PRIVATE UTILITIES FUNCTIONS
// ==============================================================================

// ==============================================================================
// PRIVATE
// ==============================================================================

// ==============================================================================
// PUBLIC
// ==============================================================================

int DSP_PROFILE::LoadDefaultProfile(const int Profile)
{
    return 0;
}

int DSP_PROFILE::WriteInstructions(int *const Instructions)
{
    return 0;
}

int DSP_PROFILE::WriteBufferB(float *const buf)
{
    return 0;
}

int DSP_PROFILE::WriteBufferA(float *const buf)
{
    return 0;
}