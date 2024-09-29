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

    int SelectPage(int Page);

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

    /**
     * @brief Configure the PLL Subsystem of the DAC
     *
     * @param[in] EnablePLL Enable the PLL
     * @param[in] PLLReference Select the PLL Reference Clock
     * @param[in] PLLSource Select the PLL Source Clock
     * @param[in] PLLP P Coefficient for the PLL
     * @param[in] PLLJ J Coefficient for the PLL
     * @param[in] PLLD D Coefficient for the PLL
     * @param[in] PLLR R Coefficient for the PLL
     * @param[in] OSR OSR Coefficient for the Clock
     * @param[in] NCP NCP Coefficient for the Clock
     * @param[in] PLLFlex1 Configure Advanced clock tree functions.
     * @param[in] PLLFlex2 Configure Advanced clock tree functions.
     * @param[out] PLLLock Return the PLL Lock Status.
     *
     * @return  0 : OK
     * @return -1 : Invalid PLLReference
     * @return -2 : Invalid PLLSource
     * @return -3 : Invalid Coefficients (PLL P, J, D, R, OSR, NCP)
     * @return -4 : IOCTL error.
     *
     */
    int ConfigurePLL(const int EnablePLL,
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
                     int *const PLLLock);

    /**
     * @brief Configure the GPIO Subsystem of the DAC
     *
     * @param[in] MISOFunction Define the function of the MISO pin.
     * @param[in] GPIOEnable Define the state of all of the GPIO. Select Input or Output.
     * @param[in] GPIO1Output Configure the output source for the GPIO1.
     * @param[in] GPIO2Output Configure the output source for the GPIO2.
     * @param[in] GPIO3Output Configure the output source for the GPIO3.
     * @param[in] GPIO4Output Configure the output source for the GPIO4.
     * @param[in] GPIO5Output Configure the output source for the GPIO5.
     * @param[in] GPIO6Output Configure the output source for the GPIO6.
     * @param[in] GPIOPolarity Configure the output polarity.
     * @param[in] GPIOInversion Configure the output inversion.
     *
     * @return  0 : OK
     * @return -1 : Invalid Enable Value
     * @return -2 : Invalid output selection for GPIO1.
     * @return -3 : Invalid output selection for GPIO2.
     * @return -4 : Invalid output selection for GPIO3.
     * @return -5 : Invalid output selection for GPIO4.
     * @return -6 : Invalid output selection for GPIO5.
     * @return -7 : Invalid output selection for GPIO6.
     * @return -8 : Invalid output polarity.
     * @return -9 : Invalid output inversion.
     * @return -10 : IOCTL error.
     */
    int ConfigureGPIO(const int MISOFunction,
                      const int GPIOEnable,
                      const int GPIO1Output,
                      const int GPIO2Output,
                      const int GPIO3Output,
                      const int GPIO4Output,
                      const int GPIO5Output,
                      const int GPIO6Output,
                      const int GPIOPolarity,
                      const int GPIOInversion);

    /**
     * @brief Read the status of the GPIO used as input.
     *
     * @param[out] GPIOInputStatus Pointer to an integer to store the value.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int ReadGPIOInput(int *const GPIOInputStatus);

    /**
     * @brief Configure the I2S Input of the DAC.
     *
     * @param[in] BCKPolarity Configure the BCK polarity
     * @param[in] BCKOutputEnable Configure the I2S BCK mode (master or slave)
     * @param[in] LRCLKOutputEnable Configure the I2S LRCLK mode (master or slave)
     * @param[in] MasterModeBCKDivider Configure the Master BCK Divider
     * @param[in] MasterModeLRCLKDivider Configure the Master LRCLK Divider
     * @param[in] Enable16xInterpolation Enable the 16x Interpolation input.
     * @param[in] FSSpeedMode Configure the FS mode (single, dual, quad or octal)
     * @param[in] I2SDataFormat Configure the I2S Data Format
     * @param[in] I2CWOrdLength Configure the I2S Data Length
     * @param[in] I2SDataShift Configure how many BCK shift are applied to the I2S Data In
     *
     * @return  0 : OK
     * @return -1 : Invalid Master BCK Divider.
     * @return -2 : Invalid Master LRCLK Divider.
     * @return -3 : Invalid FS Mode.
     * @return -4 : Invalid I2S DataFormat.
     * @return -5 : Invalid I2S Word Length.
     * @return -6 : Invalid I2C Data Shift.
     * @return -7 : IOCTL error.
     */
    int ConfigureI2S(const int BCKPolarity,
                     const int BCKOutputEnable,
                     const int LRCLKOutputEnable,
                     const int MasterModeBCKDivider,
                     const int MasterModeLRCLKDivider,
                     const int Enable16xInterpolation,
                     const int FSSpeedMode,
                     const int I2SDataFormat,
                     const int I2CWOrdLength,
                     const int I2SDataShift);

    /**
     * @brief Configure the Analog Part of the DAC.
     *
     * @param[in] OutputAmplitudeMode Configure the Output Amplitude mode (VCOM or GND)
     * @param[in] LeftAnalogGain Configure the gain for Left channel (0dB or 6dB)
     * @param[in] RightAnalogGain Configure the gain for Right channel (0dB or 6dB)
     * @param[in] AnalogMute Mute or unmute the analog part.
     * @param[in] LeftAnalogBoost Enable a 0.8 dB Analog boost on the Left Channel.
     * @param[in] RightAnalogBoost Enable a 0.8 dB Analog boost on the Right Channel.
     * @param[in] VCOMRampUp Configure the VCOM ramp up.
     * @param[in] VCOMPowerDown Configure the VCOM power down state.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int ConfigureAnalogOutput(const int OutputAmplitudeMode,
                              const int LeftAnalogGain,
                              const int RightAnalogGain,
                              const int AnalogMute,
                              const int LeftAnalogBoost,
                              const int RightAnalogBoost,
                              const int VCOMRampUp,
                              const int VCOMPowerDown);

    /**
     * @brief Configure the way for the DAC to be reseted.
     *
     * @param[in] Registers Set to 1 to reset the Registers.
     * @param[in] DSP Set to 1 to reset the DSP coefficients.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int ConfigureReset(const int Registers, const int DSP);

    /**
     * @brief Request the DAC to be placed in standby / power-down mode.
     *
     * @param[in] Standby Set to 1 to request Standby.
     * @param[in] PowerDown Set to 1 to request power down.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int ConfigureLowPower(const int Standby, const int PowerDown);

    /**
     * @brief Configure the subsystem in charge for the Digital to Analog Conversion.
     *
     * @param[in] DACClockSource Select the DAC Clock Source.
     * @param[in] LeftDataSource Select the used input data for the left channel.
     * @param[in] RightDataSource Select the used Input data for the right channel.
     * @param[in] DigitalVolumeMode Select the digital volume mode.
     * @param[in] DACArchitecture Select the DAC Architecture.
     * @param[in] RequestSync Request a sync for the clocks.
     *
     * @return  0 : OK
     * @return -1 : Invalid DAC clock.
     * @return -2 : Invalid left data input.
     * @return -3 : Invalid right data input.
     * @return -4 : Invalid digital volume mode.
     * @return -5 : IOCTL error.
     */
    int ConfigureDAC(const int DACClockSource,
                     const int LeftDataSource,
                     const int RightDataSource,
                     const int DigitalVolumeMode,
                     const int DACArchitecture,
                     const int RequestSync);

    /**
     * @brief Configure the AutoMute subsystem.
     *
     * @param[in] EnableAutoMute Enable and configure the AutoMute.
     * @param[in] LeftEnableAutoMute Enable automute for left channel.
     * @param[in] RightEnableAutoMute Enable automute for right channel.
     * @param[in] LeftAutoMuteDelay Configure delay before automute for the left channel.
     * @param[in] RightAutoMuteDelay Configure delay before automute for the right channel.
     * @param[in] VolumeRampDownSpeed Configure time between each step for ramp down.
     * @param[in] VolumeRampDownStep Configure the step size for ramp down.
     * @param[in] VolumeRampUpSpeed Configure the time between each step for ramp up.
     * @param[in] VolumeRampUpStep Configure the step size for ramp up.
     * @param[in] EmergencyVolumeRampDownSpeed Configure the emergency ramp down speed.
     * @param[in] EMergencyVolumeRampDownStep Configure the emergency ramp down step size.
     *
     * @return  0 : OK
     * @return -1 : Invalid Enable Auto Mute value.
     * @return -2 : Invalid Left Auto Mute delay value
     * @return -3 : Invalid Right Auto Mute delay value
     * @return -4 : Invalid Ramp Down Speed value.
     * @return -5 : Invalid Ramp down step value.
     * @return -6 : Invalid Ramp Up Speed value.
     * @return -7 : Invalid Ramp Up step value.
     * @return -9 : Invalid Emergency Volume Ramp down speed value
     * @return -10 : Invalid Emergency Volume Ramp down step value.
     * @return -11 : IOCTL error.
     */
    int ConfigureAutoMute(const int EnableAutoMute,
                          const int LeftEnableAutoMute,
                          const int RightEnableAutoMute,
                          const int LeftAutoMuteDelay,
                          const int RightAutoMuteDelay,
                          const int VolumeRampDownSpeed,
                          const int VolumeRampDownStep,
                          const int VolumeRampUpSpeed,
                          const int VolumeRampUpStep,
                          const int EmergencyVolumeRampDownSpeed,
                          const int EMergencyVolumeRampDownStep);

    /**
     * @brief Configure the volume (digital) for the DAC.
     *
     * @param[in] LeftVolume Left volume value.
     * @param[in] RightVolume Right volume value.
     *
     * @return  0 : OK
     * @return -1 : Invalid Left Volume
     * @return -2 : Invalid Right Volume
     * @return -3 : IOCTL error.
     */
    int ConfigureVolume(const int LeftVolume, const int RightVolume);

    /**
     * @brief Mute one or two channels on the DAC
     *
     * @param MuteLeft Mute Left channel.
     * @param MuteRight Mute Right channel.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int Mute(const int MuteLeft, const int MuteRight);

    /**
     * @brief Read the clock status of the DAC
     *
     * @param[out] DetectedBCKRatio Does the DAC has detected a BCK to SCK Ratio ?
     * @param[out] SCKPresent Does the SCK is present ?
     * @param[out] PLLLocked Is the PLL locked ?
     * @param[out] LRCLKBCKPresent Are the LRCLK or BCK present ?
     * @param[out] SCKRatio Is the SCK Ratio valid ?
     * @param[out] SCKValid Is the SCK Valid ?
     * @param[out] BCKValid Is the BCK Valid ?
     * @param[out] FSValid Is the FS mode valid ?
     * @param[out] LatchedClockHalt Does the clock has halted ?
     * @param[out] ClockMissing Does the clock miss ?
     * @param[out] ClockResync Do we need to resync the clock ?
     * @param[out] ClockError Is there Clock errors ?
     * @param[out] FSSpeedMonitor Does the FS Speed monitor is OK ?
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int ReadClockStatus(int *const DetectedBCKRatio,
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
                        int *const FSSpeedMonitor);

    /**
     * @brief Read the Mute status of the DAC
     *
     * @param[out] AnalogLeftMute Analog left channel mute status
     * @param[out] AnalogRightMute Analog right channel mute status
     * @param[out] MuteZStatus XSMT status
     * @param[out] AutoMuteLeftStatus Automute left channel status
     * @param[out] AutoMuteRightStatus Automute right channel status
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int ReadMuteStatus(int *const AnalogLeftMute,
                       int *const AnalogRightMute,
                       int *const MuteZStatus,
                       int *const AutoMuteLeftStatus,
                       int *const AutoMuteRightStatus);

    /**
     * @brief Read the DSP status
     *
     * @param[out] DSPBootStatus Does the DSP has finished booting ?
     * @param[out] DSPState In which mode is the DSP ?
     * @param[out] UsedCRAM Which CRAM is used ?
     * @param[out] ActiveCRAM Which CRAM is active ?
     * @param[out] IDAC How many steps are available for each audio frame.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int ReadDSPStatus(int *const DSPBootStatus,
                      int *const DSPState,
                      int *const UsedCRAM,
                      int *const ActiveCRAM,
                      int *const IDAC);

    /**
     * @brief Read the Analog Output Status
     *
     * @param[out] ShortCircuitOccuring A short circuit is occuring on the Output.
     * @param[out] ShortCircuitDetected A short circuit has occured on the Output (may not be present anymore).
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int ReadAnalogStatus(int *const ShortCircuitOccuring,
                         int *const ShortCircuitDetected);

    /**
     * @brief Configure the DSP substystem settings
     * @warning This function doesn't configure the coefficients.
     *
     * @param[in] EnableDeEmphasis Enable De-Emphasis filter.
     * @param[in] SelectSDOUT Select the SDOUT system.
     * @param[in] GPIOInput Set the bit 16:8 of the external DSP GPIO Input.
     * @param[in] DSPProgramSelection Select the program used by the DSP.
     * @param[in] EnableAdaptativeMode Enable the Adaptive mode.
     *
     * @return  0 : OK
     * @return -1 : Invalid GPIO Input value
     * @return -2 : Invalid DSP Program value
     * @return -3 : IOCTL Error.
     */
    int ConfigureDSP(const int EnableDeEmphasis,
                     const int SelectSDOUT,
                     const int GPIOInput,
                     const int DSPProgramSelection,
                     const int EnableAdaptativeMode);

    /**
     * @brief Ask to the DSP to switch from CRAM.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int DSPSwitchCRAM();

    /**
     * @brief Enable and configure the external Interpolation filter.
     *
     * @param[in] Enable Enable the functionnality.
     * @param[in] GPIO1OutputFunction Set the GPIO1 function for this mode.
     * @param[in] GPIO2OutputFunction Set the GPIO2 function for this mode.
     * @param[in] GPIO3OutputFunction Set the GPIO3 function for this mode.
     * @param[in] GPIO4OutputFunction Set the GPIO4 function for this mode.
     * @param[in] GPIO5OutputFunction Set the GPIO5 function for this mode.
     * @param[in] GPIO6OutputFunction Set the GPIO6 function for this mode.
     *
     * @return  0 : OK
     * @return -1 : Invalid GPIO1 Function
     * @return -2 : Invalid GPIO2 Function
     * @return -3 : Invalid GPIO3 Function
     * @return -4 : Invalid GPIO4 Function
     * @return -5 : Invalid GPIO5 Function
     * @return -6 : Invalid GPIO7 Function
     * @return -7 : IOCTL error.
     */
    int ConfigureExternalInterpolationFilter(const int Enable,
                                             const int GPIO1OutputFunction,
                                             const int GPIO2OutputFunction,
                                             const int GPIO3OutputFunction,
                                             const int GPIO4OutputFunction,
                                             const int GPIO5OutputFunction,
                                             const int GPIO6OutputFunction);

    /**
     * @brief Configure the reaction is case of Power Loss.
     *
     * @param[in] EnableXSMUTEPowerLoss Enable the external power loss detection.
     * @param[in] EnableInternalPowerLoss Enable the internal power loss detection.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int ConfigureVoltageProtection(const int EnableXSMUTEPowerLoss, const int EnableInternalPowerLoss);

    /**
     * @brief
     *
     * @param[in] AutoClockSet
     * @param[in] IgnoreFSDetection
     * @param[in] IgnoreBCKDetection
     * @param[in] IgnoreSCKDetection
     * @param[in] IgnoreClockHaltDetection
     * @param[in] IgnoreLRCLKBCKDetection
     * @param[in] IgnorePLLUnlocks
     * @param[in] ClockMissingDelay
     * @return
     */
    int ConfigureClock(const int AutoClockSet,
                       const int IgnoreFSDetection,
                       const int IgnoreBCKDetection,
                       const int IgnoreSCKDetection,
                       const int IgnoreClockHaltDetection,
                       const int IgnoreLRCLKBCKDetection,
                       const int IgnorePLLUnlocks,
                       const int ClockMissingDelay);

    /**
     * @brief Write to a CRAM buffer a list of coefficients for the DSP.
     * @warning This function is slow and blocking due to the large amount of Data to transfer.
     *
     * @param Buffer The number of the buffer.
     * @param Values An array to be wrote.
     *
     * @return  0 : OK
     * @return -1 : Invalid Buffer
     * @return -2 : Invalid Values sizes
     * @return -3 : IOCTL error.
     */
    int ConfigureDSPCoefficientBuffer(const int Buffer, int *const Values);

    /**
     * @brief Write to a CRAM buffer a list of instructions for the DSP.
     * @warning This function is slow and blocking due to the large amount of Data to transfer.
     *
     * @param Values An array of instructions to be wrote.
     *
     * @return  0 : OK
     * @return -1 : Invalid Buffer
     * @return -2 : Invalid Values sizes
     * @return -3 : IOCTL error.
     */
    int ConfigureDSPIntructions(int *const Instructions);
};