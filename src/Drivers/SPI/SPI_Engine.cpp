/**
 * @file SPI_Engine.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source for the SPI HAL.
 * @version 0.1
 * @date 2024-10-08
 *
 * @copyright Copyright (c) 2024
 *
 */

// ==============================================================================
// INCLUDES
// ==============================================================================
#include "SPI.hpp"

#include <cstdint>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

// ==============================================================================
// FUNCTIONS
// ==============================================================================

SPI_Bus* SPI_GetInfos()
{
    SPI_Bus* SPI = new SPI_Bus;

    // Set up variables
    SPI->CS_number = (int)SPI_SETTINGS::BUS_MAX_CS - 1;
    SPI->SPI_Bus = (int)SPI_SETTINGS::BUS_NUMBER;

    snprintf(SPI->SPI_Filename,
             sizeof(SPI->SPI_Filename),
             "/dev/spidev%d.%d",
             SPI->SPI_Bus,
             SPI->CS_number);
    SPI->SPI_Filename[sizeof(SPI->SPI_Filename) - 1] = '\0';

    // Open the file
    SPI->SPI_file = open(SPI->SPI_Filename, O_RDWR);

    if(SPI->SPI_file < 0)
    {
        std::cerr << "[ SPI ][ GetInfos ] : Could not open the requested SPI bus : "
                  << strerror(errno) << std::endl;
        SPI->SPI_file = (int)NULL;
    }

    return SPI;
}

int SPI_Close(SPI_Bus* SPI)
{
    close(SPI->SPI_file);
    delete SPI;
    return 0;
}

int SPI_Configure(SPI_Bus* SPI, int Mode, int WordSize, int Speed)
{
    int res = 0;

    // Configure the modes
    res = ioctl(SPI->SPI_file, SPI_IOC_WR_MODE, &Mode);
    if(res < 0)
    {
        std::cerr << "[ SPI ][ ConfigureBUS ] : Could not set the write mode on " << SPI->SPI_Bus
                  << " : " << strerror(errno) << std::endl;
        return -1;
    }
    res = ioctl(SPI->SPI_file, SPI_IOC_RD_MODE, &Mode);
    if(res < 0)
    {
        std::cerr << "[ SPI ][ ConfigureBUS ] : Could not set the read mode on " << SPI->SPI_Bus
                  << " : " << strerror(errno) << std::endl;
        return -1;
    }

    // Configure the word lengh
    res = ioctl(SPI->SPI_file, SPI_IOC_WR_BITS_PER_WORD, &WordSize);
    if(res < 0)
    {
        std::cerr << "[ SPI ][ ConfigureBUS ] : Could not set the write word lengh on "
                  << SPI->SPI_Bus << " : " << strerror(errno) << std::endl;
        return -2;
    }
    res = ioctl(SPI->SPI_file, SPI_IOC_RD_BITS_PER_WORD, &WordSize);
    if(res < 0)
    {
        std::cerr << "[ SPI ][ ConfigureBUS ] : Could not set the read word lengh  on "
                  << SPI->SPI_Bus << " : " << strerror(errno) << std::endl;
        return -2;
    }

    // Configure SPI Speeds
    res = ioctl(SPI->SPI_file, SPI_IOC_WR_MAX_SPEED_HZ, &Speed);
    if(res < 0)
    {
        std::cerr << "[ SPI ][ ConfigureBUS ] : Could not set the write speed on" << SPI->SPI_Bus
                  << " : " << strerror(errno) << std::endl;
        return -3;
    }
    res = ioctl(SPI->SPI_file, SPI_IOC_RD_MAX_SPEED_HZ, &Speed);
    if(res < 0)
    {
        std::cerr << "[ SPI ][ ConfigureBUS ] : Could not set the read speed on " << SPI->SPI_Bus
                  << " : " << strerror(errno) << std::endl;
        return -3;
    }

    // Store configuration settings for future use.
    SPI->speed = (unsigned int)Speed;
    SPI->tx_nbits = (unsigned char)1;
    SPI->rx_nbits = (unsigned char)1;
    SPI->bits = (unsigned char)WordSize;
    SPI->change = (unsigned char)0;
    SPI->delay = (unsigned char)0;

    return 0;
}
