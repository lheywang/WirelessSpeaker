/**
 * @file PCA9633.cpp
 * @brief Define basic functions for the PCA9633 Leds Drivers.
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

#define PCA9633_DATA_SIZE 8

#define MODE1 0x00
#define MODE2 0x01
#define PWM0 0x02
#define PWM1 0x03
#define PWM2 0x04
#define PWM3 0x05
#define PWM4 0x06
#define GRPPPWM 0x06
#define GRPFREQ 0x07
#define LEDOUT 0x08
#define SUBADDR1 0x09
#define SUBADDR2 0x0A
#define SUBADDR3 0x0B
#define ALLCALLADR 0x0C

// ==============================================================================
// IC CLASS FUNCTIONS
// ==============================================================================

/**
 * @brief Base class for this LED drivers IC.
 *
 */
class PCA9633
{
private:
    uint8_t address;

public:
    /**
     * @brief Construct a new PCA9633 object
     *
     * @param[in] address (int) : The address of the IC on the I2C Bus.
     */
    PCA9633(int address);

    /**
     * @brief Destroy the PCA9633 object
     *
     */
    ~PCA9633();
};