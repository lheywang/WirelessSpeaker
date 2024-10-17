/**
 * @file SPI_Engine.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define class, struct and functions for the SPI HAL.
 * @version 0.1
 * @date 2024-10-08
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <cstdint>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <cstdint>
#include <string.h>
#include <iostream>
#include "linux/spi/spidev.h"

// ==============================================================================
// DATA STRUCTURES
// ==============================================================================
/*! Define a struct that is used internally for the SPI driver */
struct SPI_Bus
{
    int SPI_file;          /*!< SPI file descriptor*/
    char SPI_Filename[30]; /*!< SPI file name*/
    int SPI_Bus;           /*!< SPI bus number (always 0)*/
    int CS_number;         /*!< SPI CS number (always 0)*/

    unsigned int speed;     /*!< Defined automatically. Store the SPI Bus speed.*/
    unsigned char delay;    /*!< Defined automatically. Store the SPI Bus delay between CS and first cycle.*/
    unsigned char bits;     /*!< Defined automatically. Store the SPI Bus number of bits per cycle.*/
    unsigned char change;   /*!< Defined automatically. Store the SPI Bus change speed after last cycle.*/
    unsigned char tx_nbits; /*!< Defined automatically. Store the SPI Bus tx bits per cycles.*/
    unsigned char rx_nbits; /*!< Defined automatically. Store the SPI Bus rx bits per cycle.*/
};

constexpr int SPI_DEFAULT_WORDSIZE = 8;       /*!< Default value for SPI wordsize*/
constexpr int SPI_DEFAULT_SPEED = 20'000'000; /*!< Default value for SPI speed*/

// ==============================================================================
// PROTOTYPES
// ==============================================================================

/**
 * @brief Open the SPI Bus and return a structure linked to it.
 *
 * @param[in] CS The selected CS for this struct.
 * @param[in] Bus The bus number used
 *
 * @return A SPI struct
 */
SPI_Bus *SPI_GetInfos();

/**
 * @brief Close and delete an SPI Object
 *
 * @param[in] bus The SPI_Bus struct to be closed.
 *
 * @return  0 : OK
 */
int SPI_Close(SPI_Bus *bus);

/**
 * @brief Configure the parameters of an SPI Bus
 *
 * @param[inout] SPI A SPI_Bus struct to be configured
 * @param[in] Mode The SPI mode for this slave
 * @param[in] WordSize The number of bits per word for this slave
 * @param[in] Speed The speed of the bus for this slave
 *
 * @return  0 : OK
 * @return -1 : Could not set IOCTL for Mode
 * @return -2 : Could not set IOCTL for WordSize
 * @return -3 : Could not set IOCTL for Speed
 */
int SPI_Configure(SPI_Bus *SPI, int Mode, int WordSize, int Speed);

/**
 * @brief Read N bytes from the bus. The order of bytes to transfer is leaved at the appreciation of an higher level code.
 *
 * @param[inout] SPI A SPI_Bus struct that serve as base
 * @param[in] InputBuffer The payload to be written.
 * @param[out] OutputBufer The payload to be read.
 * @param[in] Len The lengh of data to be written.
 *
 * @return  0 : OK
 * @return -1 : Error while allocating Input buffer
 * @return -2 : Error while allocating Output buffer
 * @return -3 : IOCTL error.
 */
template <typename I, typename O>
int SPI_Transfer(SPI_Bus *SPI, I *const InputBuffer, O *const OutputBufer, const int Len)
{
    // Allocate a unsigned long long buffer to store the data to be written.
    __u8 *TX = (__u8 *)malloc(sizeof(__u8) * Len);
    if (TX == 0)
    {
        std::cerr << "[ SPI ][ Transfer ] : Could not allocate the input buffer : "
                  << strerror(errno)
                  << std::endl;
        return -1;
    }

    // Let's copy all of the input data to the new one !
    for (int i = 0; i < Len; i++)
        TX[i] = (__u8)InputBuffer[i];

    // Allocate a unsigned long long buffer to the data to be rode.
    __u8 *RX = (__u8 *)malloc(sizeof(__u8) * Len);
    if (RX == 0)
    {
        std::cerr << "[ SPI ][ Transfer ] : Could not allocate the output buffer : "
                  << strerror(errno)
                  << std::endl;
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
        std::cerr << "[ SPI ][ Transfer ] : Could not perform transfer operation on bus "
                  << SPI->SPI_Bus
                  << " : "
                  << strerror(errno)
                  << std::endl;
        free(RX);
        free(TX);
        return -3;
    }

    // Let's copy all of the output data.
    for (int i = 0; i < Len; i++)
    {
        OutputBufer[i] = (O)RX[i];
    }

    // Free de allocated buffers.
    free(RX);
    free(TX);

    return 0;
}