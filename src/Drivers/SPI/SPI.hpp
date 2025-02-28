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
#include "linux/spi/spidev.h"

// ==============================================================================
// CONSTANTS
// ==============================================================================

/*! Define parameters of the SPI bus */
enum class SPI_SETTINGS
{
    BUS_SPEED = 500'000, /*!< Bus speed (20 MHz)*/
    BUS_WORD_SIZE = 8, /*!< Bus word size (8 bits)*/
    BUS_MODE = SPI_MODE_0, /*!< Bus mode (= 0 : CPOL = 0 and CPHA = 0)*/
    BUS_MAX_CS = 2, /*!< Number of CS : 1*/
    BUS_NUMBER = 0, /*!< Bus number : 0*/
};
