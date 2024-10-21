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

#include <cstring>
#include <iostream>
#include <math.h>
#include <stdexcept>
#include <stdlib.h>

// ==============================================================================
// CONSTANTS
// ==============================================================================
constexpr int FixedPointFloatToIntPart =
    1'048'576; // Constant equal 2^(20) to shift the farthest decimal to a integer.

// ==============================================================================
// CONSTRUCTORS
// ==============================================================================

DSP_PROFILE::DSP_PROFILE(char name[MAX_PROFILE_CHAR])
{
    // Handle the name
    this->Name = (char*)malloc(MAX_PROFILE_CHAR);
    if(this->Name == nullptr)
        throw std::runtime_error(
            "[ DSP PROFILE ][ CONSTRUCTOR ] : Failed to allocate memory for the name.");

    // Open buffers for instruction or coefficients.
    this->bufferA = (uint8_t*)malloc(MAX_COEFF * 3);
    this->bufferB = (uint8_t*)malloc(MAX_COEFF * 3);
    this->instr = (uint8_t*)malloc(MAX_INSTR * 4);
    if(this->bufferA == nullptr)
        throw std::runtime_error(
            "[ DSP PROFILE ][ CONSTRUCTOR ] : Failed to allocate memory for the buffer A.");
    if(this->bufferB == nullptr)
        throw std::runtime_error(
            "[ DSP PROFILE ][ CONSTRUCTOR ] : Failed to allocate memory for the buffer B.");
    if(this->instr == nullptr)
        throw std::runtime_error("[ DSP PROFILE ][ CONSTRUCTOR ] : Failed to allocate memory for "
                                 "the instruction buffer.");

    // Make sure data is cleaned
    memset(this->bufferA, 0x00, MAX_COEFF * 3);
    memset(this->bufferB, 0x00, MAX_COEFF * 3);
    memset(this->instr, 0x00, MAX_COEFF * 4);
    memset(this->Name, 0x00, MAX_PROFILE_CHAR);

    // Copy the data
    memcpy(this->Name, name, MAX_PROFILE_CHAR);

    // Set the size operators
    this->size = LARGE_PROFILE;
    this->sizebufferA = MAX_COEFF * 3;
    this->sizebufferB = MAX_COEFF * 3;
    this->sizeinstr = MAX_INSTR * 4;

    return;
}
DSP_PROFILE::DSP_PROFILE(char name[MAX_PROFILE_CHAR], const DSP_PROFILE_SIZE len)
{
    // Handle the name
    this->Name = (char*)malloc(MAX_PROFILE_CHAR);
    if(this->Name == nullptr)
        throw std::runtime_error(
            "[ DSP PROFILE ][ CONSTRUCTOR ] : Failed to allocate memory for the name.");

    // Open buffers for instruction or coefficients.
    int coeff = 0;
    int instr = 0;
    switch(len)
    {
    case DSP_PROFILE_SIZE::LARGE:
        coeff = MAX_COEFF;
        instr = MAX_INSTR;
        break;

    case DSP_PROFILE_SIZE::MEDIUM:
        coeff = MAX_COEFF / 2;
        instr = MAX_INSTR / 2;
        break;

    case DSP_PROFILE_SIZE::SMALL:
        coeff = MAX_COEFF / 4;
        instr = MAX_INSTR / 4;
        break;
    }

    this->bufferA = (uint8_t*)malloc(coeff * 3);
    this->bufferB = (uint8_t*)malloc(coeff * 3);
    this->instr = (uint8_t*)malloc(instr * 4);
    if(this->bufferA == nullptr)
        throw std::runtime_error(
            "[ DSP PROFILE ][ CONSTRUCTOR ] : Failed to allocate memory for the buffer A.");
    if(this->bufferB == nullptr)
        throw std::runtime_error(
            "[ DSP PROFILE ][ CONSTRUCTOR ] : Failed to allocate memory for the buffer B.");
    if(this->instr == nullptr)
        throw std::runtime_error("[ DSP PROFILE ][ CONSTRUCTOR ] : Failed to allocate memory for "
                                 "the instruction buffer.");

    // Make sure data is cleaned
    memset(this->bufferA, 0x00, coeff * 3);
    memset(this->bufferB, 0x00, coeff * 3);
    memset(this->instr, 0x00, instr * 4);
    memset(this->Name, 0x2E, MAX_PROFILE_CHAR);

    // Copy the data
    memcpy(this->Name, name, MAX_PROFILE_CHAR);

    // Set the size operators
    this->size = (int)len;
    this->sizebufferA = coeff * 3;
    this->sizebufferB = coeff * 3;
    this->sizeinstr = instr * 4;
    return;
}

// ==============================================================================
// DESTRUCTORS
// ==============================================================================
DSP_PROFILE::~DSP_PROFILE()
{
    // Buffer A
    if(this->bufferA != nullptr)
    {
        free(this->bufferA);
        this->bufferA = nullptr;
    }

    // Buffer B
    if(this->bufferB != nullptr)
    {
        free(this->bufferB);
        this->bufferB = nullptr;
    }

    // Buffer instr
    if(this->instr != nullptr)
    {
        free(this->instr);
        this->instr = nullptr;
    }

    // Buffer Name
    if(this->Name != nullptr)
    {
        free(this->Name);
        this->Name = nullptr;
    }
    // return
    return;
}

// ==============================================================================
// PRIVATE UTILITIES FUNCTIONS
// ==============================================================================

