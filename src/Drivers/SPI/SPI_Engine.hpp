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
int SPI_Transfer(SPI_Bus *SPI, int *const InputBuffer, int *const OutputBufer, const int Len);