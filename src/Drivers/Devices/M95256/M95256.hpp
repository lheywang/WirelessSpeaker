/**
 * @file M95256.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Header file for our eeprom
 * @version 0.1
 * @date 2024-10-09
 *
 * @copyright Copyright (c) 2024
 *
 */

// ==============================================================================
// PUBLIC DEFINES
// ==============================================================================
#define MAX_ADDRESS 0x7FFF

#define SOFT_WP_DISABLED ((0 << 1) | 0)
#define SOFT_WP_UPPER_QUARTER ((0 << 1) | 1)
#define SOFT_WP_UPPER_HALF ((1 << 1) | 0)
#define SOFT_WP_FULL ((1 << 1) | 1)