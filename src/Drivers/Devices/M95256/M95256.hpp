/**
 * @file M95256.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Header file for our eeprom
 * @version 0.1
 * @date 2024-10-09
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once

// type include
#include "../../SPI/SPI.hpp"

// ==============================================================================
// PUBLIC DEFINES
// ==============================================================================
#define MAX_ADDRESS 0x7FFF

#define SOFT_WP_DISABLED ((0 << 1) | 0)
#define SOFT_WP_UPPER_QUARTER ((0 << 1) | 1)
#define SOFT_WP_UPPER_HALF ((1 << 1) | 0)
#define SOFT_WP_FULL ((1 << 1) | 1)

// ==============================================================================
// IC CLASS FUNCTIONS
// ==============================================================================

class M95256
{
private:
    SPI_Bus SPI;

public:
    /**
     * @brief Constructor for the M95256 class.
     *
     * @param SPI An SPI object to be used as base
     */
    M95256(const SPI_Bus *SPI);

    /**
     * @brief Destructor for the M95256 class.
     *
     */
    ~M95256();

    /**
     * @brief Enable the ability to write on the chip. Warning : The physical pin can overhide this value.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int WriteEnable();

    /**
     * @brief Disable the write ability. This is also done after each write.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int WriteDisable();

    /**
     * @brief Read back the status register.
     *
     * @param WriteProtectStatus Return the status of the write protection, in term of software and hardware.
     * @param ProtectedBlock Return the protected block.
     * @param WriteEnable Return the status of the write enable bit.
     * @param WriteInProgress Return the status of the write engine.
     *
     * @return  0 : OK
     * @return -1 : IOCT error.
     */
    int ReadStatus(int *const WriteProtectStatus,
                   int *const ProtectedBlock,
                   int *const WriteEnable,
                   int *const WriteInProgress);

    /**
     * @brief Write the status register
     *
     * @param WriteProtectStatus Write the protection mode register
     * @param ProtectedBlock Write the protected block values
     *
     * @return 0 : OK
     * @return -1 : Invalid Protected block value
     * @return -2 : IOCTL error.
     */
    int WriteStatus(const int WriteProtectStatus,
                    const int ProtectedBlock);

    /**
     * @brief Read data of the EEPROM
     *
     * @param Adresss Address of the first byte to be read.
     * @param Data A pointer to a list of Len elements to store the output.
     * @param Len The number of bytes to read.
     *
     * @return  0 : OK
     * @return -1 : Invalid address
     * @return -2 : Invalid Len (May be triggered if Address + Len > MAX_ADDRESS)
     * @return -3 : IOCTL error.
     */
    int Read(const int Address, int *const Data, const int Len);

    /**
     * @brief Write content to EEPROM. Only possible if write has been enabled !
     *
     * @param Address Adress of the first byte to be wrote
     * @param Data A pointer to a list of elements to be wrote.
     * @param Len The number of bytes to write.
     *
     * @return  0 : OK
     * @return -1 : Invalid address
     * @return -2 : Invalid Len (May be triggered if Address + Len > MAX_ADDRESS)
     * @return -3 : IOCTL error.
     */
    int Write(const int Address, int *const Data, const int Len);
};
