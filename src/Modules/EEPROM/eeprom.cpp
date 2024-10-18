/**
 * @file eeprom.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define source for the EEPROM functions
 * @version 0.1
 * @date 2024-10-17
 *
 * @copyright Copyright (c) 2024
 *
 */

// Includes
#include "eeprom.hpp"
#include "../libcrc/checksum.h"
#include "../../Drivers/Devices/M95256/M95256.hpp"

#include <iostream>
#include <stdexcept>

// CONSTRUCTORS
EEPROM::EEPROM(bool ForceWrite)
{
    // Open a new SPI device
    this->SPI = SPI_GetInfos();
    if (this->SPI == nullptr)
        throw std::runtime_error("[ M95256 ][ CONSTRUCTOR ] : Failed to allocate memory for the SPI obect");

    // Open a new slave
    this->Slave = M95256(this->SPI);

    this->Header = new EEPROM_HEADER_V1;
    if (this->Header == nullptr)
        throw std::runtime_error("[ EEPROM ][ CONSTRUCTOR ] : Failed to allocate memory for the HEADER obect");

    int ret = this->ReadHeaderV1();
    if (ret != 0)
    {
        if (ForceWrite == true)
        {
            memcpy(this->Header, &DEFAULT_HEADER_V1, HEADER_SIZE);
            this->WriteHeaderV1();
            std::clog << "[ EEPROM ][ CONSTRUCTOR ] : Failed to read the header. Default one was wrote. Error code was : " << ret << std::endl;
        }
        else
            throw std::runtime_error("[ EEPROM ][ CONSTRUCTOR ] : Failed to read header from the EEPROM");
    }

    return;
}

// DESCTRUCTORS
EEPROM::~EEPROM()
{
    delete this->Header;
    return;
}

// PRIVATE
int EEPROM::ReadHeaderV1() // OK
{
    // Alocate the data
    uint8_t *buf = (uint8_t *)malloc(HEADER_SIZE);
    if (buf == nullptr)
        return -1;

    // Copy the data
    memset(buf, 0x00, HEADER_SIZE);

    // Read the data and put it on the structure
    int res = this->Slave.Read(HEADER_ADDRESS, buf, HEADER_SIZE);
    if (res < 0)
        return -2;
    memcpy(this->Header, buf, HEADER_SIZE);

    // CRC Check
    uint16_t read_CRC = Header->HeaderCRC16;
    this->Header->HeaderCRC16 = 0xAAAA; // Set the dummy value to ensure integrity of the computation.

    memcpy(buf, this->Header, HEADER_SIZE);
    uint16_t calc_CRC = crc_16(buf, HEADER_SIZE);

    // Free memory
    free(buf);

    if (read_CRC != calc_CRC)
        return -3;
    return 0;
}

int EEPROM::WriteHeaderV1() // OK
{
    // Creating a buffer value
    uint8_t *buf = (uint8_t *)malloc(HEADER_SIZE);
    if (buf == nullptr)
        return -1;
    memset(buf, 0x00, HEADER_SIZE);

    // Set a dummy value on the CRC16 field and copy the data to an array of uint8_t.
    this->Header->HeaderCRC16 = 0xAAAA;
    memcpy(buf, Header, HEADER_SIZE);

    // Compute the CRC
    uint16_t calc_CRC = crc_16(buf, HEADER_SIZE);
    this->Header->HeaderCRC16 = calc_CRC;

    // Copying the data
    memcpy(buf, this->Header, HEADER_SIZE);

    // Write the data (one write per 64 bytes, per page !)
    int ret = 0;
    ret += this->Slave.Write(HEADER_ADDRESS, &buf[0], PAGE_SIZE);
    ret += this->Slave.Write((HEADER_ADDRESS + PAGE_SIZE), &buf[PAGE_SIZE], PAGE_SIZE);
    free(buf);

    // Returns
    if (ret < 0)
        return -2;
    return 0;
}
int EEPROM::SetConfigCRC(const uint16_t CRC)
{
    this->Header->ConfigCRC16 = CRC;
    return 0;
}
int EEPROM::GetConfigCRC(uint16_t *const CRC)
{
    *CRC = this->Header->ConfigCRC16;
    return 0;
}

// PUBLIC
int EEPROM::GetHeaderV1(EEPROM_HEADER_V1 *const Header) // OK
{
    memcpy(Header, this->Header, HEADER_SIZE); // The header was cached, thus we don't bother reading it over SPI.
    return 0;
}

int EEPROM::WriteConfigV1(CONFIG_V1 *const Data)
{
    // Creating a buffer value and cop
    uint8_t *buf = (uint8_t *)malloc(CONFIG_SIZE);
    if (buf == nullptr)
        return -1;
    memcpy(buf, Data, CONFIG_SIZE);

    // Compute the CRC
    uint16_t calc_CRC = crc_16(buf, CONFIG_SIZE);
    std::cout << "computed CRC : " << calc_CRC << std::endl;

    this->SetConfigCRC(calc_CRC);
    this->WriteHeaderV1();

    // Write the data (one write per 64 bytes, per page !) and free the buffer.
    int ret = 0;
    for (int i = 0; i < CONFIG_SIZE; i += PAGE_SIZE)
    {
        uint8_t *ptr = &buf[i];
        std::cout << "Writing EEPROM at address " << std::dec << CONFIG_ADDRESS + i << std::endl;
        std::cout << "Address of passed buf : " << std::hex << (long *)ptr << std::endl;

        for (int ii = 0; ii < PAGE_SIZE; ii++)
            std::cout << std::hex << (int)buf[ii + i] << "-";
        std::cout << std::endl;

        ret += this->Slave.Write((CONFIG_ADDRESS + i), &buf[i], PAGE_SIZE);
        std::cout << std::endl;
        usleep(1000);
    }
    free(buf);

    // Returns
    if (ret < 0)
        return -2;
    return 0;
}

int EEPROM::ReadConfigV1(CONFIG_V1 *const Data)
{
    // Alocate the data
    uint8_t *buf = (uint8_t *)malloc(CONFIG_SIZE);
    if (buf == nullptr)
        return -1;
    // Copy the data
    memset(buf, 0x00, CONFIG_SIZE);

    // Read the data and put it on the structure
    int res = this->Slave.Read(CONFIG_ADDRESS, buf, CONFIG_SIZE);
    if (res < 0)
        return -2;
    memcpy(Data, buf, CONFIG_SIZE);

    // CRC Check
    uint16_t calc_CRC = crc_16(buf, CONFIG_SIZE);
    uint16_t read_CRC = 0;
    this->GetConfigCRC(&read_CRC);

    // Free memory
    free(buf);

    if (read_CRC != calc_CRC)
        return -3;
    return 0;
}

int EEPROM::UpdateHeaderV1(EEPROM_HEADER_V1 *Src, EEPROM_HEADER_V1 *Dest)
{
    return 0;
}

int EEPROM::UpdateConfigV1(CONFIG_V1 *Src, CONFIG_V1 *Dest)
{
    return 0;
}
