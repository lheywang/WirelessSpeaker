/**
 * @file I2C_Engine.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define basic functions to write or read to IC over I2C bus.
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 * @remark Class was tested successfully on 01/10/2024.
 *
 */

#pragma once

// ==============================================================================
// MACROS
// ==============================================================================
/**
 * @brief Swap the 8 first bits and the 8 next bits (on 16bit value). Required due to an inversion inside of the hardware.
 *
 * @param x The value to invert
 * @return The inverted value.
 */
constexpr int SWAP_BYTES(int x)
{
    return (((x & 0x00FF) << 8) | (x & 0xFF00) >> 8);
}

// ==============================================================================
// DATA STRUCTURES
// ==============================================================================

/*! Define the struct used internally by the I2C driver */
struct I2C_Bus
{
    int I2C_file; /*!< I2C file descriptor*/
    char I2C_filename[30]; /*!< I2C file name*/
    long I2C_bus; /*!< I2C bus number*/
};

// ==============================================================================
// PROTOTYPES
// ==============================================================================

/**
 * @brief Return a struct that handle the I2C infos for you.
 *        It also open the handle to the file, thus be sure to handle the closing correctly !
 *
 * @return *I2C_Bus : WARNING : The file will be initialized to NULL if unable to open the file !
 */
I2C_Bus* I2C_GetInfos();

/**
 * @brief Close the I2C Bus. Any operation tempted by after will be failed.
 *
 * @param[inout] I2C A pointer on a struct that define bus informations.
 *
 * @return 0 : File closed
 *
 */
int I2C_Close(I2C_Bus* I2C);

/**
 * @brief This function perform a write of one or more bytes (depending on the lengh of the payload) to the I2C bus.
 *        For each write, the Register value is going to be incremented.
 *
 * @param[inout] I2C A pointer on a struct that define the settings for the currently used I2C bus.
 * @param[in] Address The address of the IC on the bus.
 * @param[in] Register The register where the data shall be wrote.
 * @param[in] Payload The data to be wrote.
 * @param[in] Size The number of bytes (or words) to write. Default to 1 byte.
 * @param[in] DataSize The number of bytes per operation to write (1 or 2).
 *
 * @return  0 : Everything went fine.
 * @return -1 : Incorrect Address.
 * @return -2 : Incorrect Register.
 * @return -3 : Incorrect Payload size.
 * @return -4 : Incorrect DataSize value.
 * @return -5 : IOCTL error.
 */
int I2C_Write(
    I2C_Bus* I2C, int Address, int Register, int* Payload, int Size = 1, int DataSize = 1);

/**
 * @brief This function perform the read of N (Size) bytes on the IC.
 * @param[inout] I2C A pointer on a struct that define the settings for the currently used I2C bus.
 * @param[in] Address The address of the IC on the bus.
 * @param[in] Register The register where the data shall be rode.
 * @param[in] Payload The data to be rode. Pass an array of int of the wanted size.
 * @param[in] Size The number of bytes (or words) to be rode.
 * @param[in] DataSize The number of bytes per operation to write (1 or 2).
 *
 * @return  0 : Everything went fine.
 * @return -1 : Incorrect Address.
 * @return -2 : Incorrect Register.
 * @return -3 : Number of bytes to read too big.
 * @return -4 : Incorrect DataSize value.
 * @return -5 : IOCTL error.
 */
int I2C_Read(I2C_Bus* I2C, int Address, int Register, int* Payload, int Size = 1, int DataSize = 1);
