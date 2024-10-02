/**
 * @file PCM5252.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
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

// =====================
// PUBLIC DEFINES
// =====================
#define BUFFER_A 0x2C /**DSP Buffer A Name */
#define BUFFER_B 0x3E /**DSP Buffer B Name */

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

    int PLLINPUTFREQ;

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
     * @brief Configure the PLL Subsystem of the DAC.
     *
     * @image html PCM5252_Clocks_Values.png "Dividers factors for the PCM5252 clocking circuit."
     * @image latex PCM5252_Clocks_Values.png "Dividers factors for the PCM5252 clocking circuit."
     *
     * @warning Any error here may place the DAC into an astable state where the PLL isn't locked, blocking any further audio applications.
     *
     * @param[in] EnablePLL Enable the PLL
     * @param[in] PLLReference Select the PLL Reference Clock
     * @param[in] PLLSource Select the PLL Source Clock
     * @param[in] PLLP P Coefficient for the PLL
     * @param[in] PLLK K Coefficient for the PLL. J and D values are determined automatically.
     * @param[in] PLLR R Coefficient for the PLL
     * @param[out] PLLLock Return the PLL Lock Status.
     *
     * @return  0 : OK
     * @return -1 : Invalid PLLReference
     * @return -2 : Invalid PLLSource
     * @return -3 : Invalid Coefficients (PLL P, J, D, R, OSR, NCP)
     * @return -4 : Invalid PLLP Value
     * @return -5 : Fractionnal value of PLLK > 9999.
     * @return -6 : IOCTL error.
     */
    int ConfigurePLL(const int EnablePLL,
                     const int PLLReference,
                     const int PLLSource,
                     const int PLLP,
                     const float PLLK,
                     const int PLLR,
                     int *const PLLLock);

    /**
     * @brief Configure the GPIO Subsystem of the DAC. Some of the settings below may need an advanced clocking configuration before.
     *
     * @image html PCM5252_GPIOOutput.png "Values for the GPIO Outputs"
     * @image latex PCM5252_GPIOOutput.png "Values for the GPIO Outputs"
     *
     * @param[in] MISOFunction Define the function of the MISO pin.
     * @param[in] GPIOEnable Define the state of all of the GPIO. Select Input or Output. Each bit mean 1 GPIO, thus a mask is required. 1 is output.
     * @param[in] GPIO1Output Configure the output source for the GPIO1. --> Check Datasheet
     * @param[in] GPIO2Output Configure the output source for the GPIO2.
     * @param[in] GPIO3Output Configure the output source for the GPIO3.
     * @param[in] GPIO4Output Configure the output source for the GPIO4.
     * @param[in] GPIO5Output Configure the output source for the GPIO5.
     * @param[in] GPIO6Output Configure the output source for the GPIO6.
     * @param[in] GPIOPolarity Configure the output polarity. 1 mean output high (Only for simple digital outputs)
     * @param[in] GPIOInversion Configure the output inversion. 1 mean that the output is inverted (active low)
     *
     * @return  0 : OK
     * @return -1 : Invalid MISOBUF Function.
     * @return -2 : Invalid Enable Value
     * @return -3 : Invalid output selection for GPIO1.
     * @return -4 : Invalid output selection for GPIO2.
     * @return -5 : Invalid output selection for GPIO3.
     * @return -6 : Invalid output selection for GPIO4.
     * @return -7 : Invalid output selection for GPIO5.
     * @return -8 : Invalid output selection for GPIO6.
     * @return -9 : Invalid output polarity.
     * @return -10 : Invalid output inversion.
     * @return -11 : IOCTL error.
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
     * @brief Configure the I2S Input of the DAC.
     *
     * @param[in] BCKPolarity Configure the BCK polarity. Assert the data sampling on rising edges or falling edges.
     * @param[in] BCKOutputEnable Configure the I2S BCK mode (master or slave)
     * @param[in] LRCLKOutputEnable Configure the I2S LRCLK mode (master or slave)
     * @param[in] MasterModeBCKDivider Configure the Master BCK Divider
     * @param[in] MasterModeLRCLKDivider Configure the Master LRCLK Divider
     * @param[in] Enable16xInterpolation Enable the 16x Interpolation input.
     * @param[in] FSSpeedMode Configure the FS mode (single : 00, dual : 01, quad : 10 or octal : 11)
     * @param[in] I2SDataFormat Configure the I2S Data Format (00 : I2S, 01 : TDM/DSP, 10 : RTJ, 11 : LTJ)
     * @param[in] I2SWordLength Configure the I2S Data Length (00 = 16b, 01 = 20b, 10 = 24b, 11 = 32b)
     * @param[in] I2SDataShift Configure how many BCK shift are applied to the I2S Data In (00 = 1 shift, 255 = 256 shifts)
     *
     * @return  0 : OK
     * @return -1 : Invalid FS Mode.
     * @return -2 : Invalid I2S DataFormat.
     * @return -3 : Invalid I2S Word Length.
     * @return -4 : Invalid I2C Data Shift.
     * @return -5 : IOCTL error.
     */
    int ConfigureI2S(const int BCKPolarity,
                     const int BCKOutputEnable,
                     const int LRCLKOutputEnable,
                     const int MasterModeBCKDivider,
                     const int MasterModeLRCLKDivider,
                     const int Enable16xInterpolation,
                     const int FSSpeedMode,
                     const int I2SDataFormat,
                     const int I2SWordLength,
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
     * @param[in] DACClockSource Select the DAC Clock Source. (000 = MCLK, 001 = PLL, 011 = SCK, 100 = BCK)
     * @param[in] LeftDataSource Select the used input data for the left channel. (00 = NULL, 01 = LEFT, 10 = RIGHT)
     * @param[in] RightDataSource Select the used Input data for the right channel. (00 = NULL, 01 = RIGHT, 10 = LEFT)
     * @param[in] DigitalVolumeMode Select the digital volume mode. (00 = Independant, 01 : right = left setting, 10 = left = right settings)
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
     * @param[in] VolumeRampDownSpeed Configure time between each step for ramp down. (00 = 1 FS, 01 = 2 FS, 10 = 4 FS, 11 = INSTANT)
     * @param[in] VolumeRampDownStep Configure the step size for ramp down. (00 = -4dB / update, 01 = -2dB / update, 10 = -1dB / update, 11 = -0.5dB / update)
     * @param[in] VolumeRampUpSpeed Configure the time between each step for ramp up. Same as VolumeRampDownSpeed.
     * @param[in] VolumeRampUpStep Configure the step size for ramp up. Same as VolumeRampDownStep.
     * @param[in] EmergencyVolumeRampDownSpeed Configure the emergency ramp down speed. Same as VolumeRampDownSpeed.
     * @param[in] EMergencyVolumeRampDownStep Configure the emergency ramp down step size. Same as VolumeRampDownStep.
     *
     * @return  0 : OK
     * @return -1 : Invalid Left Auto Mute delay value
     * @return -2 : Invalid Right Auto Mute delay value
     * @return -3 : Invalid Ramp Down Speed value.
     * @return -4 : Invalid Ramp down step value.
     * @return -5 : Invalid Ramp Up Speed value.
     * @return -6 : Invalid Ramp Up step value.
     * @return -7 : Invalid Emergency Volume Ramp down speed value
     * @return -8 : Invalid Emergency Volume Ramp down step value.
     * @return -9 : IOCTL error.
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
     * @image html PCM5252_InterpolFilter.png "GPIO functions, same for all"
     * @image html PCM5252_InterpolFilter.png "GPIO functions, same for all"
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
     * @brief Configure the clocking subsystem for the whole chip.
     *
     * @param[in] AutoClockSet Enable or disable the autoset mode for the clocks.
     * @param[in] IgnoreFSDetection Ignore the FS detection.
     * @param[in] IgnoreBCKDetection Ignore the BCK detection.
     * @param[in] IgnoreSCKDetection Ignore the SCK detection.
     * @param[in] IgnoreClockHaltDetection Ignore the Clock Halt Detection
     * @param[in] IgnoreLRCLKBCKDetection Ignore the LRCLK /  BCK detection.
     * @param[in] IgnorePLLUnlocks Ignore the PLL unlock detection.
     * @param[in] ClockMissingDelay Configure the delay before triggering an error for missing clock. (000 for 1s, 111 for 8s)
     *
     * @param[in] AdvancedClock Set to 1 to enable advanced clock circuitry.
     *
     * @return  0 : OK.
     * @return -1 : Incorrect Clock Missing Delay.
     * @return -2 : IOCTL error.
     */
    int ConfigureClockErrors(const int AutoClockSet,
                             const int IgnoreFSDetection,
                             const int IgnoreBCKDetection,
                             const int IgnoreSCKDetection,
                             const int IgnoreClockHaltDetection,
                             const int IgnoreLRCLKBCKDetection,
                             const int IgnorePLLUnlocks,
                             const int ClockMissingDelay,
                             const int AdvancedClock);
    /**
     * @brief Configure the various dividers on the clock tree !
     *
     * @image html PCM5252_I2S_Clocks.png "I2S Clocking Divider schematic, from the TI's documentation"
     * @image latex PCM5252_I2S_Clocks.png "I2S Clocking Divider schematic, from the TI's documentation"
     *
     * @image html PCM5252_Global_Clocks.png "Global clocking circuitry"
     * @image latex PCM5252_Global_Clocks.png "Global clocking circuitry"
     *
     * @image html PCM5252_Clocks_Values.png "Dividers factors for the PCM5252 clocking circuit."
     * @image latex PCM5252_Clocks_Values.png "Dividers factors for the PCM5252 clocking circuit."
     *
     * @warning Any error here may place the DAC into an astable state where the PLL isn't locked, blocking any further audio applications.
     *
     * @param[in] OSR Divider coefficient for the oversampling circuit. Source = DDAC. Shall be between 0 (divide by 1) and 127 (divider by 128)
     * @param[in] NCP Divider coefficient for the Negative Charge pump.  Source = DDAC. Shall be between 0 (divide by 1) and 127 (divider by 128)
     * @param[in] DDAC Divider frequency for the DAC circuit.  Source = PLL | SCK. Shall be between 0 (divide by 1) and 127 (divider by 128)
     * @param[in] DSP Divider coefficient for the DSP circuit. Source = PLL | SCK. Shall be between 0 (divide by 1) and 127 (divider by 128)
     * @param[in] BCK Divider coefficient for the BCK value (Master mode only). Source = SCK Shall be between 0 (divide by 1) and 127 (divider by 128)
     * @param[in] LRLCK Divider coefficient for the LRLCK value. (Master mode only). Source = SCK Shall be between 0 (divide by 1) and 127 (divider by 128)
     *
     * @return -1 : Incorrect OSR Value.
     * @return -2 : Incorrect NCP Value.
     * @return -3 : Incorrect DDAC Value.
     * @return -4 : Incorrect DSP Value.
     * @return -5 : Incorrect BCK Value.
     * @return -6 : Incorrect LRLCK Value.
     * @return -7 : IOCTL error.
     */
    int ConfigureClockDividers(const int OSR,
                               const int NCP,
                               const int DDAC,
                               const int DSP,
                               const int BCK,
                               const int LRLCK);

    /**
     * @brief Write to a CRAM buffer a list of coefficients for the DSP.
     * @warning This function is slow and blocking due to the large amount of Data to transfer.
     *
     * @param[in] Buffer The number of the buffer.
     * @param[in] Values An array to be wrote.
     * @param[in] CoeffNumber The number of values to write.
     *
     * @return  0 : OK
     * @return -1 : Invalid Buffer
     * @return -2 : Invalid Values sizes
     * @return -3 : IOCTL error.
     */
    int ConfigureDSPCoefficientBuffer(const int Buffer, int *const Values, const int CoeffNumber);

    /**
     * @brief Write to a CRAM buffer a list of instructions for the DSP.
     * @warning This function is slow and blocking due to the large amount of Data to transfer.
     *
     * @param[in] Values An array of instructions to be wrote.
     * @param[in] InstrNumber The number of instructions to write.
     *
     * @return  0 : OK
     * @return -1 : Invalid Values sizes
     * @return -2 : IOCTL error.
     * @return -3 : Unknown error. Shoudln't get here, if you land here, good luck !
     */
    int ConfigureDSPIntructions(int *const Instructions, const int InstrNumber);

    /**
     * @brief Configure the volume (digital) for the DAC.
     *
     * @image html PCM5252_Digital_Volume.png "Values for the digital volume"
     * @image latex PCM5252_Digital_Volume.png "Values for the digital volume"
     *
     * @param[in] LeftVolume Left volume value.
     * @param[in] RightVolume Right volume value.
     *
     * @return  0 : OK
     * @return -1 : Invalid Left Volume
     * @return -2 : Invalid Right Volume
     * @return -3 : IOCTL error.
     * @return -4 : Unknown error. Shoudln't get here, if you land here, good luck !
     */
    int ConfigureVolume(const int LeftVolume, const int RightVolume);

    /**
     * @brief Mute one or two channels on the DAC
     *
     * @param[in] MuteLeft Mute Left channel.
     * @param[in] MuteRight Mute Right channel.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int Mute(const int MuteLeft, const int MuteRight);

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
     * @param[out] DetectedFS Seen FS.
     * @param[out] DetectedSCK Seen SCK in FS counts.
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
                        int *const FSSpeedMonitor,
                        int *const DetectedFS,
                        int *const DetectedSCK);

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
     * @param[out] DSPOverflow Does the DSP has overflow ?
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int ReadDSPStatus(int *const DSPBootStatus,
                      int *const DSPState,
                      int *const UsedCRAM,
                      int *const ActiveCRAM,
                      int *const IDAC,
                      int *const DPSOverflow);

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
};