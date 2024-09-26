/**
 * @file I2C_Engine.hpp
 * @author l.heywang
 * @brief Define basic functions to write or read to IC over I2C bus.
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once

// ==============================================================================
// DATA STRUCTURES
// ==============================================================================

/**
 * @brief
 *
 */
struct I2C_Bus
{
    int I2C_file;
    char I2C_filename[30];
    long I2C_bus;
};

// ==============================================================================
// PROTOTYPES
// ==============================================================================

/**
 * @brief Return a struct that handle the I2C infos for you.
 *        It also open the handle to the file, thus be sure to handle the closing correctly !
 *
 * @return *I2C_Bus
 */
I2C_Bus *I2C_GetInfos();

/**
 * @brief Close the I2C Bus. Any operation tempted by after will be failed.
 *
 * @param[inout] I2C A pointer on a struct that define bus informations.
 *
 * @return 0 : File closed
 * @return -1: Unable to close the file.
 */
int I2C_Close(I2C_Bus *I2C);

/**
 * @brief This function perform a write of one or more bytes (depending on the lengh of the payload) to the I2C bus. For each write, the Register value is going to be incremented.
 *
 * @param[inout] I2C A pointer on a struct that define the settings for the currently used I2C bus.
 * @param[in] Address The address of the IC on the bus.
 * @param[in] Register The register where the data shall be wrote.
 * @param[in] Payload The data to be wrote.
 *
 * @return 0 : Everything went fine.
 * @return -1 : Unable to find the Address.
 * @return -2 : Unable to find the Register.
 * @return -3 : Incorrect Payload.
 * @return -4 : Payload too long.
 */
int I2C_Write(I2C_Bus *I2C, int Address, int Register, int *Payload);

/**
 * @brief This function perform the read of N (Size) bytes on the IC. The Data size will also be automatically determined.
 *
 * @param[inout] I2C A pointer on a struct that define the settings for the currently used I2C bus.
 * @param[in] Address The address of the IC on the bus.
 * @param[in] Register The register where the data shall be wrote.
 * @param[in] Payload The data to be rode. Pass an array of int of the wanted size.
 * @param[in] DataSize The number of bites to be rode. By default 8.
 *
 * @return 0 : Everything went fine.
 * @return -1 : Unable to find the Address.
 * @return -2 : Unable to find the Register.
 * @return -3 : Number of bytes to read too big.
 * @return -4 : DataSize Incorrect. Only 8 or 16 are accepted.
 */
int I2C_Read(I2C_Bus *I2C, int Address, int Register, int *Payload, int DataSize = 8);

/**
 * @brief This function, called automatically before any operation configure the address on the IOCTL file.
 *
 * @param[inout] I2C A pointer on a struct that define the settings for the currently used I2C bus.
 * @param[in] Address The address of the IC on the bus.
 * @return 0 : Everything went fine
 * @return -1 : Cannot configure address
 */
int I2C_ConfigureAddress(I2C_Bus *I2C, int Address);
