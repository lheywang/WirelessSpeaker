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
#include "../../I2C/I2C.hpp"

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

#define DS1882_DATA_SIZE 8 // 8b register here

// wipers value (bits 6 and 7)
#define WIPER_0 0x00
#define WIPER_1 0x40
#define CONFIG 0x80

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
    uint8_t address;
    I2C_Bus I2C;
    bool b_PotiConfig;

public:
    /**
     * @brief Construct a new DS1882 object
     *
     * @param[in] I2C A pointer to the I2C struct that is used to handle IO operation on this bus.
     * @param[in] address The address of the IC on the I2C bus.
     */
    DS1882(const I2C_Bus *I2C, const int address);

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
     * @return  0 : OK
     * @return -1 : Incorrect wiper
     * @return -2 : Incorrect wiper value
     * @return -3 : IOCTL error.
     *
     * @test This function need to be tested !
     */
    int WriteWiper(const int wiper, const int value);

    /**
     * @brief
     *
     * @param[inout] wiper0 Pointer to an int to store the Wiper0 value
     * @param[inout] wiper1 Pointer to an int to store the Wiper1 value
     *
     * @return  0 : OK
     * @return -1 : Invalid wipers pointers.
     * @return -2 : IOCTL error.
     *
     * @test This function need to be tested !
     *
     */
    int ReadWipers(int *const wiper0, int *const wiper1);

    /**
     * @brief Configure the potentiometer.
     *
     *
     * @param Volatile Set to 1 to let the poti settings volatile
     * @param ZeroCrossing Set to 1 to enable the Zero Crossing Change*
     * @param PotiConfig Set to 1 to enable the 63 pos Poti unless of the 33 pos mode.
     *
     * @return  0 : OK
     * @return -1 : IOCTL errror.
     */
    int ConfigurePoti(const int Volatile, const int ZeroCrossing, const int PotiConfig);
};