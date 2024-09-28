/**
 * @file AT42QT1070.hpp
 * @author l.heywang
 * @brief Define a class and functions for the AT42QT1070 Capacitive Touch Sensor.
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

// prevent multiple include
#pragma once

// type include
#include <cstdint>
#include "../../I2C/I2C.hpp"

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

#define AT42QT1070_DATA_SIZE 8 // 8b register here

#define AT42QT1070_ADDRESS 0x1B

#define CHIP_ID 0x00
#define FIRMWARE_VERSION 0x01
#define DETECTION_STATUS 0x02
#define FASTOUT_MAXCAL_GUARD 0x35
#define LOW_POWER_MODE 0x36
#define MAX_ON_DURATION 0x37
#define CALIBRATE 0x38
#define TOUCH_RESET 0x39

// KEY SIGNALS
#define KEY_SIGNAL_0_MSB 0x04
#define KEY_SIGNAL_0_LSB 0x05
#define KEY_SIGNAL_1_MSB 0x06
#define KEY_SIGNAL_1_LSB 0x07
#define KEY_SIGNAL_2_MSB 0x08
#define KEY_SIGNAL_2_LSB 0x09
#define KEY_SIGNAL_3_MSB 0x0A
#define KEY_SIGNAL_3_LSB 0x0B
#define KEY_SIGNAL_4_MSB 0x0C
#define KEY_SIGNAL_4_LSB 0x0D
#define KEY_SIGNAL_5_MSB 0x0E
#define KEY_SIGNAL_5_LSB 0x0F
#define KEY_SIGNAL_6_MSB 0x10
#define KEY_SIGNAL_6_LSB 0x11

// REFERENCE DATA
#define REFERENCE_DATA_0_MSB 0x12
#define REFERENCE_DATA_0_LSB 0x13
#define REFERENCE_DATA_1_MSB 0x14
#define REFERENCE_DATA_1_LSB 0x15
#define REFERENCE_DATA_2_MSB 0x16
#define REFERENCE_DATA_2_LSB 0x17
#define REFERENCE_DATA_3_MSB 0x18
#define REFERENCE_DATA_3_LSB 0x19
#define REFERENCE_DATA_4_MSB 0x1A
#define REFERENCE_DATA_4_LSB 0x1B
#define REFERENCE_DATA_5_MSB 0x1C
#define REFERENCE_DATA_5_LSB 0x1D
#define REFERENCE_DATA_6_MSB 0x1E
#define REFERENCE_DATA_6_LSB 0x1F

// NEGATIVE THRESHOLD
#define NEGATIVE_THRESHOLD_KEY_0 0x20
#define NEGATIVE_THRESHOLD_KEY_1 0x21
#define NEGATIVE_THRESHOLD_KEY_2 0x22
#define NEGATIVE_THRESHOLD_KEY_3 0x23
#define NEGATIVE_THRESHOLD_KEY_4 0x24
#define NEGATIVE_THRESHOLD_KEY_5 0x25
#define NEGATIVE_THRESHOLD_KEY_6 0x26

// ADJACENT KEY SUPPRESION LEVEL
#define ADJACENT_SUPPRESSION_LEVEL_KEY_0 0x27
#define ADJACENT_SUPPRESSION_LEVEL_KEY_1 0x28
#define ADJACENT_SUPPRESSION_LEVEL_KEY_2 0x29
#define ADJACENT_SUPPRESSION_LEVEL_KEY_3 0x2A
#define ADJACENT_SUPPRESSION_LEVEL_KEY_4 0x2B
#define ADJACENT_SUPPRESSION_LEVEL_KEY_5 0x2C
#define ADJACENT_SUPPRESSION_LEVEL_KEY_6 0x2D

// DETECTION INTEGRATOR COUNTER
#define DETECTION_INTEGRATOR_COUNTER_KEY_0 0x2E
#define DETECTION_INTEGRATOR_COUNTER_KEY_1 0x2F
#define DETECTION_INTEGRATOR_COUNTER_KEY_2 0x30
#define DETECTION_INTEGRATOR_COUNTER_KEY_3 0x31
#define DETECTION_INTEGRATOR_COUNTER_KEY_4 0x32
#define DETECTION_INTEGRATOR_COUNTER_KEY_5 0x33
#define DETECTION_INTEGRATOR_COUNTER_KEY_6 0x34

// ==============================================================================
// IC CLASS FUNCTIONS
// ==============================================================================

/**
 * @brief This class contain all of the basic functions to exploit the AT42QT1070 Touch Sensor.
 *
 */
class AT42QT1070
{
private:
    uint8_t address;
    I2C_Bus I2C;

public:
    /**
     * @brief Construct a new AT42QT1070 object
     *
     * @param[in] I2C A pointer to the I2C struct that is used to handle IO operation on this bus.
     * @param[in] address The address of the IC on the I2C bus.
     *
     */
    AT42QT1070(const I2C_Bus *I2C, const int address);

    /**
     * @brief Destroy the AT42QT1070 object
     *
     */
    ~AT42QT1070();