int ConvertFloatToFixedPoint4dot20(const float In, int* const Out)
{
    // The number in the the function will be expressed as :
    // SA.B where
    // S is the sign
    // A is the integer part
    // B is the floating part
    int S = 0;
    int A = 0;
    int B = 0;

    // Check for capability on the DSP buffer
    if(In < 0)
    {
        A = round(In);
        S = 1;

        if(A > 7)
            return -1;
    }
    else
    {
        A = round(In);
        S = 0;
        if(A < -7)
            return -1;
    }

    // Compute the float part
    B = (int)((In - A) * FixedPointFloatToIntPart);

    // Create the output buffer;
    *Out = S << 3;
    *Out |= A << 20;
    *Out |= B;
    *Out &= 0x00FFFFFF; // Make sure that there are 0 on the 8 MSBit
    return 0;
}

// ==============================================================================
// PRIVATE
// ==============================================================================

int DSP_PROFILE::ReadBuffers(uint8_t* const buf, int* const Len)
{
    // Safety checks
    if(*Len < this->size)
        return -1;

    // Copy the differents data as the memory layout define it !
    // We use relative offsets to match a specification change easily !
    memcpy(&buf[0], this->Name, MAX_PROFILE_CHAR);
    memcpy(&buf[MAX_PROFILE_CHAR], this->bufferA, this->sizebufferA);
    memcpy(&buf[MAX_PROFILE_CHAR + this->sizebufferA], this->bufferA, this->sizebufferB);
    memcpy(&buf[MAX_PROFILE_CHAR + this->sizebufferA + this->sizebufferB],
           this->bufferA,
           this->sizeinstr);

    *Len = MAX_PROFILE_CHAR + this->sizebufferA + this->sizebufferB + this->sizeinstr;
    return 0;
}

int DSP_PROFILE::WriteBuffers(uint8_t* const buf, int* const Len)
{
    // Safety checks
    if(*Len > this->size)
        return -1;

    // Copy the differents data as the memory layout define it !
    // We use relative offsets to match a specification change easily !
    memcpy(this->Name, &buf[0], MAX_PROFILE_CHAR);
    memcpy(this->bufferA, &buf[MAX_PROFILE_CHAR], this->sizebufferA);
    memcpy(this->bufferB, &buf[MAX_PROFILE_CHAR + this->sizebufferA], this->sizebufferB);
    memcpy(this->instr,
           &buf[MAX_PROFILE_CHAR + this->sizebufferA + this->sizebufferB],
           this->sizeinstr);

    *Len = MAX_PROFILE_CHAR + this->sizebufferA + this->sizebufferB + this->sizeinstr;
    return 0;
}

// ==============================================================================
// PUBLIC
// ==============================================================================

int DSP_PROFILE::LoadDefaultProfile(const int Profile)
{
    return 0;
}

int DSP_PROFILE::WriteInstructions(int* const Instructions, const int bufLen)
{
    if(bufLen > this->sizeinstr)
        return -1;

    int bufaddr = 0;

    for(int i = 0; i < bufLen; i++)
    {
        bufaddr = i * 4;
        this->instr[bufaddr] = (Instructions[i] & 0xFF000000) >> 24;
        this->instr[bufaddr + 1] = (Instructions[i] & 0x00FF0000) >> 16;
        this->instr[bufaddr + 2] = (Instructions[i] & 0x0000FF00) >> 8;
        this->instr[bufaddr + 3] = Instructions[i] & 0x000000FF;
    }
    return 0;
}

int DSP_PROFILE::WriteBufferB(float* const buf, const int bufLen)
{
    if(bufLen > this->sizeinstr)
        return -1;

    int bufaddr = 0;
    int t = 0;

    for(int i = 0; i < bufLen; i++)
    {
        if(ConvertFloatToFixedPoint4dot20(buf[i], &t) != 0)
            return -2;

        bufaddr = i * 3;
        this->bufferB[bufaddr] = (t & 0x00FF0000) >> 16;
        this->bufferB[bufaddr + 1] = (t & 0x0000FF00) >> 8;
        this->bufferB[bufaddr + 2] = t & 0x000000FF;
    }
    return 0;
}

int DSP_PROFILE::WriteBufferA(float* const buf, const int bufLen)
{
    if(bufLen > this->sizeinstr)
        return -1;

    int bufaddr = 0;
    int t = 0;

    for(int i = 0; i < bufLen; i++)
    {
        if(ConvertFloatToFixedPoint4dot20(buf[i], &t) != 0)
            return -2;

        bufaddr = i * 3;
        this->bufferA[bufaddr] = (t & 0x00FF0000) >> 16;
        this->bufferA[bufaddr + 1] = (t & 0x0000FF00) >> 8;
        this->bufferA[bufaddr + 2] = t & 0x000000FF;
    }
    return 0;
}

int DSP_PROFILE::ReturnBufferAValues(uint8_t* const buf)
{
    memcpy(buf, this->bufferA, this->sizebufferA);
    return 0;
}

int DSP_PROFILE::ReturnBufferBValues(uint8_t* const buf)
{
    memcpy(buf, this->bufferB, this->sizebufferB);
    return 0;
}

int DSP_PROFILE::ReturnInstrBufferValues(uint8_t* const buf)
{
    memcpy(buf, this->instr, this->sizeinstr);
    return 0;
}

int DSP_PROFILE::ReturnName(char buf[MAX_PROFILE_CHAR]) // OK
{
    memcpy(buf, this->Name, MAX_PROFILE_CHAR);
    return 0;
}