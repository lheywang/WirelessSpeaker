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
/**
 * @struct SPI_Bus
 * @brief Store SPI Bus configuration.
 *
 * @param SPI_Bus::SPI_file Store the file descriptor.
 * @param SPI_Bus::SPI_Filename The name of the openned file
 * @param SPI_Bus::SPI_Bus The number of the SPI Bus
 * @param SPI_Bus::CS_Number The number of CS availables.
 *
 * @param SPI_Bus::speed The speed of the bus. Defined automatically.
 * @param SPI_Bus::delau The delay between CS and first clock
 * @param SPI_Bus::bits The number of bits per transfer
 * @param SPI_Bus::change The delay between the last clock and CS
 * @param SPI_Bus::tx_nbits The number of bits per transfer on the TX line
 * @param SPI_Bus::rx_nbits The number of bits per transfer on the RX line
 */
struct SPI_Bus
{
    int SPI_file;
    char SPI_Filename[30];
    int SPI_Bus;
    int CS_number;

    unsigned int speed;
    unsigned char delay;
    unsigned char bits;
    unsigned char change;
    unsigned char tx_nbits;
    unsigned char rx_nbits;
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
SPI_Bus *SPI_GetInfos(int CS, int Bus);

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
 * @param[in] WriteLen The lengh of data to be written.
 *
 * @return  0 : OK
 * @return -1 : Error while allocating Input buffer
 * @return -2 : Error while allocating Output buffer
 * @return -3 : IOCTL error.
 */
int SPI_Transfer(SPI_Bus *SPI, int *const InputBuffer, int *const OutputBufer, const int Len);