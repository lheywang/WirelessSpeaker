/**
 * @file PCM5252.cpp
 * @author l.heywang
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
}

// CONFIGURATION FUNCTIONS
int PCM5252::ConfigurePLL(const int EnablePLL,
                          const int PLLReference,
                          const int PLLSource,
                          const int PLLP,
                          const float PLLK,
                          const int PLLR,
                          const int OSR,
                          const int NCP,
                          const int AdvancedClock,
                          int *const PLLLock)
{
    if ((PLLReference > 0x03) | (PLLReference == 0x02))
        return -1;
    if ((PLLSource < 0x00) | (PLLSource > 0x05))
        return -2;

    // Checking the Input parameters.
    // We assume that the DAC is in VREF mode.
    // To enable the VCOM mode, an electrical schematic modification is needed thus judged improbable.
    int temp = (this->PLLINPUTFREQ / PLLP);
    if ((temp > 20'000'001) | (temp < 999'999))
        return -3;
    temp = (this->PLLINPUTFREQ * PLLK * PLLR) / PLLP;
    if ((temp > 100'000'001) | (temp < 63'999'999))
        return -3;

    temp = floor(PLLK);
    int PLLD = round(PLLK - temp);
    if ((PLLD == 0) & ((temp < 1) | (temp > 63)))
        return -3;
    else if ((temp < 4) | (temp > 11))
        return -3;
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
}

int PCM5252::ReadGPIOInput(int *const GPIOInputStatus)
{
}

int PCM5252::ConfigureI2S(const int BCKPolarity,
                          const int BCKOutputEnable,
                          const int LRCLKOutputEnable,
                          const int MasterModeBCKDivider,
                          const int MasterModeLRCLKDivider,
                          const int Enable16xInterpolation,
                          const int FSSpeedMode,
                          const int I2SDataFormat,
                          const int I2CWOrdLength,
                          const int I2SDataShift)
{
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
}

int PCM5252::ConfigureDAC(const int DACClockSource,
                          const int LeftDataSource,
                          const int RightDataSource,
                          const int DigitalVolumeMode,
                          const int DACArchitecture,
                          const int RequestSync)
{
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
}

int PCM5252::ConfigureVolume(const int LeftVolume, const int RightVolume)
{
}

int PCM5252::ConfigureDSP(const int EnableDeEmphasis,
                          const int SelectSDOUT,
                          const int GPIOInput,
                          const int DSPProgramSelection,
                          const int EnableAdaptativeMode)
{
}

int PCM5252::ConfigureExternalInterpolationFilter(const int Enable,
                                                  const int GPIO1OutputFunction,
                                                  const int GPIO2OutputFunction,
                                                  const int GPIO3OutputFunction,
                                                  const int GPIO4OutputFunction,
                                                  const int GPIO5OutputFunction,
                                                  const int GPIO6OutputFunction)
{
}

int PCM5252::ConfigureVoltageProtection(const int EnableXSMUTEPowerLoss, const int EnableInternalPowerLoss)
{
}

int PCM5252::ConfigureClock(const int AutoClockSet,
                            const int IgnoreFSDetection,
                            const int IgnoreBCKDetection,
                            const int IgnoreSCKDetection,
                            const int IgnoreClockHaltDetection,
                            const int IgnoreLRCLKBCKDetection,
                            const int IgnorePLLUnlocks,
                            const int ClockMissingDelay)
{
}

int PCM5252::ConfigureDSPCoefficientBuffer(const int Buffer, int *const Values)
{
}

int PCM5252::ConfigureDSPIntructions(int *const Instructions)
{
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
                             int *const FSSpeedMonitor)
{
}

int PCM5252::ReadMuteStatus(int *const AnalogLeftMute,
                            int *const AnalogRightMute,
                            int *const MuteZStatus,
                            int *const AutoMuteLeftStatus,
                            int *const AutoMuteRightStatus)
{
}

int PCM5252::ReadDSPStatus(int *const DSPBootStatus,
                           int *const DSPState,
                           int *const UsedCRAM,
                           int *const ActiveCRAM,
                           int *const IDAC)
{
}

int PCM5252::ReadAnalogStatus(int *const ShortCircuitOccuring,
                              int *const ShortCircuitDetected)
{
}
