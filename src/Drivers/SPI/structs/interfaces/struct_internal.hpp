/**
 * @file struct_internal.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define internal behaviors of the speaker
 * @version 0.1
 * @date 2024-10-08
 *
 * @copyright Copyright (c) 2024
 *
 */

// Only included one time
#pragma once

// Libs
#include <iostream>
#include <cstdint>

/*! Define values that are stored on the EEPROM for the temperature sensor */
struct Temperature
{
    uint16_t Maximal_Temperature; /*!< Define maximal temperature before triggering an interrupt*/
    uint16_t Minimal_Temperature; /*!< Define minimal temperature before triggering an interrupt*/
};
