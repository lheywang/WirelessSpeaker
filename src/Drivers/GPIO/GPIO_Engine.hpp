// ==============================================================================
//                              GPIO/GPIO.hpp
//                              Wrote by lheywang
//
// Define our basic I2C settings on the boards, such as :
// - Pins usage
// ==============================================================================

// Only included one time
#pragma once
// ==============================================================================
// INCLUDES
// ==============================================================================
#include <linux/gpio.h>

/**
 * @struct GPIO
 * @brief GPIO struct, used as base handle for GPIO manipulations.
 *        This is custom struct for our needs.
 *
 * @var GPIO::PinNumber The number of the GPIO that is used. WARNING : This is BCM Convention and not RPi one.
 * @var GPIO::FuncName A custom string to describe to which function this GPIO is used.
 * @var GPIO::InOut Boolean that store the direction of this GPIO. Take True if set as Output.
 * @var GPIO::Polarity Boolean to store the polarity of the GPIO. Take True if active low.
 * @var GPIO::Type Integer that take different values depending on the type of the electrical type. (1 if Open-Drain, 2 if Open-Source, 0 if neither)
 * @var GPIO::Kernel Integer set to 1 if the Linux kernel is using it.
 * @var GPIO::Used A boolean to identify which GPIO are used by another code. Is filled by any definition functions.
 * @var GPIO::FuncName A string that store the function identifier that is currently linked to.
 *
 */
struct GPIO
{
    unsigned int PinNumber;

    bool InOut;
    bool Polarity;
    int Type;
    int Kernel;

    char Name[GPIO_MAX_NAME_SIZE];
    char FuncName[GPIO_MAX_NAME_SIZE];

    bool Used;
};

/**
 * @brief Return the GPIOChip infos.
 *
 * @param[inout] info A gpiochip_info struct that is going to be filled by the function call.
 *
 * @return  0 : OK
 * @return -1 : Error while openning the DEV_NAME file
 * @return -2 : Error while fetching the data on the file
 */
int GetGPIOChipInfos(gpiochip_info *info);

/**
 * @brief Return the informations of a specific GPIO Pin.
 *
 * @param[inout] info A GPIO struct to be filled with the returned infos.
 *
 * @return
 */
int GetGPIOInfo(GPIO *info);

/**
 * @brief Read the status of a GPIO.
 *
 * @warning Define the GPIO as Input, thus at High-Z state.
 *
 * @param[inout] info A GPIO struct that contain at least the GPIO number.
 * @param[out] status Pointer to an int that store the GPIO read value.
 *
 * @return  0 : OK
 * @return -1 : Failed to open the dev file
 * @return -2 : Failed to read the dev file
 * @return -3 : Failed to read the state of the GPIO
 */
int ReadGPIO(GPIO *info, int *const status);

/**
 * @brief Write the status to a GPIO.
 *
 * @warning Define the GPIO as Output, with active LOW by default.
 *
 * @param[inout] info A GPIO struct that contain at least the GPIO number.
 * @param[in] Status An integer to set the value. 0 = OFF_STATE, anything other will be ON_STATE.
 *
 * @return  0 : OK
 * @return -1 : Failed to open the dev file
 * @return -2 : Failed to read the dev file
 * @return -3 : Failed to write the state of the GPIO
 */
int WriteGPIO(GPIO *info, const int Status);
