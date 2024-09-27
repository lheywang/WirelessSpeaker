/**
 * @file PCM5252.hpp
 * @author l.heywang
 * @brief Define a class and functions to exploit the PCM5252 audio DAC.
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */
// prevent multiple include
#pragma once

#include <cstdint>
#include "../../I2C/I2C.hpp"

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

// Theses are global defines
#define PCM5252_DATA_SIZE 8 // 8b register here
#define PAGE_SELECT 0x00

// WARNING :
// This device use multiple pages registers.
// No checks are done in software, please verify your works.
// Somes register contain RESERVED bits. Read the documentation before attempting write to it.

// =====================
// PAGE 0
// =====================
// PLL Config
#define PLL_P_FACTOR 0x14
#define PLL_J_FACTOR 0x15
#define PLL_D_FACTOR_MSB 0x16
#define PLL_D_FACTOR_LSB 0x17
#define PLL_R_FACTOR 0x18
#define PLL_CONTROL 0x04
#define PLL_INPUT_SOURCE 0x0D
#define PLL_INPUT_GPIO 0x12

// GPIO Config
#define GPIO1_OUTPUT_FUNCTION 0x50
#define GPIO2_OUTPUT_FUNCTION 0x51
#define GPIO3_OUTPUT_FUNCTION 0x52
#define GPIO4_OUTPUT_FUNCTION 0x53
#define GPIO5_OUTPUT_FUNCTION 0x54
#define GPIO6_OUTPUT_FUNCTION 0x55
#define GPIO_OUTPUT_STATUS 0x56
#define GPIO_POLARITY 0x57
#define EXTERNAL_DIGITAL_FILTER 0x7A
#define GPIO12_EXTERNAL_FILTER 0x7B
#define GPIO34_EXTERNAL_FILTER 0x7C
#define GPIO56_EXTERNAL_FILTER 0x7D
#define GPIO_INPUT_VALUES 0x77
#define GPIO_CONTROL 0x08

// SPI Config
#define SPI_MISO_MODE 0x06

// DSP Config
#define DSP_CLOCK_DIVIDER 0x1B
#define DSP_INPUT 0x0A
#define DSP_OVERFLOW 0x5A
#define DSP_PROGRAM_SELECT 0x2B
#define AUDIO_DATA_PATH 0x2A
#define SDOUT_EMPHASIS 0x07
#define IDAC_MSB 0x23
#define IDAC_LSB 0x24

// I2S Config
#define I2S_CLOCK_CONFIG 0x09
#define I2S_CONFIG 0x28
#define I2S_OFFSET 0x29
#define FS_SPEED 0x22

// Clocks
#define DAC_CLOCK_DIVIDER 0x1C
#define IGNORE_DETECTION 0x25
#define CLOCK_MISSING_DETECT 0x2C
#define CLOCK_SYSTEM_STATUS 0x5E
#define CLOCK_SYSTEM_ERRORS 0x5F
#define MASTER_MODE_CONTROL 0x0C
#define DAC_CLOCK_SOURCE 0x0E
#define DAC_RESYNC 0x13
#define NCP_CLOCK_DIVIDER 0x1D
#define OSR_CLOCK_DIVIDER 0x1E
#define MASTER_BCK_DIVIDER 0x20
#define LRCK_DIVIDER 0x21
#define DETECTED_AUDIO_SPECS 0x5B
#define DETECTED_BCK_RATIO_MSB 0x5C
#define DETECTED_BCK_RATIO_LSB 0x5D

// Misc. DAC Controls
#define DAC_RESET 0x01
#define POWER_CONTROL 0x02
#define MUTE_CONTROL 0x03
#define DAC_ARCHITECTURE 0x79

// DAC Status (for most read-only)
#define MUTE_STATUS 0x6C
#define OUTPUT_SHORT_STATUS 0x6D
#define XSMUTE_STATUS 0x72
#define FS_SPEED_MONITOR 0x73
#define DSP_STATUS 0x76
#define AUTO_MUTE_STATUS 0x78

// Analog Output Config
#define AUTOMUTE_DELAY 0x3B
#define GLOBAL_DIGITAL_VOLUME 0x3C
#define LEFT_DIGITAl_VOLUME 0x3D
#define RIGHT_DIGITAl_VOLUME 0x3E
#define NORMAL_VOLUME_RAMPS 0x3F
#define ERROR_VOLUME_RAMPS 0x40
#define AUTO_MUTE 0x41

// =====================
// PAGE 1
// =====================
#define OUTPUT_AMPLITUDE_REF 0x01
#define ANALOG_GAIN 0x02
#define EXTERNAL_UVP 0x05
#define ANALOG_MUTE 0x06
#define ANALOG_GAIN_BOOST 0x07
#define VCOM_RAMP 0x08
#define VCOM_POWER 0x09

// =====================
// PAGE 44
// =====================
#define DSP_ADAPTATIVE 0x01

// =====================
// PAGE 253
// =====================
#define CLOCK_FLEX_1 0x3F
#define CLOCK_FLEX_2 0x40

// ==============================================================================
// IC CLASS FUNCTIONS
// ==============================================================================

/**
 * @brief Base class for this audio 32b DAC.
 *
 */
class PCM5252
{
private:
    uint8_t address;
    I2C_Bus I2C;

public:
    /**
     * @brief Construct a new PCM5252 object
     *
     * @param[in] I2C A pointer to the I2C struct that is used to handle IO operation on this bus.
     * @param[in] address The address of the IC on the I2C bus.
     */
    PCM5252(const I2C_Bus *I2C, const int address);

    /**
     * @brief Destroy the PCM5252 object
     *
     */
    ~PCM5252();
};