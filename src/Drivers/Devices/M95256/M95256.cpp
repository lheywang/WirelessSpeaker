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

#include "../../SPI/SPI.hpp"
#include "M95256.hpp"
#include <cstdlib>
#include <iostream>
#include <cerrno>
#include <cstring>

// ==============================================================================
// PRIVATE DEFINES
// ==============================================================================
#define WREN 0x06  // No following data
#define WRDI 0x04  // No following data
#define RDSR 0x05  // No following data
#define WRSR 0x01  // No following data
#define READ 0x03  // 2 bytes address page
#define WRITE 0x02 // 2 bytes address page

// ==============================================================================
// FUNCTIONS
// ==============================================================================

M95256::M95256(const SPI_Bus *SPI)
{
    this->SPI = *SPI;
    return;
}

M95256::~M95256()
{
    return;
}

int M95256::WriteEnable()
{
    int buf[3] = {0};
    int res = 0;

    buf[0] = WREN;

    res = SPI_Transfer(&this->SPI, buf, buf, 1);

    if (res != 0)
        return -1;
    return 0;
}

int M95256::WriteDisable()
{
    int buf[3] = {0};
    int res = 0;

    buf[0] = WRDI;

    res = SPI_Transfer(&this->SPI, buf, buf, 1);

    if (res != 0)
        return -1;
    return 0;
}

int M95256::ReadStatus(int *const WriteProtectStatus,
                       int *const ProtectedBlock,
                       int *const WriteEnable,
                       int *const WriteInProgress)
{
    int buf[3] = {0};
    int res = 0;

    buf[0] = RDSR;

    res = SPI_Transfer(&this->SPI, buf, buf, 1);

    if (res != 0)
        return -1;

    *WriteProtectStatus = (buf[0] & 0x80) >> 7;
    *ProtectedBlock = (buf[0] & 0x0C) >> 2;
    *WriteEnable = (buf[0] & 0x02) >> 1;
    *WriteInProgress = buf[0] & 0x01;

    return 0;
}

int M95256::WriteStatus(const int WriteProtectStatus,
                        const int ProtectedBlock)
{
    if ((0 > ProtectedBlock) | (ProtectedBlock > 0x03))
        return -1;

    int buf[3] = {0};
    int res = 0;

    buf[0] = (bool)WriteProtectStatus;
    buf[0] = buf[0] << 4 | ProtectedBlock;
    buf[0] = buf[0] << 2;

    res = SPI_Transfer(&this->SPI, buf, buf, 1);

    if (res != 0)
        return -2;
    return 0;
}

int M95256::Read(const int Address, int *const Data, const int Len)
{
    if ((0 > Address) | (Address > MAX_ADDRESS))
        return -1;
    if ((Address + Len) > MAX_ADDRESS)
        return -2;

    int res = 0;
    int *buf = (int *)malloc((sizeof(int) * (Len + 3)));
    if (buf == 0)
    {
        std::cerr << "[ M95256 ][ Read ] Could not allocate memory for read operation "
                  << strerror(errno)
                  << std::endl;
        return -1;
    }

    memset(buf, 0x00, (sizeof(int) * (Len + 1)));
    buf[0] = READ;
    buf[1] = Address & 0xFF00;
    buf[2] = Address & 0x00FF;

    res = SPI_Transfer(&this->SPI, buf, buf, 1);

    for (int i = 0; i < Len; i++)
        Data[i] = buf[i + 3];

    if (res != 0)
    {
        free(buf);
        return -3;
    }

    free(buf);
    return 0;
}

int M95256::Write(const int Address, int *const Data, const int Len)
{
    if ((0 > Address) | (Address > MAX_ADDRESS))
        return -1;
    if ((Address + Len) > MAX_ADDRESS)
        return -2;

    int res = 0;
    int *buf = (int *)malloc((sizeof(int) * (Len + 3)));
    if (buf == 0)
    {
        std::cerr << "[ M95256 ][ Write ] Could not allocate memory for read operation "
                  << strerror(errno)
                  << std::endl;
        return -1;
    }

    buf[0] = WRITE;
    buf[1] = Address & 0xFF00;
    buf[2] = Address & 0x00FF;
    memcpy(&buf[3], Data, Len * sizeof(int));

    res = SPI_Transfer(&this->SPI, buf, buf, 1);

    if (res != 0)
    {
        free(buf);
        return -2;
    }

    free(buf);
    return 0;
}