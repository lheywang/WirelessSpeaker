/**
 * @file writter.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define the tool that is used to write data on the EEPROM.
 * @version 0.1
 * @date 2024-10-15
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "eeprom.hpp"

int WriteHeaderV1(EEPROM_HEADER_V1 *const Header)
{
    uint8_t *buf = (uint8_t *)malloc(sizeof(EEPROM_HEADER_V1));
    return 0;
}

int WriteConfigV1(ConfigV1 *const Data)
{
    return 0;
}
