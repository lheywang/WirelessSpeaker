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

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <cstdint>
#include <string.h>

#include <iostream>

// ==============================================================================
// FUNCTIONS
// ==============================================================================

SPI_Bus *SPI_GetInfos(int CS, int Bus)
{
    SPI_Bus *SPI = new SPI_Bus;

    if ((0 > CS) | (CS > BUS_MAX_CS))
    {
        fprintf(stderr, "[ SPI ][ GetInfos ] : Invalid Slave ID\n");
        SPI->SPI_file = -1;
        return SPI;
    }
    if ((0 > Bus) | (Bus > 0x01))
    {
        fprintf(stderr, "[ SPI ][ GetInfos ] : Invalid Bus Number\n");
        SPI->SPI_file = -1;
        return SPI;
    }

    // Set up variables
    SPI->CS_number = CS;
    SPI->SPI_Bus = Bus;

    snprintf(SPI->SPI_Filename, sizeof(SPI->SPI_Filename), "/dev/spidev%d.%d", SPI->SPI_Bus, SPI->CS_number);
    SPI->SPI_Filename[sizeof(SPI->SPI_Filename) - 1] = '\0';

    // Open the file
    SPI->SPI_file = open(SPI->SPI_Filename, O_RDWR);

    if (SPI->SPI_file < 0)
    {
        fprintf(stderr, "[ SPI ][ GetInfos ] : Could not open the requested SPI bus : %s\n", strerror(errno));
        SPI->SPI_file = (int)NULL;
    }

    return SPI;
}

int SPI_CloseDevice(SPI_Bus *SPI)
{
    close(SPI->SPI_file);
    delete SPI;
    return 0;
}

int SPI_ConfigureBUS(SPI_Bus *SPI, int Mode, int WordSize, int Speed)
{
    int res = 0;

    // Configure the modes
    res = ioctl(SPI->SPI_file, SPI_IOC_WR_MODE, &Mode);
    if (res < 0)
    {
        fprintf(stderr, "[ SPI ][ ConfigureBUS ] : Could not set the write mode on the SPI Bus %d : %s\n", SPI->SPI_Bus, strerror(errno));
        return -1;
    }
    res = ioctl(SPI->SPI_file, SPI_IOC_RD_MODE, &Mode);
    if (res < 0)
    {
        fprintf(stderr, "[ SPI ][ ConfigureBUS ] : Could not set the read mode on the SPI Bus %d : %s\n", SPI->SPI_Bus, strerror(errno));
        return -1;
    }

    // Configure the word lengh
    res = ioctl(SPI->SPI_file, SPI_IOC_WR_BITS_PER_WORD, &WordSize);
    if (res < 0)
    {
        fprintf(stderr, "[ SPI ][ ConfigureBUS ] : Could not set the write word lengh on the SPI Bus %d : %s\n", SPI->SPI_Bus, strerror(errno));
        return -2;
    }
    res = ioctl(SPI->SPI_file, SPI_IOC_RD_BITS_PER_WORD, &WordSize);
    if (res < 0)
    {
        fprintf(stderr, "[ SPI ][ ConfigureBUS ] : Could not set the read word lengh on the SPI Bus %d : %s\n", SPI->SPI_Bus, strerror(errno));
        return -2;
    }

    // Configure SPI Speeds
    res = ioctl(SPI->SPI_file, SPI_IOC_WR_MAX_SPEED_HZ, &Speed);
    if (res < 0)
    {
        fprintf(stderr, "[ SPI ][ ConfigureBUS ] : Could not set the write bus speed on the SPI Bus %d : %s\n", SPI->SPI_Bus, strerror(errno));
        return -3;
    }
    res = ioctl(SPI->SPI_file, SPI_IOC_RD_MAX_SPEED_HZ, &Speed);
    if (res < 0)
    {
        fprintf(stderr, "[ SPI ][ ConfigureBUS ] : Could not set the read bus speed on the SPI Bus %d : %s\n", SPI->SPI_Bus, strerror(errno));
        return -3;
    }

    // Store configuration settings for future use.
    SPI->speed = (unsigned int)Speed;
    SPI->tx_nbits = (unsigned char)1;
    SPI->rx_nbits = (unsigned char)1;
    SPI->bits = (unsigned char)WordSize;
    SPI->change = (unsigned char)0;
    SPI->delay = (unsigned char)1;

    return 0;
}

int SPI_Transfer(SPI_Bus *SPI, int *const InputBuffer, int *const OutputBufer, const int Len)
{
    // Allocate a unsigned long long buffer to store the data to be written.
    __u8 *TX = (__u8 *)malloc(sizeof(__u8) * Len);
    if (TX == 0)
    {
        fprintf(stderr, "[ SPI ][ Read ] : Could not allocate the input buffer : %s\n", strerror(errno));
        return -1;
    }
    // Let's copy all of the input data to the new one !
    for (int i = 0; i < Len; i++)
        TX[i] = (__u8)InputBuffer[i] << 1;

    // Allocate a unsigned long long buffer to the data to be rode.
    __u8 *RX = (__u8 *)malloc(sizeof(__u8) * Len);
    if (RX == 0)
    {
        fprintf(stderr, "[ SPI ][ Read ] : Could not allocate the output buffer : %s\n", strerror(errno));
        return -2;
    }
    memset(RX, 0x00, Len * sizeof(__u8));

    struct spi_ioc_transfer message =
        {
            .tx_buf = (unsigned long)TX,
            .rx_buf = (unsigned long)RX,
            .len = (unsigned int)Len,
            .speed_hz = SPI->speed,
            .delay_usecs = SPI->delay,
            .bits_per_word = SPI->bits,
            .cs_change = SPI->change,
            .tx_nbits = SPI->tx_nbits,
            .rx_nbits = SPI->rx_nbits,
            .word_delay_usecs = SPI->delay,
            .pad = 0, // padding, remain at 0
        };

    // Perform IOCTL
    int res = 0;
    res = ioctl(SPI->SPI_file, SPI_IOC_MESSAGE(1), &message);
    if (res < 0)
    {
        fprintf(stderr, "[ SPI ][ Read ] : Could not perform transfer operation on bus %d : %s\n", SPI->SPI_Bus, strerror(errno));
        free(RX);
        free(TX);
        return -3;
    }

    // Let's copy all of the output data.
    for (int i = 0; i < Len; i++)
        OutputBufer[i] = (int)RX[i];

    // Free de allocated buffers.
    free(RX);
    free(TX);

    return 0;
}