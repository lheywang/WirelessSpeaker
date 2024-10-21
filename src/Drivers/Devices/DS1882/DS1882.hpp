/**
 * @file DS1882.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
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
#include "../../I2C/I2C.hpp"
#include <cstdint>

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

/*! Define values for the wipers on the DS1882 */
enum class LOG_WIPER
{
    WIPER_0 = 0x00, /*!< Wiper 0*/
    WIPER_1 = 0x40, /*!< Wiper 1*/
};

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
    DS1882(const I2C_Bus* I2C, const LOG_POTI address);

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
     * @return -1 : Incorrect wiper value
     * @return -2 : IOCTL error.
     *
     * @test This function need to be tested !
     */
    int WriteWiper(const LOG_WIPER wiper, const int value);

    /**
     * @brief
     *
     * @param[out] wiper0 Pointer to an int to store the Wiper0 value
     * @param[out] wiper1 Pointer to an int to store the Wiper1 value
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     * @test This function need to be tested ! since a command byte (0x00) is sent, I don't know of the DS1882 will accept it !
     *
     */
    int ReadWipers(LOG_WIPER* const wiper0, LOG_WIPER* const wiper1);

    /**
     * @brief Configure the potentiometer.
     *
     *
     * @param[in] Volatile Set to 1 to let the poti settings volatile
     * @param[in] ZeroCrossing Set to 1 to enable the Zero Crossing Change*
     * @param[in] PotiConfig Set to 1 to enable the 63 pos Poti unless of the 33 pos mode.
     *
     * @return  0 : OK
     * @return -1 : IOCTL errror.
     */
    int ConfigurePoti(const int Volatile, const int ZeroCrossing, const int PotiConfig);
};