/**
 * @file struct_dsp_profile.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define a DSP profile for the DAC.
 * @version 0.1
 * @date 2024-10-17
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
// ==============================================================================
// INCLUDES
// ==============================================================================
#include <cstdint>

// ==============================================================================
// CONSTANTS
// ==============================================================================
constexpr int MAX_PROFILE_CHAR = 30; /*!< Maximal number of characters in the name of a DSP profile*/
constexpr int LARGE_PROFILE = 5662;  /*!< Size in bytes for the largest DSP Profile*/
constexpr int MEDIUM_PROFILE = 2846; /*!< Size in bytes for the medium DSP Profile*/
constexpr int SMALL_PROFILE = 1438;  /*!< Size in bytes for the smallest DSP Profile*/
constexpr int MAX_COEFF = 256;       /*!< Maximal number of coefficients for the DSP*/
constexpr int MAX_INSTR = 1024;      /*!< Maximal number of instructions for the DSP*/

// ==============================================================================
// ENUMS
// ==============================================================================
enum class DSP_PROFILE_SIZE
{
    LARGE = LARGE_PROFILE,
    MEDIUM = MEDIUM_PROFILE,
    SMALL = SMALL_PROFILE,
};

// ==============================================================================
// CLASS
// ==============================================================================
class DSP_PROFILE
{
    // Enabling to the EEPROM class to access to the buffers,
    // to make easier the copy of the data directly, without requiring setters and getters.
    friend class EEPROM;

private:
protected:
    int size;
    int sizebufferA;
    int sizebufferB;
    int sizeinstr;

    char *Name;
    uint8_t *bufferA;
    uint8_t *bufferB;
    uint8_t *instr;

    /**
     * @brief This function is only available to friends class, and is used to write a serialized (from EEPROM) buffer to the differents fields.
     *
     * @param[in] buf The data to read
     * @param[inout] Len First, the len of the input buffer, and then the number of wrote bytes.
     *
     * @return  0 : OK
     * @return -1 : Buf too big
     */
    int WriteBuffers(uint8_t *const buf, int *const Len);

    /**
     * @brief This function is only available to friends class, and is used to fill a buffer of X len with the correct formatted data.
     * @warning A too small buffer may be misinterpreted. You'll need to ensure this point.
     *
     * @param[out] buf The data to rode
     * @param[inout] Len First, the len of the output buffer, and then the number of wrote bytes.
     *
     * @return  0 : OK
     * @return -1 : Buf too small.
     */
    int ReadBuffers(uint8_t *const buf, int *const Len);

public:
    // ==============================================================================
    // CONSTRUCTORS
    // ==============================================================================
    /**
     * @brief Construct a new dsp profile
     * @warning Since the len hasn't been specified, this one is defaulted to the maximal value.
     *
     * @param[in] name Name of the DSP Profile as a char array.
     */
    DSP_PROFILE(char name[MAX_PROFILE_CHAR]);

    /**
     * @brief Construct a new dsp profile
     *
     * @param[in] name Name of the DSP Profile as a char array.
     * @param[in] len Len of the DSP Profile.
     */

    DSP_PROFILE(char name[MAX_PROFILE_CHAR], const DSP_PROFILE_SIZE len);

    // ==============================================================================
    // DESTRUCTORS
    // ==============================================================================
    /**
     * @brief Destroy the dsp profile
     *
     */
    ~DSP_PROFILE();

    // ==============================================================================
    // FUNCTIONS
    // ==============================================================================
    /**
     * @brief
     *
     * @param buf
     * @return int
     */
    int WriteBufferA(float *const buf, const int bufLen);

    /**
     * @brief
     * @param buf
     * @return
     */
    int WriteBufferB(float *const buf, const int bufLen);

    /**
     * @brief
     * @param Instructions
     * @return
     */
    int WriteInstructions(int *const Instructions, const int bufLen);

    /**
     * @brief
     * @param Profile
     * @return
     */
    int LoadDefaultProfile(const int Profile);
};
