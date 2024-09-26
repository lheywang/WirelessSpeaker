/**
 * @file I2C_Engine.cpp
 * @author l.heywang
 * @brief Define basic I2C functions to perform write nor reads to IC.
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

// ==============================================================================
// INCLUDES
// ==============================================================================
#include "I2C_Engine.hpp"
#include "I2C.hpp"

#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <cstdint>

// ==============================================================================
// FUNCTIONS
// ==============================================================================

// ------------------------------------------------------------------------------
I2C_Bus *I2C_GetInfos()
{
    // Create struct
    I2C_Bus *I2C = new I2C_Bus;

    I2C->I2C_bus = I2C_BUS_NUMBER;

    // Generate the file
    snprintf(I2C->I2C_filename, sizeof(I2C->I2C_filename), "/dev/i2c/%ld", I2C->I2C_bus);
    I2C->I2C_filename[sizeof(I2C->I2C_filename) - 1] = '\0';

    // Open the file
    I2C->I2C_file = open(I2C->I2C_filename, O_RDWR);

    if (I2C->I2C_file < 0)
    {
        fprintf(stderr, "Could not open the requested I2C bus.");
        I2C->I2C_file = (int)NULL;
    }

    return I2C;
}

// ------------------------------------------------------------------------------
int I2C_Close(I2C_Bus *I2C)
{
    close(I2C->I2C_file);
    delete I2C;
    return 0;
}

// ------------------------------------------------------------------------------
int I2C_Write(I2C_Bus *I2C, int Address, int Register, int *Payload)
{
    // Configure the I2C Slave address
    I2C_ConfigureAddress(I2C, Address);

    if (sizeof(Payload[0]) == 1)
    {
        int res = i2c_smbus_write_block_data(I2C->I2C_file, Register, sizeof(Payload), (uint8_t *)Payload);
    }
    else if (sizeof(Payload[0]) == 2)
    {
        for (int i = 0; i < (sizeof(Payload) / sizeof(Payload[0])) + 1; i++)
        {
            int res = i2c_smbus_write_word_data(I2C->I2C_file, Register, Payload[i]);
        }
    }
    else
        return -4;
}

// ------------------------------------------------------------------------------
int I2C_Read(I2C_Bus *I2C, int Address, int Register, int *Payload, int Size, int DataSize)
{
    // Configure the I2C Slave address
    I2C_ConfigureAddress(I2C, Address);

    // Iterate over the wanted number of data
    for (int i = 0; i < (sizeof(Payload) / sizeof(Payload[0])) + 1; i++)
    {
        // Match the wanted datasize.
        if (DataSize == 8)
        {
            i2c_smbus_write_byte(I2C->I2C_file, Register);
            int res = i2c_smbus_read_byte(I2C->I2C_file);
        }
        else if (DataSize == 16)
        {
            int res = i2c_smbus_read_word_data(I2C->I2C_file, Register);
        }
        else
            return -4;

        // Increment to point to the next address
        Register++;
    }
    return 0;
}

// ------------------------------------------------------------------------------
int I2C_ConfigureAddress(I2C_Bus *I2C, int Address)
{
    if (ioctl(I2C->I2C_file, I2C_SLAVE, Address) < 0)
    {
        fprintf(stderr, "Could not set address");
        return -errno;
    }

    return 0;
}