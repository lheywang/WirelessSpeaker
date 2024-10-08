/**
 * @file AT42QT1070.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define a class and functions for the AT42QT1070 Capacitive Touch Sensor.
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 * @remark Class was tested successfully on 02/10/2024.
 *
 */

// prevent multiple include
#pragma once

// type include
#include <cstdint>
#include "../../I2C/I2C.hpp"

// ==============================================================================
// PUBLIC DEFINES
// ==============================================================================

#define AT42QT1070_ADDRESS 0x1B

// Keys
#define TOUCH_KEY0 0x00
#define TOUCH_KEY1 0x01
#define TOUCH_KEY2 0x02
#define TOUCH_KEY3 0x03
#define TOUCH_KEY4 0x04
#define TOUCH_KEY5 0x05
#define TOUCH_KEY6 0x06
#define TOUCH_KEY7 0x07

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
     *
     */
    AT42QT1070(const I2C_Bus *I2C);

    /**
     * @brief Destroy the AT42QT1070 object
     *
     */
    ~AT42QT1070();

    /**
     * @brief Return the Device IDs.
     *
     * @param[out] ID Pointer to an Integer to an int to store the Device ID.
     * @param[out] FirmwareRevision Pointer to an int to store the FirmwareRevision.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     */
    int GetIDs(int *const ID, int *const FirmwareRevision);

    /**
     * @brief Get the Keys Status (ALL Channels + Others Infos)
     *
     * @param[out] Calibration Pointer to an integer to store the Calibration value.
     * @param[out] Overflow Pointer to an integer to store the Overflow Status.
     * @param[out] Touch Pointer to the TOUCH value.
     * @param[out] Keys Pointer to an integer to store the keys value.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     */
    int GetKeysStatus(int *const Calibration, int *const Overflow, int *const Touch, int *const Keys);

    /**
     * @brief Get the Key Signals for a channel.
     *
     * @param[out] Key Key ID Identifier value.
     * @param[out] Value Pointer to an integer to store the read value.
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
     * @param[out] Key Key ID Identifier value.
     * @param[out] Value Pointer to an integer to store the read value.
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
     * @param[in] Key Key ID Identifier value.
     * @param[in] Value Value to be written in the register.
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
     * @param[out] Key Key ID Identifier value.
     * @param[out] Value Pointer to an integer to store the read value.
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
     * @param[in] Key Key ID Identifier value.
     * @param[in] Value Value to be written in the register.
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
     * @param[out] Key Key ID Identifier value.
     * @param[out] Value Pointer to an integer to store the read value.
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
     * @param[in] Key Key ID Identifier value.
     * @param[in] Value Value to be written in the register.
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
     * @param[out] Key Key ID Identifier value.
     * @param[out] Value Pointer to an integer to store the read value.
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
     * @param[in] FastOut Force all channels Detection Integrator with a value of 4. (1 to enable, 0 to disable)
     * @param[in] MaxCal Force recalibration of all channels if a MaxOnDuration has been reached. (1 to enable, 0 to disable)
     * @param[in] GuardChannel Configure the guard channel value.
     * @param[in] LowPower Configure the time between each measures on the Capacitive touch.
     * @param[in] MaxOnDuration Configure the maximal allowed ON time before calibration of the key(s).
     * @param[in] Calibrate Force calibration of the IC.
     * @param[in] nRESET Force a reset of the IC.
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