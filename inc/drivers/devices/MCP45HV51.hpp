/**
 * @file MCP45HV51.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define a class and functions for the MCP45HV51 linear digital potentiometer.
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */
// prevent multiple include
#pragma once

// Drivers
#include "drivers/peripherals/i2c.hpp"

// STD
#include <cstdint>

// ==============================================================================
// IC CLASS FUNCTIONS
// ==============================================================================

/**
 * @brief Base class to exploit the functionnality of this linear potentiometer.
 *
 */
class MCP45HV51
{
private:
    uint8_t address;
    I2C_Bus I2C;

public:
    /**
     * @brief Construct a new MCP45HV51 object
     *
     * @param[in] I2C A pointer to the I2C struct that is used to handle IO operation on this bus.
     * @param[in] address The address of the IC on the I2C bus.
     */
    MCP45HV51(const I2C_Bus* I2C, const LIN_POTI address);

    /**
     * @brief Destroy the MCP45HV51 object
     *
     */
    ~MCP45HV51();

    /**
     * @brief Configure the operating mode of the potentiometer
     *
     * @param[in] HardwareShutdownMode Pin Shutdown has an effect on the IC (0 to disable shutdown, 1 to enable shutdown)
     * @param[in] R0A Connect the A terminal to the resistor network. (1 to enable, 0 to disable)
     * @param[in] R0W Connect the W terminal to the resistor network. (1 to enable, 0 to disable)
     * @param[in] R0B Connect the B terminal to the resistor network. (1 to enable, 0 to disable)
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     * @test Function to test !
     */
    int ConfigurePotentiometer(const int HardwareShutdownMode,
                               const int R0A,
                               const int R0W,
                               const int R0B);

    /**
     * @brief Write a value to the potentiometer.
     *
     * @param[in] Value The value to be written to the potentiometer.
     *
     * @return  0 : OK
     * @return -1 : Invalid Value
     * @return -2 : IOCTL error.
     *
     * @test Function to test !
     */
    int WriteWiper(const int Value);

    /**
     * @brief Return the Poti value
     *
     * @param[out] Value A pointer to an integer to store the value
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     * @test Function to test !
     */
    int ReadWiper(int* const Value);

    /**
     * @brief Increment the wiper value
     *
     * @return  0 : OK
     * @return -1 : IOCTL error (the wiper may be at one end !! --> Generate a NACK)
     *
     * @test Function to test !
     */
    int IncrementWiper();

    /**
     * @brief Decrement the wiper value
     *
     * @return  0 : OK
     * @return -1 : IOCTL error (the wiper may be at one end !! --> Generate a NACK)
     *
     * @test Function to test !
     */
    int DecrementWiper();
};