/**
 * @file AT42QT1070.cpp
 * @brief Define basic functions for the AT42QT1070 Capacitive Touch Sensor IC.
 * @author l.heywang
 *
 */

// prevent multiple include
#pragma once

// type include
#include <cstdint>

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

public:
    /**
     * @brief Construct a new AT42QT1070 object
     *
     * @param[in] address The address of the IC on the I2C bus.
     *
     */
    AT42QT1070(int address);

    /**
     * @brief Destroy the AT42QT1070 object
     *
     */
    ~AT42QT1070();
};