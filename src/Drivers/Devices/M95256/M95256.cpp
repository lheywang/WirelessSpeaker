/**
 * @file M95256.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief  Source file for our eeprom
 * @version 0.1
 * @date 2024-10-09
 *
 * @copyright Copyright (c) 2024
 *
 */

// ==============================================================================
// PRIVATE DEFINES
// ==============================================================================
#define WREN 0x06  // No following data
#define WRDI 0x04  // No following data
#define RDSR 0x05  // No following data
#define WRSR 0x01  // No following data
#define READ 0x03  // 2 bytes address page
#define WRITE 0x02 // 2 bytes address page