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

#define EEPROM_STRUCT_SIZE (sizeof(Config) * 4)
#define EEPROM_SIZE 256'000
#define EEPROM_VALID EEPROM_STRUCT_SIZE <= EEPROM_SIZE