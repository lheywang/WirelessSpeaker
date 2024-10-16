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
#include "../libcrc/checksum.h"

#include <iostream>

int EEPROM_WriteHeaderV1(M95256 Slave, EEPROM_HEADER_V1 *const Header)
{
    // Creating a buffer value
    uint8_t *buf = (uint8_t *)malloc(HEADER_SIZE);
    memcpy(buf, Header, HEADER_SIZE);

    // Compute the CRC
    uint16_t calc_CRC = crc_16(buf, HEADER_SIZE);
    Header->HeaderCRC16 = calc_CRC; // Overwrite the CRC value.

    std::cout << calc_CRC << std::endl;

    // Copying the data
    memcpy(buf, Header, HEADER_SIZE);

    // Write the data
    int ret = Slave.Write(HEADER_ADDRESS, buf, HEADER_SIZE);
    free(buf);

    // Returns
    if (ret < 0)
        return -1;
    return 0;
}

int EEPROM_WriteConfigV1(M95256 Slave, ConfigV1 *const Data)
{
    return 0;
}
