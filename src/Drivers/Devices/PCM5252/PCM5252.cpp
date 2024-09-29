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

// =====================
// PRIVATE FUNCTIONS
// =====================

int PCM5252::SelectPage(int Page)
{
}

// =====================
// MACROS
// =====================
#define REGISTER_AUTOINCREMENT(x) ((x & 0x7F) | 0x80)
#define REGISTER_NONINCREMENT(X) ((x & 0x7F) | 0x00)

// =====================
// CONSTRUCTORS
// =====================

PCM5252::PCM5252(const I2C_Bus *I2C, const int address)
{
    this->address = (uint8_t)address;
    this->I2C = *I2C;
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

int PCM5252::ConfigurePLL(const int EnablePLL,
                          const int PLLReference,
                          const int PLLSource,
                          const int PLLP,
                          const int PLLJ,
                          const int PLLD,
                          const int PLLR,
                          const int OSR,
                          const int NCP,
                          const int PLLFLex1,
                          const int PLLFlex2,
                          int *const PLLLock) {}

int PCM5252::ConfigureGPIO(const int MISOFunction,
                           const int GPIOEnable,
                           const int GPIO1Output,
                           const int GPIO2Output,
                           const int GPIO3Output,
                           const int GPIO4Output,
                           const int GPIO5Output,
                           const int GPIO6Output,
                           const int GPIOPolarity,
                           const int GPIOInversion) {}

int PCM5252::ReadGPIOInput(int *const GPIOInputStatus) {}
int PCM5252::ConfigureI2S(const int BCKPolarity,
                          const int BCKOutputEnable,
                          const int LRCLKOutputEnable,
                          const int MasterModeBCKDivider,
                          const int MasterModeLRCLKDivider,
                          const int Enable16xInterpolation,
                          const int FSSpeedMode,
                          const int I2SDataFormat,
                          const int I2CWOrdLength,
                          const int I2SDataShift) {}
int PCM5252::ConfigureAnalogOutput(const int OutputAmplitudeMode,
                                   const int LeftAnalogGain,
                                   const int RightAnalogGain,
                                   const int AnalogMute,
                                   const int LeftAnalogBoost,
                                   const int RightAnalogBoost,
                                   const int VCOMRampUp,
                                   const int VCOMPowerDown) {}
int PCM5252::ConfigureReset(const int Registers, const int DSP) {}
int PCM5252::ConfigureLowPower(const int Standby, const int PowerDown) {}
int PCM5252::ConfigureDAC(const int DACClockSource,
                          const int LeftDataSource,
                          const int RightDataSource,
                          const int DigitalVolumeMode,
                          const int DACArchitecture,
                          const int RequestSync) {}
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
                               const int EMergencyVolumeRampDownStep) {}
int PCM5252::ConfigureVolume(const int LeftVolume, const int RightVolume) {}
int PCM5252::Mute(const int MuteLeft, const int MuteRight) {}
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
                             int *const FSSpeedMonitor) {}
int PCM5252::ReadMuteStatus(int *const AnalogLeftMute,
                            int *const AnalogRightMute,
                            int *const MuteZStatus,
                            int *const AutoMuteLeftStatus,
                            int *const AutoMuteRightStatus) {}
int PCM5252::ReadDSPStatus(int *const DSPBootStatus,
                           int *const DSPState,
                           int *const UsedCRAM,
                           int *const ActiveCRAM,
                           int *const IDAC) {}
int PCM5252::ReadAnalogStatus(int *const ShortCircuitOccuring,
                              int *const ShortCircuitDetected) {}
int PCM5252::ConfigureDSP(const int EnableDeEmphasis,
                          const int SelectSDOUT,
                          const int GPIOInput,
                          const int DSPProgramSelection,
                          const int EnableAdaptativeMode) {}
int PCM5252::DSPSwitchCRAM() {}
int PCM5252::ConfigureExternalInterpolationFilter(const int Enable,
                                                  const int GPIO1OutputFunction,
                                                  const int GPIO2OutputFunction,
                                                  const int GPIO3OutputFunction,
                                                  const int GPIO4OutputFunction,
                                                  const int GPIO5OutputFunction,
                                                  const int GPIO6OutputFunction) {}

int PCM5252::ConfigureVoltageProtection(const int EnableXSMUTEPowerLoss, const int EnableInternalPowerLoss) {}
int PCM5252::ConfigureClock(const int AutoClockSet,
                            const int IgnoreFSDetection,
                            const int IgnoreBCKDetection,
                            const int IgnoreSCKDetection,
                            const int IgnoreClockHaltDetection,
                            const int IgnoreLRCLKBCKDetection,
                            const int IgnorePLLUnlocks,
                            const int ClockMissingDelay) {}
int PCM5252::ConfigureDSPCoefficientBuffer(const int Buffer, int *const Values) {}
int PCM5252::ConfigureDSPIntructions(int *const Instructions) {}