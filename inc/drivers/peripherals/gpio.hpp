/**
 * @file GPIO.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Header for custom GPIO functions, that rely on the linux kernel functions.
 * @version 1.0
 * @date 2024-10-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
// ==============================================================================
// INCLUDES
// ==============================================================================

#include "core/clk.hpp"
#include <linux/gpio.h>
#include <string>

// ==============================================================================
// PUBLIC DEFINES
// ==============================================================================
static constexpr const char* DEV_NAME = "/dev/gpiochip0";

/*! Define user accessibles pins on the speaker. */
enum class PINS
{
    AMP1_FAULT = 17, /*!< Amplifier 1 active low fault signal*/
    AMP2_FAULT = 27, /*!< Amplifier 2 active low fault signal*/
    AMP3_FAULT = 22, /*!< Amplifier 3 active low fault signal*/
    POWER_INT = 16, /*!< Power subsystem fault active low signal */
    aRGB_TOP = 6, /*!< Addressable RGB for WS2812 leds (top)*/
    aRGB_FRONT = 13, /*!< Addressable RGB for WS2812 leds (front)*/
    EXT_INT = 5, /*!< Active low interrupt signal from the exterior ??*/
    TOUCH_INT = 26, /*!< Active low interrupt signal from the capacitive touch sensor*/
    NWRITE = 15, /*!< TEMP VALUES !!!!*/
    NHOLD = 14, /*!< TEMP VALUES !!!!*/
};

/*! Define values for the operating modes of the GPIO */
enum class GPMODES
{
    INPUT = 0x00, /*!< Input*/
    OUTPUT = 0x01, /*!< Output*/
};

/*! Define GPIO structure used within our project */
struct GPIO
{
    unsigned int
        PinNumber; /*!< The number of the GPIO that is used. WARNING : This is BCM Convention and not RPi one.*/

    GPMODES Mode; /*!< A mode indicator, used to block incorrects requests.*/
    bool
        InOut; /*!< Boolean that store the direction of this GPIO. Take True if set as Output. Given by the kernel / hardware*/
    bool Polarity; /*!< Boolean to store the polarity of the GPIO. Take True if active low.*/
    int Type; /*!< Integer that take different values depending on the type of the electrical type. (1 if Open-Drain, 2 if Open-Source, 0 if neither)*/
    int Kernel; /*!< Integer set to 1 if the Linux kernel is using it.*/

    char Name
        [GPIO_MAX_NAME_SIZE]; /*!< A custom string to describe to which function this GPIO is used.*/
    char FuncName
        [GPIO_MAX_NAME_SIZE]; /*!< A string that store the function identifier that is currently linked to.*/
};

// ==============================================================================
// FUNCTIONS
// ==============================================================================

/**
 * @brief Return the informations of a specific GPIO Pin.
 *
 * @param[in] Pin A PINS enum member to designate a pin
 * @param[in] Mode A GPMODES enum member to designate the mode
 *
 * @return GPIO struct for further operations.
 */
GPIO* GPIO_GetInfos(const PINS Pin, const GPMODES Mode);

/**
 * @brief Close a GPIO Handle.
 *
 * @param[in] info A GPIO struct to be closed.
 *
 * @return  0 : OK
 */
int GPIO_Close(GPIO* info);

/**
 * @brief Read the status of a GPIO.
 *
 * @warning Define the GPIO as Input, thus at High-Z state.
 *
 * @param[inout] info A GPIO struct that contain at least the GPIO number.
 * @param[out] status Pointer to an int that store the GPIO read value.
 *
 * @return  0 : OK
 * @return -1 : Incorrect pin mode.
 * @return -1 : Failed to open the dev file
 * @return -2 : Failed to read the dev file
 * @return -3 : Failed to read the state of the GPIO
 */
int GPIO_Read(GPIO* info, int* const status);

/**
 * @brief Write the status to a GPIO.
 *
 * @warning Define the GPIO as Output, with active LOW by default.
 *
 * @param[inout] info A GPIO struct that contain at least the GPIO number.
 * @param[in] Status An integer to set the value. 0 = OFF_STATE, anything other will be ON_STATE.
 *
 * @return  0 : OK
 * @return -1 : Incorrect pin mode.
 * @return -2 : Failed to open the dev file
 * @return -3 : Failed to read the dev file
 * @return -4 : Failed to write the state of the GPIO
 */
int GPIO_Write(GPIO* info, const int Status);
