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
#include "../../I2C/I2C.hpp"
#include <cstdint>

// ==============================================================================
// PUBLIC DEFINES
// ==============================================================================
/*! Define values for the KEYS on the AT42QT1070 */
enum class TOUCH_KEYS
{
    KEY0 = 0x00, /*!< Key 0*/
    KEY1 = 0x01, /*!< Key 1*/
    KEY2 = 0x02, /*!< Key 2*/
    KEY3 = 0x03, /*!< Key 3*/
    KEY4 = 0x04, /*!< Key 4*/
    KEY5 = 0x05, /*!< Key 5*/
    KEY6 = 0x06, /*!< Key 6*/
    KEY7 = 0x07, /*!< Key 7*/
};

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
    AT42QT1070(const I2C_Bus* I2C);

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
    int GetIDs(int* const ID, int* const FirmwareRevision);

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
    int
    GetKeysStatus(int* const Calibration, int* const Overflow, int* const Touch, int* const Keys);

    /**
     * @brief Get the Key Signals for a channel.
     *
     * @param[out] Key Key ID Identifier value.
     * @param[out] Value Pointer to an integer to store the read value.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     */
    int GetKeySignals(const TOUCH_KEYS Key, int* const Value);

    /**
     * @brief Get the Key Reference Signal for a channel.
     *
     * @param[out] Key Key ID Identifier value.
     * @param[out] Value Pointer to an integer to store the read value.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     */
    int GetKeyReferenceSignal(const TOUCH_KEYS Key, int* const Value);

    /**
     * @brief Configure the reference threshold value for a channel.
     *
     * @param[in] Key Key ID Identifier value.
     * @param[in] Value Value to be written in the register.
     *
     * @return  0 : OK
     * @return -1 : Invalid Value.
     * @return -2 : IOCTL error.
     *
     */
    int SetReferenceThreshold(const TOUCH_KEYS Key, const int Value);

    /**
     * @brief Get the Reference threshold value for a channel.
     *
     * @param[out] Key Key ID Identifier value.
     * @param[out] Value Pointer to an integer to store the read value.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     */
    int GetReferenceThreshold(const TOUCH_KEYS Key, int* const Value);

    /**
     * @brief Set the Adjacent Key Suppresion object for a channel.
     *
     * @param[in] Key Key ID Identifier value.
     * @param[in] Value Value to be written in the register.
     *
     * @return  0 : OK
     * @return -1 : Invalid Value.
     * @return -2 : IOCTL error.
     *
     */
    int SetAdjacentKeySuppresion(const TOUCH_KEYS Key, const int Value);
    /**
     * @brief Get the Adjacent Key Suppresion configured value for a channel.
     *
     * @param[out] Key Key ID Identifier value.
     * @param[out] Value Pointer to an integer to store the read value.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     */
    int GetAdjacentKeySuppresion(const TOUCH_KEYS Key, int* const Value);

    /**
     * @brief Set the Detection Integrator value for a channel.
     *
     * @param[in] Key Key ID Identifier value.
     * @param[in] Value Value to be written in the register.
     *
     * @return  0 : OK
     * @return -1 : Invalid Value.
     * @return -2 : IOCTL error.
     *
     */
    int SetDetectionIntegrator(const TOUCH_KEYS Key, const int Value);
    /**
     * @brief Get the Detection Integrator value for a channel.
     *
     * @param[out] Key Key ID Identifier value.
     * @param[out] Value Pointer to an integer to store the read value.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     */
    int GetDetectionIntegrator(const TOUCH_KEYS Key, int* const Value);

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