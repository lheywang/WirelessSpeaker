/**
 * @file SPI.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define the global SPI Interface for the board
 * @version 0.1
 * @date 2024-10-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

#include "SPI_Engine.hpp"
#include "structs/Struct.hpp"
#include "linux/spi/spidev.h"

// ==============================================================================
// CONSTANTS
// ==============================================================================

/**
 * @brief Define SPI Bus operating parameters.
 *
 * @enumvalue SPI_SETTINGS::BUS_SPEED Define SCLK Frequency
 * @enumvalue SPI_SETTINGS::BUS_WORD_SIZE Define number of bits per cycle
 * @enumvalue SPI_SETTINGS::BUS_MODE Define SPI Mode.
 * @enumvalue SPI_SETTINGS::BUS_MAX_CS Define the maximal number of CS. Selected by the device tree.
 * @enumvalue SPI_SETTINGS::BUS_NUMBER Define the bus number, defined by RPi design.
 */
enum class SPI_SETTINGS
{
    BUS_SPEED = 20'000'000,
    BUS_WORD_SIZE = 8,
    BUS_MODE = SPI_MODE_0,
    BUS_MAX_CS = 1,
    BUS_NUMBER = 0,
};
