/**
 * @file dsp_profile.hpp
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
/*! Enum used to communicate a standard size for DSP profile to prevent mistypes. */
enum class DSP_PROFILE_SIZE
{
    LARGE = LARGE_PROFILE,   /*!< Large profile. (0) = 5662 bytes.*/
    MEDIUM = MEDIUM_PROFILE, /*!< Medium profile. (1) = 2846 bytes.*/
    SMALL = SMALL_PROFILE,   /*!< Small profile. (2) = 1438 bytes.*/
};

// ==============================================================================
// CLASS
// ==============================================================================
/**
 * @brief Class to provide high level integration and management functions for the DSP Profiles for the PCM5252 DAC IC.
 *
 */
class DSP_PROFILE
{
    // Enabling to the EEPROM class to access to the buffers,
    // to make easier the copy of the data directly, without requiring setters and getters.
    friend class EEPROM;

private:
protected:
    int size;        /*!< Store the size in bytes of the DSP profile on the eeprom. This doesn't compare to the size in RAM for a class instance.*/
    int sizebufferA; /*!< Store the size in bytes of the buffer A part of the DSP Profile*/
    int sizebufferB; /*!< Store the size in bytes of the buffer B part of the DSP Profile*/
    int sizeinstr;   /*!< Store the size in bytes of the instruction buffer part of the DSP Profile*/

    char *Name;       /*!< Store the name of the DSP Profile*/
    uint8_t *bufferA; /*!< Store the values of the coefficient A buffer of DSP Profile. Warning : Theses values are formatted to be exported on the DAC, thus expressed as a proprietary format.*/
    uint8_t *bufferB; /*!< Store the values of the coefficient B buffer of DSP Profile. Warning : Theses values are formatted to be exported on the DAC, thus expressed as a proprietary format.*/
    uint8_t *instr;   /*!< Store the values of the instructions buffer of DSP Profile. Warning : Theses values are formatted to be exported on the DAC, thus expressed as a proprietary format.*/

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
     * @brief Write the coefficients to buffer A
     *
     * @param[in] buf Float values to be wrote in the buffer A. Must be within +-7 range.
     * @param[in] bufLen Number of values to be wrote.
     *
     * @return  0 : OK
     * @return -1 : Incorrect buffer length (too big)
     * @return -2 : Buffer contain at least an incorrect value that cannot be converted to binary format.
     */
    int WriteBufferA(float *const buf, const int bufLen);

    /**
     * @brief Write the coefficients to buffer B
     *
     * @param[in] buf Float values to be wrote in the buffer A. Must be within +-7 range.
     * @param[in] bufLen Number of values to be wrote.
     *
     * @return  0 : OK
     * @return -1 : Incorrect buffer length (too big)
     * @return -2 : Buffer contain at least an incorrect value that cannot be converted to binary format.
     */
    int WriteBufferB(float *const buf, const int bufLen);

    /**
     * @brief Write the instructions
     *
     * @param[in] Instructions Int values used as instructions to be wrote.
     * @param[in] bufLen Number of values to be wrote.
     *
     * @return  0 : OK
     * @return -1 : Incorrect buffer length (too big)
     */
    int WriteInstructions(int *const Instructions, const int bufLen);

    /**
     * @brief Ask the class to load a default profile. Shall be included in the executable package when compiled.
     *
     * @param[in] Profile Profile ID to be loaded. Check correspondance table to be defined.
     *
     * @return  0 : OK
     * @return -1 : Incorrect buffer length (too big)
     */
    int LoadDefaultProfile(const int Profile);

    /**
     * @brief Return the buffer A formated values, ready to be flashed on the DAC.
     *
     * @param[out] buf The ouput buffer.
     *
     * @return  0 : OK
     */
    int ReturnBufferAValues(uint8_t *const buf);

    /**
     * @brief Return the buffer B formated values, ready to be flashed on the DAC.
     *
     * @param[out] buf The ouput buffer.
     *
     * @return  0 : OK
     */
    int ReturnBufferBValues(uint8_t *const buf);

    /**
     * @brief Return the instruction buffer formated values, ready to be flashed on the DAC.
     *
     * @param[out] buf The ouput buffer.
     *
     * @return  0 : OK
     */
    int ReturnInstrBufferValues(uint8_t *const buf);

    /**
     * @brief Return the name of the DSP Profile.
     *
     * @param[out] buf
     *
     * @return  0 : OK
     */
    int ReturnName(char buf[MAX_PROFILE_CHAR]);
};
