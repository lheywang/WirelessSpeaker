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
#include <cstdint>

// Values arent the maximum ones, since there is a little to no case the are able to use them. Passed 48 kHz instruction are capped to 512.
// For some low sampling frequencies, you can always combine both of the parameters.
// And there is always the option to load some DSP profiles externaly, by software on the SD card.
constexpr int MAX_COEFF = 256;       /*!< Maximal number of coefficients for the DSP*/
constexpr int MAX_INSTR = 1024;      /*!< Maximal number of instructions for the DSP*/
constexpr int MAX_PROFILE_CHAR = 30; /*!< Maximal number of characters in the name of a DSP profile*/

/*! Define an optionnal user customized DSP profile with the maximum number of elements. Usefull for particularly slow audio sampling rates.*/
struct DSP_PROFILE_1024
{
    uint8_t DSP_Profile1[MAX_PROFILE_CHAR];     /*!< Name of the DSP Profile 1*/
    uint8_t DSP_BufferA_values1[MAX_COEFF * 3]; /*!< Buffer A values for the DSP Profile 1*/
    uint8_t DSP_BufferB_values1[MAX_COEFF * 3]; /*!< Buffer B values for the DSP Profile 1*/
    uint8_t DSP_Intr_values1[MAX_INSTR * 4];    /*!< Instruction buffer for the DSP Profile 1*/
};
constexpr int DSP_PROFILE_1024_SIZE = 5662;

/*! Define an optionnal user customized DSP profile with the half of number of elements. Usefull for particularly normal audio sampling rates.*/
struct DSP_PROFILE_512
{
    uint8_t DSP_Profile1[MAX_PROFILE_CHAR];           /*!< Name of the DSP Profile 1*/
    uint8_t DSP_BufferA_values1[(MAX_COEFF / 2) * 3]; /*!< Buffer A values for the DSP Profile 1*/
    uint8_t DSP_BufferB_values1[(MAX_COEFF / 2) * 3]; /*!< Buffer B values for the DSP Profile 1*/
    uint8_t DSP_Intr_values1[(MAX_INSTR / 2) * 4];    /*!< Instruction buffer for the DSP Profile 1*/
};
constexpr int DSP_PROFILE_512_SIZE = 2846;

/*! Define an optionnal user customized DSP profile with the quarter of number of elements. Usefull for particularly fast or very fast audio sampling rates.*/
struct DSP_PROFILE_256
{
    uint8_t DSP_Profile1[MAX_PROFILE_CHAR];           /*!< Name of the DSP Profile 1*/
    uint8_t DSP_BufferA_values1[(MAX_COEFF / 4) * 3]; /*!< Buffer A values for the DSP Profile 1*/
    uint8_t DSP_BufferB_values1[(MAX_COEFF / 4) * 3]; /*!< Buffer B values for the DSP Profile 1*/
    uint8_t DSP_Intr_values1[(MAX_INSTR / 4) * 4];    /*!< Instruction buffer for the DSP Profile 1*/
};
constexpr int DSP_PROFILE_256_SIZE = 1438;