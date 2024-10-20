/**
 * @file struct_automated_interfaces.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define the user accessible interfaces that are managed automatically behaviors.
 * @version 0.1
 * @date 2024-10-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <cstdint>

/*! Define values that are stored on the EEPROM for the USB-C PD3 Interface*/
struct BasicPDO
{
    uint8_t Voltage[2]; /*!< Voltage requested for this PDO. Form is Int.Float, with float a number of 20 mV steps.*/
    uint8_t Current[2]; /*!< Current requested for this PDO. Form is Int.Float, with float a number of 50 mA steps.*/
    uint8_t EnablePPS;  /*!< Enable PPS (Programmable Power Supply)*/
};