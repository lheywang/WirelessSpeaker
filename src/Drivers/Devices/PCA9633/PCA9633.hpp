/**
 * @file PCA9633.hpp
 * @author l.heywang
 * @brief Define a class and basic function for the PCA9633 leds drivers.
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
    I2C_Bus I2C;

public:
    /**
     * @brief Construct a new PCA9633 object
     *
     * @param[in] I2C A pointer to the I2C struct that is used to handle IO operation on this bus.
     * @param[in] address The address of the IC on the I2C bus.
     */
    PCA9633(I2C_Bus *I2C, int address);

    /**
     * @brief Destroy the PCA9633 object
     *
     */
    ~PCA9633();
};