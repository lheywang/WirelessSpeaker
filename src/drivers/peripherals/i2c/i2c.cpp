/**
 * @file I2C_Engine.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define basic I2C functions to perform write nor reads to IC.
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 * @remark Class was tested successfully on 01/10/2024.
 *
 */

// ==============================================================================
// INCLUDES
// ==============================================================================
// Header
#include "drivers/peripherals/i2c.hpp"

// STD
#include <cstdint>
#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <linux/i2c-dev.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

// ==============================================================================
// FUNCTIONS
// ==============================================================================

// Custom builded smbus.h file, from the original repo : https://github.com/Sensirion/i2c-tools/tree/master
// Only includes path were modified.
// File extension was changed to C++ to make the compilation easier.
#include "drivers/peripherals/core/smbus.h"

// ==============================================================================
// PRIVATE FUNCTIONS
// ==============================================================================
int I2C_ConfigureAddress(I2C_Bus* I2C, int Address);
int I2C_CheckRegister(int Register);
int I2C_CheckAddress(int Address);

// ==============================================================================
// FUNCTIONS
// ==============================================================================

// ------------------------------------------------------------------------------
I2C_Bus* I2C_GetInfos()
{
    // Create struct
    I2C_Bus* I2C = new I2C_Bus;

    I2C->I2C_bus = I2C_BUS_NUMBER;

    // Generate the file
    snprintf(I2C->I2C_filename, sizeof(I2C->I2C_filename), "/dev/i2c-%ld", I2C->I2C_bus);
    I2C->I2C_filename[sizeof(I2C->I2C_filename) - 1] = '\0';

    // Open the file
    I2C->I2C_file = open(I2C->I2C_filename, O_RDWR);

    if(I2C->I2C_file < 0)
    {
        std::cerr << "[ I2C ][ GetInfos ] : Could not open the requested I2C bus : "
                  << strerror(errno) << std::endl;
        I2C->I2C_file = (int)NULL;
    }

    return I2C;
}

// ------------------------------------------------------------------------------
int I2C_Close(I2C_Bus* I2C)
{
    close(I2C->I2C_file);
    delete I2C;
    return 0;
}

// ------------------------------------------------------------------------------
int I2C_Write(I2C_Bus* I2C, int Address, int Register, int* Payload, int Size, int DataSize)
{
    // basics checks
    if(I2C_CheckAddress(Address) != 0)
        return -1;
    if(I2C_CheckRegister(Register) != 0)
        return -2;

    int res = 0;

    // address conf to the driver
    I2C_ConfigureAddress(I2C, (uint8_t)Address);

    for(int i = 0; i < Size; i++)
    {
        if(DataSize == 1)
            res = i2c_smbus_write_byte_data(I2C->I2C_file, Register + i, (uint8_t)Payload[i]);
        else
            res = i2c_smbus_write_word_data(I2C->I2C_file, Register + i, (uint16_t)Payload[i]);
    }

    if(res != 0)
        return -4;
    return 0;
}

// ------------------------------------------------------------------------------
int I2C_Read(I2C_Bus* I2C, int Address, int Register, int* Payload, int Size, int DataSize)
{
    // basics checks
    if(I2C_CheckAddress(Address) != 0)
        return -1;
    if(I2C_CheckRegister(Register) != 0)
        return -2;
    if(Size > 0xFF)
        return -3;

    int res = 0;

    // address conf to the driver// Configure the I2C Slave address
    I2C_ConfigureAddress(I2C, Address);

    // If data == 0 (We send only a command !)
    for(int i = 0; i < Size; i++)
    {
        if(DataSize == 1)
            res = i2c_smbus_read_byte_data(I2C->I2C_file, Register + i);
        else if(DataSize == 2)
            res = i2c_smbus_read_word_data(I2C->I2C_file, Register + i);
        Payload[i] = res;
    }
    return 0;
}

// ------------------------------------------------------------------------------
int I2C_ConfigureAddress(I2C_Bus* I2C, int Address)
{
    if(ioctl(I2C->I2C_file, I2C_SLAVE, Address) < 0)
    {
        std::cerr << "[ I2C ][ ConfigureAddress ] : Could not set address : " << strerror(errno)
                  << std::endl;
        return -errno;
    }
    return 0;
}
// ------------------------------------------------------------------------------
int I2C_CheckAddress(int Address)
{
    if(Address < 0x08 or Address > 0x77)
        return -1;
    return 0;
}

// ------------------------------------------------------------------------------
int I2C_CheckRegister(int Register)
{
    if(Register > 0xFF)
        return -1;
    return 0;
}