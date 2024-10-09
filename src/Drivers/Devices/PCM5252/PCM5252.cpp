/**
 * @file PCM5252.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source of basic functions for the PCM5252 Audio DAC.
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

// Header file
#include "PCM5252.hpp"

// Cpp modules
#include <cstdint>
#include "../../I2C/I2C.hpp"
#include <math.h>
#include <cstdlib>
#include <unistd.h>

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

// Theses are global defines
#define PAGE_SELECT 0x00

// WARNING :
// This device use multiple pages registers.
// No checks are done in software, please verify your works.
// Somes register contain RESERVED bits. Read the documentation before attempting write to it.

// =====================
// PAGE 0
// =====================
#define PAGE_0 0x00
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
#define MASTER_MODE_CONTROL 0x0C

// Clocks
#define DAC_CLOCK_DIVIDER 0x1C
#define IGNORE_DETECTION 0x25
#define CLOCK_MISSING_DETECT 0x2C
#define CLOCK_SYSTEM_STATUS 0x5E
#define CLOCK_SYSTEM_ERRORS 0x5F
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
#define PAGE_1 0x01
// Analog Config
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
#define PAGE_44 0x2C
#define DSP_ADAPTATIVE 0x01

// =====================
// PAGE 253
// =====================
#define PAGE_253 0xFD
#define CLOCK_FLEX_1 0x3F
#define CLOCK_FLEX_2 0x40

// =====================
// DSP
// =====================
#define INSTR 0x98

// =====================
// MACROS
// =====================
#define REGISTER_AUTOINCREMENT(x) ((x & 0x7F) | 0x80)
#define REGISTER_NONINCREMENT(x) ((x & 0x7F) | 0x00)

// =====================
// PRIVATE FUNCTIONS
// =====================

int PCM5252::SelectPage(int Page)
{
    return I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(PAGE_SELECT), &Page);
}

// =====================
// CONSTRUCTORS
// =====================

PCM5252::PCM5252(const I2C_Bus *I2C, const int address)
{
    // Global I2C variables
    this->address = (uint8_t)address;
    this->I2C = *I2C;

    // PLL Variables
    this->PLLINPUTFREQ = 16'000'000;
    return;
}

// =====================
// DESTRUCTORS
// =====================

PCM5252::~PCM5252()
{
    return;
}

// =====================
// FUNCTIONS
// =====================

// SIMPLE FUNCTIONS
int PCM5252::ConfigureReset(const int Registers, const int DSP)
{
    int buf = (bool)DSP;
    buf = (buf << 4) | (bool)Registers;

    int res = 0;
    res += this->SelectPage(PAGE_0);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(DAC_RESET), &buf);

    if (res != 0)
        return -1;
    return 0;
}

int PCM5252::ConfigureLowPower(const int Standby, const int PowerDown)
{
    int buf = (bool)Standby;
    buf = (buf << 4) | (bool)PowerDown;

    int res = 0;
    res += this->SelectPage(PAGE_0);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(POWER_CONTROL), &buf);

    if (res != 0)
        return -1;
    return 0;
}

int PCM5252::Mute(const int MuteLeft, const int MuteRight)
{
    int buf = (bool)MuteLeft;
    buf = (buf << 4) | (bool)MuteRight;

    int res = 0;
    res += this->SelectPage(PAGE_0);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(MUTE_CONTROL), &buf);

    if (res != 0)
        return -1;
    return 0;
}

int PCM5252::DSPSwitchCRAM()
{
    int res = 0;
    int buf = 0;

    res += this->SelectPage(PAGE_44);
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(DSP_ADAPTATIVE), &buf);

    buf = buf | 0x01; // Set the last bit to '1'

    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(DSP_ADAPTATIVE), &buf);

    if (res != 0)
        return -1;
    return 0;
}

// CONFIGURATION FUNCTIONS
int PCM5252::ConfigurePLL(const int EnablePLL,
                          const int PLLReference,
                          const int PLLSource,
                          const int PLLP,
                          const float PLLK,
                          const int PLLR,
                          int *const PLLLock)
{
    if ((PLLReference > 0x03) | (PLLReference == 0x02))
        return -1;
    if ((0x00 > PLLSource) | (PLLSource > 0x05))
        return -2;
    if ((0 > PLLP) | (PLLP > 14))
        return -3;

    // Checking the Input parameters.
    // We assume that the DAC is in VREF mode.
    // To enable the VCOM mode, an electrical schematic modification is needed thus judged improbable.
    int PLLIN = (this->PLLINPUTFREQ / PLLP);
    if ((999'999 > PLLIN) | (PLLIN > 20'000'001))
        return -4;

    int PLLOUT = (this->PLLINPUTFREQ * PLLK * PLLR) / PLLP;
    if ((63'999'999 > PLLOUT) | (PLLOUT > 100'000'001))
        return -4;

    int PLLJ = floor(PLLK);
    int PLLD = round(PLLK - PLLJ) * 1000;
    if ((PLLD == 0) & ((1 > PLLJ) | (PLLJ > 63)))
        return -4;
    else if ((4 > PLLJ) | (PLLJ > 11))
        return -4;
    if (PLLD > 9999)
        return -5;

    // Creating buffers
    int buf[9] = {0};
    buf[0] = (bool)EnablePLL;   // R4
    buf[1] = PLLReference << 4; // R13
    buf[2] = PLLSource;         // R18
    buf[3] = PLLP;              // R20
    buf[4] = PLLJ;              // R21
    buf[5] = PLLD & 0x00FF;     // R22
    buf[6] = PLLD & 0xFF00;     // R23
    buf[7] = PLLR;              // R24

    int res = 0;

    // Writes
    res += this->SelectPage(PAGE_0);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(PLL_CONTROL), &buf[0]);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(PLL_INPUT_SOURCE), &buf[1]);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(PLL_INPUT_GPIO), &buf[2]);

    // Since five registers are contigous, we iterate over them inside of the I2C_Write function. We only pass the address of begining.
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(PLL_P_FACTOR), &buf[3], 5);

    // Read back the lock flag
    usleep(800); // 800 us delay to ensure that the PLL will lock if settings are correctly configured.
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(PLL_CONTROL), &buf[8]);

    if (res != 0)
        return -6;

    *PLLLock = (buf[8] >> 4) & 0x01;
    return 0;
}

int PCM5252::ConfigureGPIO(const int MISOFunction,
                           const int GPIOEnable,
                           const int GPIO1Output,
                           const int GPIO2Output,
                           const int GPIO3Output,
                           const int GPIO4Output,
                           const int GPIO5Output,
                           const int GPIO6Output,
                           const int GPIOPolarity,
                           const int GPIOInversion)
{
    int res = 0;
    int buf[10] = {0}; // Our buffers

    // MISO Function Selection
    if ((0 > MISOFunction) | (MISOFunction > 1))
        return -1;
    buf[0] = MISOFunction;
    // GPIO Enable

    if ((0 > GPIOEnable) | (GPIOEnable > 63))
        return -2;
    buf[1] = GPIOEnable;

    // GPIO Functions
    if ((0 > GPIO1Output) | (GPIO1Output > 16))
        return -3;
    buf[2] = GPIO1Output;
    if ((0 > GPIO2Output) | (GPIO2Output > 16))
        return -4;
    buf[3] = GPIO2Output;
    if ((0 > GPIO3Output) | (GPIO3Output > 16))
        return -5;
    buf[4] = GPIO3Output;
    if ((0 > GPIO4Output) | (GPIO4Output > 16))
        return -6;
    buf[5] = GPIO4Output;

    if ((0 > GPIO5Output) | (GPIO5Output > 16))
        return -7;
    buf[6] = GPIO5Output;
    if ((0 > GPIO6Output) | (GPIO6Output > 16))
        return -8;
    buf[7] = GPIO6Output;

    // GPIO Ouput polarity
    if ((0 > GPIOPolarity) | (GPIOPolarity > 63))
        return -9;
    buf[8] = GPIOPolarity;

    // GPIO Inversion
    if ((0 > GPIOInversion) | (GPIOInversion > 63))
        return -10;
    buf[9] = GPIOInversion;

    // I2C Writes
    res += this->SelectPage(PAGE_0);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(SPI_MISO_MODE), &buf[0]);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(GPIO_CONTROL), &buf[1]);

    // Since eight registers are contigous, we iterate over them inside of the I2C_Write function. We only pass the address of begining.
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(GPIO1_OUTPUT_FUNCTION), buf + 2 * sizeof(buf[0]), 8);

    if (res != 0)
        return -11;
    return 0;
}

int PCM5252::ReadGPIOInput(int *const GPIOInputStatus)
{
    int res = 0;
    int buf = 0;

    res += this->SelectPage(PAGE_0);
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(GPIO_INPUT_VALUES), &buf);

    if (res != 0)
        return -1;

    *GPIOInputStatus = buf & 0x3F;
    return 0;
}

int PCM5252::ConfigureI2S(const int BCKPolarity,
                          const int BCKOutputEnable,
                          const int LRCLKOutputEnable,
                          const int MasterModeBCKDivider,
                          const int MasterModeLRCLKDivider,
                          const int Enable16xInterpolation,
                          const int FSSpeedMode,
                          const int I2SDataFormat,
                          const int I2SWordLength,
                          const int I2SDataShift)
{
    if ((0x00 > FSSpeedMode) | (FSSpeedMode > 0x03))
        return -1;
    if ((0x00 > I2SDataFormat) | (I2SDataFormat > 0x03))
        return -2;
    if ((0x00 > I2SWordLength) | (I2SWordLength > 0x03))
        return -3;
    if ((0x00 > I2SDataShift) | (I2SDataShift > 0xFF))
        return -4;

    int res = 0;
    int buf[5] = {0};

    buf[0] = (bool)BCKPolarity;
    buf[0] = buf[0] << 1 | (bool)BCKOutputEnable;
    buf[0] = buf[0] << 4 | (bool)LRCLKOutputEnable; // R9

    buf[1] = (bool)MasterModeBCKDivider;
    buf[1] = buf[1] << 1 | (bool)MasterModeLRCLKDivider; // R12

    buf[2] = (bool)Enable16xInterpolation;
    buf[2] = buf[2] << 4 | FSSpeedMode; // R34

    buf[3] = I2SDataFormat;
    buf[3] = buf[3] << 4 | I2SWordLength; // R40

    buf[4] = I2SDataShift; // R41

    // Writes
    res += this->SelectPage(PAGE_0);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(I2S_CLOCK_CONFIG), &buf[0]);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(MASTER_MODE_CONTROL), &buf[1]);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(FS_SPEED), &buf[2]);

    // Since two registers are contigous, we iterate over them inside of the I2C_Write function. We only pass the address of begining.
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(I2S_CONFIG), &buf[3], 2);

    if (res != 0)
        return -5;
    return 0;
}

int PCM5252::ConfigureAnalogOutput(const int OutputAmplitudeMode,
                                   const int LeftAnalogGain,
                                   const int RightAnalogGain,
                                   const int AnalogMute,
                                   const int LeftAnalogBoost,
                                   const int RightAnalogBoost,
                                   const int VCOMRampUp,
                                   const int VCOMPowerDown)
{
    int res = 0;
    int buf[6] = {0};

    buf[0] = (bool)OutputAmplitudeMode; // R1

    buf[1] = (bool)LeftAnalogGain;
    buf[1] = buf[1] << 4 | (bool)RightAnalogGain; // R2

    buf[2] = (bool)AnalogMute; // R6

    buf[3] = (bool)LeftAnalogBoost;
    buf[3] = buf[3] << 4 | (bool)RightAnalogBoost; // R7

    buf[4] = (bool)VCOMRampUp; // R8

    buf[5] = (bool)VCOMPowerDown; // R9

    res += this->SelectPage(PAGE_1);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(OUTPUT_AMPLITUDE_REF), &buf[0]);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(ANALOG_GAIN), &buf[1]);

    // Since four registers are contigous, we iterate over them inside of the I2C_Write function. We only pass the address of begining.
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(ANALOG_MUTE), &buf[2], 4);

    if (res != 0)
        return -1;
    return 0;
}

int PCM5252::ConfigureDAC(const int DACClockSource,
                          const int LeftDataSource,
                          const int RightDataSource,
                          const int DigitalVolumeMode,
                          const int DACArchitecture,
                          const int RequestSync)
{
    if ((0 > DACClockSource) | (DACClockSource > 0x04))
        return -1;
    if ((0 > LeftDataSource) | (LeftDataSource > 0x03))
        return -2;
    if ((0 > RightDataSource) | (RightDataSource > 0x03))
        return -3;
    if ((0 > DigitalVolumeMode) | (DigitalVolumeMode > 0x03))
        return -3;

    int res = 0;
    int buf[5] = {0};

    buf[0] = DACClockSource << 4; // R14

    buf[1] = LeftDataSource;
    buf[1] = buf[1] << 4 | RightDataSource; // R42

    buf[2] = DigitalVolumeMode; // R60

    buf[3] = (bool)DACArchitecture; // R121

    buf[4] = (bool)RequestSync; // R19

    // Writes
    res += this->SelectPage(PAGE_0);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(DAC_CLOCK_SOURCE), &buf[0]);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(AUDIO_DATA_PATH), &buf[1]);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(GLOBAL_DIGITAL_VOLUME), &buf[2]);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(DAC_ARCHITECTURE), &buf[3]);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(DAC_RESYNC), &buf[4]);

    if (res != 0)
        return -4;
    return 0;
}

int PCM5252::ConfigureAutoMute(const int EnableAutoMute,
                               const int LeftEnableAutoMute,
                               const int RightEnableAutoMute,
                               const int LeftAutoMuteDelay,
                               const int RightAutoMuteDelay,
                               const int VolumeRampDownSpeed,
                               const int VolumeRampDownStep,
                               const int VolumeRampUpSpeed,
                               const int VolumeRampUpStep,
                               const int EmergencyVolumeRampDownSpeed,
                               const int EMergencyVolumeRampDownStep)
{
    if ((0 > LeftAutoMuteDelay) | (LeftAutoMuteDelay > 0x07))
        return -1;
    if ((0 > RightAutoMuteDelay) | (RightAutoMuteDelay > 0x07))
        return -2;
    if ((0 > VolumeRampDownSpeed) | (VolumeRampDownSpeed > 0x03))
        return -3;
    if ((0 > VolumeRampDownStep) | (VolumeRampDownStep > 0x03))
        return -4;
    if ((0 > VolumeRampUpSpeed) | (VolumeRampUpSpeed > 0x03))
        return -5;
    if ((0 > VolumeRampUpStep) | (VolumeRampUpStep > 0x03))
        return -6;
    if ((0 > EmergencyVolumeRampDownSpeed) | (EmergencyVolumeRampDownSpeed > 0x03))
        return -7;
    if ((0 > EMergencyVolumeRampDownStep) | (EMergencyVolumeRampDownStep > 0x03))
        return -8;

    int res = 0;
    int buf[4] = {0};

    buf[0] = LeftAutoMuteDelay;
    buf[0] = buf[0] << 4 | RightAutoMuteDelay; // R59

    buf[1] = VolumeRampDownSpeed;
    buf[1] = buf[1] << 2 | VolumeRampDownStep;
    buf[1] = buf[1] << 2 | VolumeRampUpSpeed;
    buf[1] = buf[1] << 2 | VolumeRampUpStep; // R63

    buf[2] = EmergencyVolumeRampDownSpeed;
    buf[2] = buf[2] << 2 | EMergencyVolumeRampDownStep;
    buf[2] = buf[2] << 4; // R64

    buf[3] = (bool)EnableAutoMute;
    buf[3] = buf[3] << 1 | (bool)LeftEnableAutoMute;
    buf[3] = buf[3] << 1 | (bool)RightEnableAutoMute; // R65

    // Writes
    res += this->SelectPage(PAGE_0);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(AUTOMUTE_DELAY), &buf[0]);

    // Since three registers are contigous, we iterate over them inside of the I2C_Write function. We only pass the address of begining.
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(NORMAL_VOLUME_RAMPS), &buf[1], 3);

    if (res != 0)
        return -10000;
    return 0;
}

int PCM5252::ConfigureVolume(const int LeftVolume, const int RightVolume)
{
    if ((0 > LeftVolume) | (LeftVolume > 0xFF))
        return -1;
    if ((0 > RightVolume) | (RightVolume > 0xFF))
        return -2;

    int res = 0;
    int buf[2] = {0};

    buf[0] = LeftVolume;
    buf[1] = RightVolume;

    // Writes
    res += this->SelectPage(PAGE_0);
    res += I2C_Write(&this->I2C, this->address, REGISTER_AUTOINCREMENT(LEFT_DIGITAl_VOLUME), buf, 2);

    if (res != 0)
        return -3;
    return 0;
}

int PCM5252::ConfigureDSP(const int EnableDeEmphasis,
                          const int SelectSDOUT,
                          const int GPIOInput,
                          const int DSPProgramSelection,
                          const int EnableAdaptativeMode)
{
    if ((0 > GPIOInput) | (GPIOInput > 0xFF))
        return -1;
    if ((0x01 > DSPProgramSelection) | (DSPProgramSelection > 0x07))
        return -2;
    if ((DSPProgramSelection == 0x04))
        return -2;
    if ((DSPProgramSelection == 0x06))
        return -2;

    int res = 0;
    int buf[4] = {0};

    buf[0] = (bool)EnableDeEmphasis;
    buf[0] = buf[0] << 4 | (bool)SelectSDOUT; // R7

    buf[1] = GPIOInput; // R10

    buf[2] = DSPProgramSelection; // R43

    // Writes
    res += this->SelectPage(PAGE_0);
    res += I2C_Write(&this->I2C, this->address, REGISTER_AUTOINCREMENT(SDOUT_EMPHASIS), &buf[0]);
    res += I2C_Write(&this->I2C, this->address, REGISTER_AUTOINCREMENT(DSP_INPUT), &buf[1]);
    res += I2C_Write(&this->I2C, this->address, REGISTER_AUTOINCREMENT(DSP_PROGRAM_SELECT), &buf[2]);

    res += this->SelectPage(PAGE_44); // R1
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(DSP_ADAPTATIVE), &buf[3]);
    if ((bool)EnableAdaptativeMode)
        buf[3] = buf[3] | 0x04; // Set the 3rd bit to '1'
    else
        buf[3] = buf[3] & 0xFB; // Set the 3rd bit to '0'
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(DSP_ADAPTATIVE), &buf[3]);

    if (res != 0)
        return -3;
    return 0;
}

int PCM5252::ConfigureExternalInterpolationFilter(const int Enable,
                                                  const int GPIO1OutputFunction,
                                                  const int GPIO2OutputFunction,
                                                  const int GPIO3OutputFunction,
                                                  const int GPIO4OutputFunction,
                                                  const int GPIO5OutputFunction,
                                                  const int GPIO6OutputFunction)
{
    if ((0 > GPIO1OutputFunction) | (GPIO1OutputFunction > 0x07))
        return -1;
    if ((0 > GPIO2OutputFunction) | (GPIO2OutputFunction > 0x07))
        return -3;
    if ((0 > GPIO3OutputFunction) | (GPIO3OutputFunction > 0x07))
        return -3;
    if ((0 > GPIO4OutputFunction) | (GPIO4OutputFunction > 0x07))
        return -4;
    if ((0 > GPIO5OutputFunction) | (GPIO5OutputFunction > 0x07))
        return -5;
    if ((0 > GPIO6OutputFunction) | (GPIO6OutputFunction > 0x07))
        return -6;

    int res = 0;
    int buf[4] = {0};

    buf[0] = (bool)Enable; // R122

    buf[1] = GPIO1OutputFunction;
    buf[1] = buf[1] << 4 | GPIO2OutputFunction; // R123

    buf[2] = GPIO3OutputFunction;
    buf[2] = buf[2] << 4 | GPIO4OutputFunction; // R124

    buf[3] = GPIO5OutputFunction;
    buf[3] = buf[3] << 4 | GPIO6OutputFunction; // R125

    // Writes
    res += this->SelectPage(PAGE_0);
    // Chained writes.
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(EXTERNAL_DIGITAL_FILTER), buf, 4);

    if (res != 0)
        return -7;
    return 0;
}

int PCM5252::ConfigureVoltageProtection(const int EnableXSMUTEPowerLoss, const int EnableInternalPowerLoss)
{
    int res = 0;
    int buf = 0;

    buf = (bool)EnableXSMUTEPowerLoss;
    buf = buf << 1 | (bool)EnableInternalPowerLoss; // R5

    // Writes
    res += this->SelectPage(PAGE_1);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(EXTERNAL_UVP), &buf);

    if (res != 0)
        return -1;
    return 0;
}

int PCM5252::ConfigureClockErrors(const int AutoClockSet,
                                  const int IgnoreFSDetection,
                                  const int IgnoreBCKDetection,
                                  const int IgnoreSCKDetection,
                                  const int IgnoreClockHaltDetection,
                                  const int IgnoreLRCLKBCKDetection,
                                  const int IgnorePLLUnlocks,
                                  const int ClockMissingDelay,
                                  const int AdvancedClock)
{
    if ((0 > ClockMissingDelay) | (ClockMissingDelay > 0x07))
        return -1;

    int res = 0;
    int buf[4] = {0};

    buf[0] = (bool)IgnoreFSDetection;
    buf[0] = buf[0] << 1 | (bool)IgnoreBCKDetection;
    buf[0] = buf[0] << 1 | (bool)IgnoreSCKDetection;
    buf[0] = buf[0] << 1 | (bool)IgnoreClockHaltDetection;
    buf[0] = buf[0] << 1 | (bool)IgnoreLRCLKBCKDetection;
    buf[0] = buf[0] << 1 | (bool)AutoClockSet;
    buf[0] = buf[0] << 1 | (bool)IgnorePLLUnlocks; // R37

    buf[1] = ClockMissingDelay; // R44

    if ((bool)AdvancedClock) // Values given according the datasheet.
    {
        buf[2] = 0x11;
        buf[3] = 0xFF;
    }
    else
    {
        buf[2] = 0x00;
        buf[3] = 0x00;
    }

    // Writes
    res += this->SelectPage(PAGE_0);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(IGNORE_DETECTION), &buf[0]);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(CLOCK_MISSING_DETECT), &buf[1]);

    res += this->SelectPage(PAGE_44);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(CLOCK_FLEX_1), &buf[2], 2);

    if (res != 0)
        return -2;
    return 0;
}

int PCM5252::ConfigureClockDividers(const int OSR,
                                    const int NCP,
                                    const int DDAC,
                                    const int DSP,
                                    const int BCK,
                                    const int LRLCK)
{
    if ((0 > OSR) | (OSR > 0x7F))
        return -1;
    if ((0 > NCP) | (NCP > 0x7F))
        return -2;
    if ((0 > DDAC) | (DDAC > 0x7F))
        return -3;
    if ((0 > DSP) | (DSP > 0x7F))
        return -4;
    if ((0 > BCK) | (BCK > 0x7F))
        return -5;
    if ((0 > LRLCK) | (LRLCK > 0x7F))
        return -6;

    int res = 0;
    int buf[6] = {0};

    buf[0] = DSP;   // R27
    buf[1] = DDAC;  // R28
    buf[2] = NCP;   // R29
    buf[3] = OSR;   // R30
    buf[4] = BCK;   // R32 WARNING GAP HERE !
    buf[5] = LRLCK; // R33

    // Writes
    res += this->SelectPage(PAGE_0);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(DSP_CLOCK_DIVIDER), &buf[0], 4);
    res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(MASTER_BCK_DIVIDER), &buf[4], 2);

    if (res != 0)
        return -7;
    return 0;
}

int PCM5252::ConfigureDSPCoefficientBuffer(const int Buffer, int *const Values, const size_t CoeffNumber)
{
    if ((Buffer != DAC_BUFFER_A) & (Buffer != DAC_BUFFER_B))
        return -1;
    if (CoeffNumber > 255)
        return -2;

    int res = 0;
    int buf[3] = {0};
    int temp = 0;
    int coeff = 1;

    // First, we iterate over the pages.
    for (int page = Buffer; page < Buffer + 9; page++)
    {
        res += this->SelectPage(page);
        // Then, we iterate over each coefficients.
        for (int coefficient = 0; coefficient < 30; coefficient++)
        {
            temp = *(Values + (page * 30 + coefficient) * sizeof(int));

            // We write the MSB first
            buf[0] = temp & 0x00FF0000;
            buf[1] = temp & 0x0000FF00;
            buf[2] = temp & 0x000000FF;

            res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(((coefficient * 4) + 8)), buf, 3);
            coeff++;

            // Check if we reached the end coefficient, or the end of the provided list.
            if ((coeff == (int)CoeffNumber) | (coeff == 255))
            {
                if (res != 0)
                    return -3;
                return 0;
            }
        }
    }
    return -4;
}

int PCM5252::ConfigureDSPIntructions(int *const Instructions, const size_t InstrNumber)
{
    if (InstrNumber > 1023)
        return -1;

    int res = 0;
    int buf[4] = {0};
    int temp = 0;
    int instr = 1;

    // First, we iterate over the pages.
    for (int page = 0x7D; page < 0xB1; page++)
    {
        res += this->SelectPage(page);
        // Then, we iterate over each instruction.
        for (int instruction = 0; instruction < 30; instruction++)
        {
            temp = *(Instructions + ((page * 30) + instruction) * sizeof(int));
            buf[0] = temp & 0xFF000000;
            buf[1] = temp & 0x00FF0000;
            buf[2] = temp & 0x0000FF00;
            buf[2] = temp & 0x000000FF;

            res += I2C_Write(&this->I2C, this->address, REGISTER_NONINCREMENT(((instruction * 4) + 8)), buf, 4);
            instr++;

            // Check if we reached the end instruction, or the end of the provided list.
            if ((instr == (int)InstrNumber) | (instr == 1023))
            {
                if (res != 0)
                    return -2;
                return 0;
            }
        }
    }
    return -3;
}

// READ BACK FUNCTIONS
int PCM5252::ReadClockStatus(int *const DetectedBCKRatio,
                             int *const SCKPresent,
                             int *const PLLLocked,
                             int *const LRCLKBCKPresent,
                             int *const SCKRatio,
                             int *const SCKRatioValid,
                             int *const BCKValid,
                             int *const FSValid,
                             int *const LatchedClockHalt,
                             int *const ClockMissing,
                             int *const ClockResync,
                             int *const ClockError,
                             int *const FSSpeedMonitor,
                             int *const DetectedFS,
                             int *const DetectedSCK)
{
    int res = 0;
    int buf[6] = {0};

    res += this->SelectPage(PAGE_0);
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(DETECTED_BCK_RATIO_MSB), &buf[0]); // R92
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(DETECTED_BCK_RATIO_LSB), &buf[1]); // R93
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(CLOCK_SYSTEM_STATUS), &buf[2]);    // R94
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(CLOCK_SYSTEM_ERRORS), &buf[3]);    // R95
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(FS_SPEED_MONITOR), &buf[4]);       // R115
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(DETECTED_AUDIO_SPECS), &buf[5]);   // R91

    if (res != 0)
        return -1;

    *DetectedBCKRatio = buf[0] << 8 | buf[1];

    *SCKPresent = (buf[2] & 0x40) >> 6;
    *PLLLocked = (buf[2] & 0x20) >> 5;
    *LRCLKBCKPresent = (buf[2] & 0x10) >> 4;
    *SCKRatio = (buf[2] & 0x08) >> 3;
    *SCKRatioValid = (buf[2] & 0x04) >> 2;
    *BCKValid = (buf[2] & 0x02) >> 1;
    *FSValid = buf[2] & 0x01;

    *LatchedClockHalt = (buf[3] & 0x10) >> 4;
    *ClockMissing = (buf[3] & 0x04) >> 2;
    *ClockResync = (buf[3] & 0x02) >> 1;
    *ClockError = buf[3] & 0x01;

    *FSSpeedMonitor = buf[4] & 0x03;

    *DetectedFS = (buf[5] & 0x70) >> 4;
    *DetectedSCK = buf[5] & 0x0F;

    return 0;
}

int PCM5252::ReadMuteStatus(int *const AnalogLeftMute,
                            int *const AnalogRightMute,
                            int *const MuteZStatus,
                            int *const AutoMuteLeftStatus,
                            int *const AutoMuteRightStatus)
{
    int res = 0;
    int buf[3] = {0};

    res += this->SelectPage(PAGE_0);
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(MUTE_STATUS), &buf[0]);   // R108
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(XSMUTE_STATUS), &buf[1]); // R114
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(XSMUTE_STATUS), &buf[2]); // R120

    if (res != 0)
        return -1;

    *AnalogLeftMute = (buf[0] & 0x02) >> 1;
    *AnalogRightMute = buf[0] & 0x01;

    *MuteZStatus = buf[1] & 0x03;

    *AutoMuteLeftStatus = (buf[2] & 0x10) >> 4;
    *AutoMuteRightStatus = buf[2] & 0x01;

    return 0;
}

int PCM5252::ReadDSPStatus(int *const DSPBootStatus,
                           int *const DSPState,
                           int *const UsedCRAM,
                           int *const ActiveCRAM,
                           int *const IDAC,
                           int *const DSPOverflow)
{
    int res = 0;
    int buf[5] = {0};

    res += this->SelectPage(PAGE_0);
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(DSP_STATUS), &buf[0]);   // R118
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(DSP_OVERFLOW), &buf[1]); // R90
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(IDAC_MSB), &buf[2]);     // R35
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(IDAC_LSB), &buf[3]);     // R34

    res += this->SelectPage(PAGE_44);
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(DSP_ADAPTATIVE), &buf[4]); // P44 R1

    if (res != 0)
        return -1;

    *DSPBootStatus = (buf[0] & 0x80) >> 7;
    *DSPState = buf[0] & 0x0F;

    *DSPOverflow = buf[1] & 0x3F;

    *IDAC = buf[2] << 8 | buf[3];

    *ActiveCRAM = (buf[4] & 0x02) >> 1;
    *UsedCRAM = (buf[4] & 0x08) >> 3;

    return 0;
}

int PCM5252::ReadAnalogStatus(int *const ShortCircuitOccuring,
                              int *const ShortCircuitDetected)
{
    int res = 0;
    int buf = 0;

    res += this->SelectPage(PAGE_0);
    res += I2C_Read(&this->I2C, this->address, REGISTER_NONINCREMENT(OUTPUT_SHORT_STATUS), &buf); // R109

    if (res != 0)
        return -1;

    *ShortCircuitOccuring = buf & 0x01;
    *ShortCircuitDetected = (buf & 0x10) >> 4;

    return 0;
}
