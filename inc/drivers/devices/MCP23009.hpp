/**
 * @file MCP23009.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief MCP23009 Base class.
 * @version 1.0
 * @date 2024-10-02
 *
 * @copyright Copyright (c) 2024
 *
 * @remark Class was tested successfully on 07/10/2024.
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
 * @brief MCP23009 base class, to exploit the basics functions of this I2C GPIO port.
 *
 */
class MCP23009
{
private:
    uint8_t address;
    I2C_Bus I2C;

public:
    /**
     * @brief Construct a new MCP23009 object
     *
     * @param[in] I2C A pointer to the I2C struct that is used to handle IO operation on this bus.
     * @param[in] address The address of the IC on the I2C bus.
     */
    MCP23009(const I2C_Bus* I2C, const GPIO_EXPANDER address);

    /**
     * @brief Destroy the MCP23009 object
     *
     */
    ~MCP23009();

    /**
     * @brief Configure the GPIO of the IC
     *
     * @param[in] Direction Set the direction (Input or Output) of the port. This value is an 8b mask : 1 for input, 0 for output.
     * @param[in] Polarity Set the polarity of the Inputs ! This value is an 8b mask. If set to 1, the value read will be inverted.
     * @param[in] EnablePullUps Enable or Disable pull ups on the GPIO ports. This value is an 8b mask. 1 to enable the pull up.
     * @param[in] EnableInterrupts Enable or Disable the Interrupts on change for the pins. This value is an 8b mask. Warning : This require some further configuration.
     * @param[in] IOC Enable the IOC module. This is an 8b mask. If set to 0, the value is compared to it's previous state. Otherwise, it's compared to the default value.
     * @param[in] DefaultValue Default value to be compared for the Interrupt based on comparison.
     *
     * @return  0 : OK
     * @return -1 : Invalid Direction
     * @return -2 : Invalid Polarity
     * @return -3 : Invalid Pull Ups
     * @return -4 : Invalid Interrupt Enable
     * @return -5 : Invalid IOC
     * @return -6 : Invalid default value
     * @return -7 : IOCTL error.
     */
    int ConfigureGPIO(const int Direction,
                      const int Polarity,
                      const int EnablePullUps,
                      const int EnableInterrupts,
                      const int IOC,
                      const int DefaultValue);

    /**
     * @brief Configure the IC
     *
     * @remark Others parameters are defined by the function itself since their configuration is trivial in our case.
     *
     * @param[in] INTPinMode Configure the INT as Open drain (1) or totem pole (0)
     * @param[in] INTPolarity Configure the active state for the INT Pin : Active Low (0), Active High (1)
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int Configure(const int INTPinMode, const int INTPolarity);

    /**
     * @brief Set the ouputs of the IC
     *
     * @param[in] Status An 8b value of the outputs to set.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int SetOutputs(const int Status);

    /**
     * @brief Read back the inputs status
     *
     * @param[out] Status Pointer to an int to store the 8b read value.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int ReadInputs(int* const Status);

    /**
     * @brief Read back the Interrupts status
     *
     * @param[out] INTFlags Pointer to an int to read back an 8b value whcich contain the Inputs that triggered an Input.
     * @param[out] PortValue Pointer to an int to contain the value of the Input port at the time of interrupt.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int ReadInterrupts(int* const INTFlags, int* const PortValue);
};