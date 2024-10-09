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
#define EEPROM_STRUCT_UL_SIZE sizeof(Config) * 4
#define EEPROM_SIZE 256'000
#define BUS_SPEED 20'000'000
#define BUS_WORD_SIZE 8
#define BUS_MODE SPI_MODE_0
#define BUS_MAX_CS 1
#define BUS_NUMBER 0

// ==============================================================================
// CS
// ==============================================================================
#define EEPROM 0
#define NONE 1 // Unused. Using it does nothing.