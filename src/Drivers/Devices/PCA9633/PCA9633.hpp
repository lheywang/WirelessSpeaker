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
#define GRPPPWM 0x06
#define GRPFREQ 0x07
#define LEDOUT 0x08
#define SUBADDR1 0x09
#define SUBADDR2 0x0A
#define SUBADDR3 0x0B
#define ALLCALLADR 0x0C

// OE Status
#define LED_OFF 0x00
#define LED_ON 0x01
#define LED_IN 0x02
#define LED_PWM 0x02
#define LED_PWM_GLOB 0x03

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
    PCA9633(const I2C_Bus *I2C, const int address);

    /**
     * @brief Destroy the PCA9633 object
     *
     */
    ~PCA9633();

    /**
     * @brief Configure the IC.
     *
     * @param[in] Mode Configure Low Power or Active IC mode. (1 for active, 0 for LP)
     * @param[in] SubAddr1Response The IC respond to Sub Address 1 commands. (1 to enable, 0 to disable)
     * @param[in] SubAddr2Response The IC respond to Sub Address 2 commands. (1 to enable, 0 to disable)
     * @param[in] SubAddr3Response The IC respond to Sub Address 3 commands. (1 to enable, 0 to disable)
     * @param[in] AllAddrResponse The IC respond to Sub address ALL commands. (1 to enable, 0 to disable)
     * @param[in] Dimming Enable or Disable LED blinking or dimming (0 for dimming, 1 for blinking)
     * @param[in] Inverter Select LED polarity. (1 to invert logic, 0 to let by default)
     * @param[in] Change Select if device apply the commands at the ACK or the STOP on I2C bus (0 on STOP, 1 on ACK)
     * @param[in] OutputDriver Configure the output scheme. (0 for open drain, 1 for totem-pole)
     * @param[in] OEStatus Select the nOE behaviour. Accepted values within the range of the defined.
     *
     * @return  0 : OK
     * @return -1 : Incorrect OEStatus value
     * @return -2 : IOCTL error.
     *
     */
    int Configure(const int Mode,
                  const int SubAddr1Response,
                  const int SubAddr2Response,
                  const int SubAddr3Response,
                  const int AllAddrResponse,
                  const int Dimming,
                  const int Inverter,
                  const int Change,
                  const int OutputDriver,
                  const int OEStatus);

    /**
     * @brief Configure the duty cycle.
     *        Support the configuration of multiple channels in one function call.
     *        The same value will be copied.
     *
     * @param[in] FirstChannel The first channel to be configured.
     * @param[in] Value Pointer to the value to be defined. May be an array of multiple elements.
     * @param[in] AutoIncrement Set to the number of channel to set. By default 1, for 1 channel.
     *                      Up to four channel may be configured, depending on the first channel.
     *
     * @return  0 : OK
     * @return -1 : First channel incorrect value
     * @return -2 : Invalid AutoIncrement value (Too big or 0).
     * @return -3 : IOCTL error.
     */
    int ConfigureDutyCycle(const int FirstChannel, int *const Value, const int AutoIncrement = 1);

    /**
     * @brief Configure the global dimming circuitry on the chip.
     *        This include a Dimming or Blinking engine
     * @warning Theses settings meaning depend on global IC configuration.
     *
     * @param[in] DutyCycle The requested Duty Cycle
     * @param[in] Period The requested period in count of 41 ms (0 = 0s, 255 = 10.83s).
     *
     * @return  0 : OK
     * @return -1 : Invalid Duty Cycle value
     * @return -2 : Invalid Period value
     * @return -3 : IOCTL error.
     */
    int ConfigureGlobalDimming(const int DutyCycle, const int Period);

    /**
     * @brief Configure the leds action mode.
     *        LED_ON, LED_OFF, LED_PWM (individual control only) and LED_PWM_GLOB are accepted.
     *
     * @param[in] LED1 Setting for the LED1.
     * @param[in] LED2 Setting for the LED2.
     * @param[in] LED3 Setting for the LED3.
     * @param[in] LED4 Setting for the LED4.
     *
     * @return  0 : OK
     * @return -1 : Invalid value for a LED setting.
     * @return -2 : IOCTL error.
     */
    int SetLedStatus(const int LED1, const int LED2, const int LED3, const int LED4);

    /**
     * @brief Configure a Subaddress of the IC.
     *
     * @param[in] SUBADDR The configured subaddress.
     * @param[in] address The value of this address.
     *
     * @return  0 : OK
     * @return -1 : Invalid SUBADDR
     * @return -2 : Invalid address
     * @return -3 : IOCTL error.
     */
    int ConfigureSubAddress(const int SUBADDR, const int address);
};