    /**
     * @brief Return the Device IDs.
     *
     * @param ID Pointer to an Integer to an int to store the Device ID.
     * @param FirmwareRevision Pointer to an int to store the FirmwareRevision.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     */
    int GetIDs(int *const ID, int *const FirmwareRevision);

    /**
     * @brief Get the Keys Status (ALL Channels + Others Infos)
     *
     * @param Calibration Pointer to an integer to store the Calibration value.
     * @param Overflow Pointer to an integer to store the Overflow Status.
     * @param Touch Pointer to the TOUCH value.
     * @param Keys Pointer to an array of 6 elements to store the KEY values.
     *
     * @return  0 : OK
     * @return -1 : Keys array to short.
     * @return -2 : IOCTL error.
     *
     */
    int GetKeysStatus(int *const Calibration, int *const Overflow, int *const Touch, int *const Keys);

    /**
     * @brief Get the Key Signals for a channel.
     *
     * @param Key Key ID Identifier value.
     * @param Value Pointer to an integer to store the read value.
     *
     * @return  0 : OK
     * @return -1 : Invalid Key Value.
     * @return -2 : IOCTL error.
     *
     */
    int GetKeySignals(const int Key, int *const Value);

    /**
     * @brief Get the Key Reference Signal for a channel.
     *
     * @param Key Key ID Identifier value.
     * @param Value Pointer to an integer to store the read value.
     *
     * @return  0 : OK
     * @return -1 : Invalid Key Value.
     * @return -2 : IOCTL error.
     *
     */
    int GetKeyReferenceSignal(const int Key, int *const Value);

    /**
     * @brief Configure the reference threshold value for a channel.
     *
     * @param Key Key ID Identifier value.
     * @param Value Value to be written in the register.
     *
     * @return  0 : OK
     * @return -1 : Invalid Key Value.
     * @return -2 : Invalid Value.
     * @return -3 : IOCTL error.
     *
     */
    int SetReferenceThreshold(const int Key, const int Value);
    /**
     * @brief Get the Reference threshold value for a channel.
     *
     * @param Key Key ID Identifier value.
     * @param Value Pointer to an integer to store the read value.
     *
     * @return  0 : OK
     * @return -1 : Invalid Key Value.
     * @return -2 : IOCTL error.
     *
     */
    int GetReferenceThreshold(const int Key, int *const Value);

    /**
     * @brief Set the Adjacent Key Suppresion object for a channel.
     *
     * @param Key Key ID Identifier value.
     * @param Value Value to be written in the register.
     *
     * @return -1 : Invalid Key Value.
     * @return -2 : Invalid Value.
     * @return -3 : IOCTL error.
     *
     */
    int SetAdjacentKeySuppresion(const int Key, const int Value);
    /**
     * @brief Get the Adjacent Key Suppresion configured value for a channel.
     *
     * @param Key Key ID Identifier value.
     * @param Value Pointer to an integer to store the read value.
     *
     * @return  0 : OK
     * @return -1 : Invalid Key Value.
     * @return -2 : IOCTL error.
     *
     */
    int GetAdjacentKeySuppresion(const int Key, int *const Value);

    /**
     * @brief Set the Detection Integrator value for a channel.
     *
     * @param Key Key ID Identifier value.
     * @param Value Value to be written in the register.
     *
     * @return -1 : Invalid Key Value.
     * @return -2 : Invalid Value.
     * @return -3 : IOCTL error.
     *
     */
    int SetDetectionIntegrator(const int Key, const int Value);
    /**
     * @brief Get the Detection Integrator value for a channel.
     *
     * @param Key Key ID Identifier value.
     * @param Value Pointer to an integer to store the read value.
     *
     * @return  0 : OK
     * @return -1 : Invalid Key Value.
     * @return -2 : IOCTL error.
     *
     */
    int GetDetectionIntegrator(const int Key, int *const Value);

    /**
     * @brief Configure the behavior of the IC
     *
     * @param FastOut Force all channels Detection Integrator with a value of 4. (1 to enable, 0 to disable)
     * @param MaxCal Force recalibration of all channels if a MaxOnDuration has been reached. (1 to enable, 0 to disable)
     * @param GuardChannel Configure the guard channel value.
     * @param LowPower Configure the time between each measures on the Capacitive touch.
     * @param MaxOnDuration Configure the maximal allowed ON time before calibration of the key(s).
     * @param Calibrate Force calibration of the IC.
     * @param nRESET Force a reset of the IC.
     *
     * @return  0 : OK
     * @return -1 : Incorrect guard channel value.
     * @return -2 : Incorrect LowPower value
     * @return -3 : Incorrect MaxOnDuration value
     * @return -4 : IOCTL error.
     */
    int ConfigureCapacitiveSensor(const int FastOut,
                                  const int MaxCal,
                                  const int GuardChannel,
                                  const int LowPower,
                                  const int MaxOnDuration,
                                  const int Calibrate,
                                  const int nRESET);
};