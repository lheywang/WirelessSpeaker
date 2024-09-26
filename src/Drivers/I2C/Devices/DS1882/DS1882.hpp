/**
 * @file DS1882.hpp
 * @author l.heywang
 * @brief Define a class and functions to exploit the DS1882 Audio logarithmic potentiometer
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

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

#define DS1882_DATA_SIZE 8 // 8b register here

// wipers value (bits 6 and 7)
#define WIPER_0 0x00
#define WIPER_1 0x40
#define CONFIG 0x80

// config register defined values
#define ZERO_CROSSING 0x01
#define WIPER_RES 0x00
#define WIPER_VOLATILE 0x02
#define EEPROM_STORE 0x80

// ==============================================================================
// IC CLASS FUNCTIONS
// ==============================================================================

/**
 * @brief DS1882 base class, to exploit the basics functions of this logarithmic audio digital potentiometer.
 *
 */
class DS1882
{
private:
    uint8_t address = 0x00;

public:
    /**
     * @brief Construct a new DS1882 object
     *
     * @param[in] address (int) : The address of the device on the I2C bus.
     */
    DS1882(int address);

    /**
     * @brief Destroy the DS1882 object
     *
     */
    ~DS1882();

    // Methods
    /**
     * @brief : Change the value of a potentiometer.
     *
     * @param[in] wiper int : Wiper selection. Use value defined in the header
     * @param[in] value int : Wiper value.
     *
     * @return int : 0 if correct.
     * @return int : -1 if incorrect wiper is choosen.
     */
    int WriteWiper(int wiper, int value);

    /**
     * @brief : read the value of a potentiometer
     *
     * @param[in] wiper int : Wiper selection. Use value defined in the header
     *
     * @return int : value. -1 if incorrect wiper has been choosen.
     */
    int ReadWiper(int wiper);
};