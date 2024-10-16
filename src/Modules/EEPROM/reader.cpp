/**
 * @file reader.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define the tool that is used to read the data back from the eeprom, and parse it if required.
 * @version 0.1
 * @date 2024-10-15
 *
 * @copyright Copyright (c) 2024
 *
 */
#include "eeprom.hpp"
#include "../libcrc/checksum.h"

#include <iostream>

int EEPROM_ReadHeaderV1(M95256 Slave, EEPROM_HEADER_V1 *const Header)
{
    // Alocate the data
    uint8_t *buf = (uint8_t *)malloc(HEADER_SIZE);
    memset(buf, 0x00, HEADER_SIZE);

    // Read the data and put it on the structure
    int res = Slave.Read(HEADER_ADDRESS, buf, HEADER_SIZE);
    if (res < 0)
        return -1;
    memcpy(Header, buf, HEADER_SIZE);

    // CRC Check
    uint16_t read_CRC = Header->HeaderCRC16;
    Header->HeaderCRC16 = 0xAAAA; // Set the dummy value to ensure integrity of the computation.
    memcpy(buf, Header, HEADER_SIZE);
    uint16_t calc_CRC = crc_16(buf, HEADER_SIZE);

    // Free memory
    free(buf);

    if (read_CRC != calc_CRC)
        return -2;
    return 0;
}

int EEPROM_ReadConfigV1(M95256 Slave, CONFIG_V1 *const Data)
{
    return 0;
}