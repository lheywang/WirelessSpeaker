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

// ==============================================================================
// DATA STRUCTURES
// ==============================================================================
/**
 * @struct SPI_Bus
 * @brief Store SPI Bus configuration.
 *
 * @var SPI_Bus::SPI_file Store the file descriptor.
 * @var SPI_Bus::SPI_Filename : The name of the openned file
 * @var SPI_Bus::SPI_Bus : The number of the SPI Bus
 * @var SPI_Bus::CS_Number : The number of CS availables.
 */
struct SPI_Bus
{
    int SPI_file;
    char SPI_Filename[30];
    int SPI_Bus;
    int CS_number;
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
int SPI_CloseDevice(SPI_Bus *bus);

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
int SPI_ConfigureBUS(SPI_Bus *SPI, int Mode, int WordSize, int Speed);

/**
 * @brief Read N bytes from the bus.
 *
 * @param[inout] SPI A SPI_Bus struct that serve as base
 * @param[in] address The address of the data to be wrote. This will be appended at the beginning of the InputBuffer.
 * @param[in] InputBuffer The payload to be written.
 * @param[out] OutputBufer The payload to be read.
 * @param[in] WriteLen The lengh of data to be written.
 * @param[in] ReadLen The lengh of data to be rode.
 *
 * @return  0 : OK
 */
int SPI_Transfer(SPI_Bus *SPI, const int address, int *const InputBuffer, int *const OutputBufer, const int WriteLen, const int ReadLen);