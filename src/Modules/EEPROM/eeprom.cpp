/**
 * @file eeprom.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define source for the EEPROM functions
 * @version 0.1
 * @date 2024-10-17
 *
 * @copyright Copyright (c) 2024
 *
 */

// ==============================================================================
// INCLUDES
// ==============================================================================
#include "eeprom.hpp"
#include "../libcrc/checksum.h"
#include "../../Drivers/Devices/M95256/M95256.hpp"

#include <iostream>
#include <stdexcept>
#include <math.h>

// ==============================================================================
// CONSTANTS
// ==============================================================================
constexpr int PROFILE_7 = 0x80;
constexpr int PROFILE_6 = 0x40;
constexpr int PROFILE_5 = 0x20;
constexpr int PROFILE_4 = 0x10;
constexpr int PROFILE_3 = 0x08;
constexpr int PROFILE_2 = 0x04;
constexpr int PROFILE_1 = 0x02;
constexpr int PROFILE_0 = 0x01;

constexpr int PROFILES[] = {
    PROFILE_0,
    PROFILE_1,
    PROFILE_2,
    PROFILE_3,
    PROFILE_4,
    PROFILE_5,
    PROFILE_6,
    PROFILE_7,
};

constexpr int LARGE_PROFILE = 5662;
constexpr int MEDIUM_PROFILE = 2846;
constexpr int SMALL_PROFILE = 1438;

// ==============================================================================
// CONSTRUCTORS
// ==============================================================================

EEPROM::EEPROM(bool ForceWrite)
{
    // Open a new SPI device
    this->SPI = SPI_GetInfos();
    if (this->SPI == nullptr)
        throw std::runtime_error("[ M95256 ][ CONSTRUCTOR ] : Failed to allocate memory for the SPI obect");

    // Open a new slave
    this->Slave = M95256(this->SPI);

    this->Header = new EEPROM_HEADER_V1;
    if (this->Header == nullptr)
        throw std::runtime_error("[ EEPROM ][ CONSTRUCTOR ] : Failed to allocate memory for the HEADER obect");

    int ret = this->ReadHeaderV1();
    if (ret != 0)
    {
        if (ForceWrite == true)
        {
            memcpy(this->Header, &DEFAULT_HEADER_V1, HEADER_SIZE);
            this->WriteHeaderV1();
            std::clog << "[ EEPROM ][ CONSTRUCTOR ] : Failed to read the header. Default one was wrote. Error code was : " << ret << std::endl;
        }
        else
            throw std::runtime_error("[ EEPROM ][ CONSTRUCTOR ] : Failed to read header from the EEPROM");
    }

    return;
}

// ==============================================================================
// DESTRUCTORS
// ==============================================================================

EEPROM::~EEPROM()
{
    delete this->Header;
    this->Slave.~M95256(); // Call the destructor.
    SPI_Close(this->SPI);
    return;
}

// ==============================================================================
// PRIVATE UTILITIES FUNCTIONS
// ==============================================================================

int CheckProfileValue(int Profile)
{
    if ((1 > Profile) | (Profile > 8))
        return -1;
    return 0;
}

// ==============================================================================
// PRIVATE
// ==============================================================================

int EEPROM::ReadHeaderV1() // OK
{
    // Alocate the data
    uint8_t *buf = (uint8_t *)malloc(HEADER_SIZE);
    if (buf == nullptr)
        return -1;

    // Copy the data
    memset(buf, 0x00, HEADER_SIZE);

    // Read the data and put it on the structure
    int res = this->Slave.Read(HEADER_ADDRESS, buf, HEADER_SIZE);
    if (res < 0)
        return -2;
    memcpy(this->Header, buf, HEADER_SIZE);

    // CRC Check
    uint16_t read_CRC = Header->HeaderCRC16;
    this->Header->HeaderCRC16 = 0xAAAA; // Set the dummy value to ensure integrity of the computation.

    memcpy(buf, this->Header, HEADER_SIZE);
    uint16_t calc_CRC = crc_16(buf, HEADER_SIZE);

    // Free memory
    free(buf);

    if (read_CRC != calc_CRC)
        return -3;
    return 0;
}

int EEPROM::WriteHeaderV1() // OK
{
    // Creating a buffer value
    uint8_t *buf = (uint8_t *)malloc(HEADER_SIZE);
    if (buf == nullptr)
        return -1;
    memset(buf, 0x00, HEADER_SIZE);

    // Set a dummy value on the CRC16 field and copy the data to an array of uint8_t.
    this->Header->HeaderCRC16 = 0xAAAA;
    memcpy(buf, Header, HEADER_SIZE);

    // Compute the CRC
    uint16_t calc_CRC = crc_16(buf, HEADER_SIZE);
    this->Header->HeaderCRC16 = calc_CRC;

    // Copying the data
    memcpy(buf, this->Header, HEADER_SIZE);

    // Write the data (one write per 64 bytes, per page !)
    int ret = 0;
    ret += this->Slave.Write(HEADER_ADDRESS, &buf[0], PAGE_SIZE);
    ret += this->Slave.Write((HEADER_ADDRESS + PAGE_SIZE), &buf[PAGE_SIZE], PAGE_SIZE);
    free(buf);

    // Returns
    if (ret < 0)
        return -2;
    return 0;
}
int EEPROM::SetConfigCRC(const uint16_t CRC) // OK
{
    this->Header->ConfigCRC16 = CRC;
    return 0;
}
int EEPROM::GetConfigCRC(uint16_t *const CRC) // OK
{
    *CRC = this->Header->ConfigCRC16;
    return 0;
}

// ==============================================================================
// GLOBAL MANAGEMENT
// ==============================================================================

int EEPROM::GetHeaderV1(EEPROM_HEADER_V1 *const Header) // OK
{
    memcpy(Header, this->Header, HEADER_SIZE); // The header was cached, thus we don't bother reading it over SPI.
    return 0;
}

int EEPROM::WriteConfigV1(CONFIG_V1 *const Data) // OK
{
    // Creating a buffer value and cop
    uint8_t *buf = (uint8_t *)malloc(CONFIG_SIZE);
    if (buf == nullptr)
        return -1;
    memcpy(buf, Data, CONFIG_SIZE);

    // Compute the CRC and write it on the header / EEPROM
    uint16_t calc_CRC = crc_16(buf, CONFIG_SIZE);
    this->SetConfigCRC(calc_CRC);
    this->WriteHeaderV1();

    // Write the data (one write per 64 bytes, per page !) and free the buffer.
    int ret = 0;
    for (int i = 0; i < CONFIG_SIZE; i += PAGE_SIZE)
        ret += this->Slave.Write((CONFIG_ADDRESS + i), &buf[i], PAGE_SIZE);
    free(buf);

    // Returns
    if (ret < 0)
        return -2;
    return 0;
}

int EEPROM::ReadConfigV1(CONFIG_V1 *const Data) // OK
{
    // Alocate the data
    uint8_t *buf = (uint8_t *)malloc(CONFIG_SIZE);
    if (buf == nullptr)
        return -1;
    // Copy the data
    memset(buf, 0x00, CONFIG_SIZE);

    // Read the data and put it on the structure
    int res = this->Slave.Read(CONFIG_ADDRESS, buf, CONFIG_SIZE);
    if (res < 0)
        return -2;
    memcpy(Data, buf, CONFIG_SIZE);

    // CRC Check
    uint16_t calc_CRC = crc_16(buf, CONFIG_SIZE);
    uint16_t read_CRC = 0;
    this->GetConfigCRC(&read_CRC);

    // Free memory
    free(buf);

    if (read_CRC != calc_CRC)
        return -3;
    return 0;
}

// ==============================================================================
// DSP PROFILE FUNCTIONS
// ==============================================================================

int EEPROM::CheckForDSPProfileSpace(DSP_PROFILE *const Profile, int *const PossibleProfileID)
{
    // Check if at least a profile is available.
    if (this->Header->DSP_PROFILE_NUMBER == 0xFF) // All profiles are used.
        return -1;

    // Variables for after.
    int ProfileSize = 0xFFFF;
    int ActualAddress = 0;
    int FutureAddress = 0;
    int PredictedAddress = 0;

    // Identify the size of the profile
    switch (Profile->Size)
    {
    case DSP_PROFILE::PROFILE_1024:
        ProfileSize = LARGE_PROFILE;
        break;
    case DSP_PROFILE::PROFILE_512:
        ProfileSize = MEDIUM_PROFILE;
        break;
    case DSP_PROFILE::PROFILE_256:
        ProfileSize = SMALL_PROFILE;
        break;
    }

    // Iterate over the profiles
    for (int i = 0; i < 8; i++)
    {
        // If possible, we compute the available size. In case of match, the first will be choosen.
        if ((this->Header->DSP_PROFILE_NUMBER & PROFILES[i]) == 0)
        {
            // Fetch some parameters
            ActualAddress = this->Header->Profile[i].Address;

            // Get the end address.
            if (i != 7)
            {
                FutureAddress = this->Header->Profile[i + 1].Address;
            }
            else
                FutureAddress = EEPROM_MAX_ADDRESS;

            // If 0x0000 (default value), then use the max value
            if (FutureAddress == 0x0000)
            {
                FutureAddress = EEPROM_MAX_ADDRESS;
            }

            // Compute the predicted address
            PredictedAddress = ActualAddress + ProfileSize;

            // If size can be stored here, use it.
            if (PredictedAddress < FutureAddress)
            {
                *PossibleProfileID = i;
                return 0;
            }
        }
    }
    return -1;
}

int EEPROM::AddDSPProfile(DSP_PROFILE *const Profile, int *const ProfileNumber)
{
    int ret = 0;

    // Allocate memory
    int Size = 0;
    switch (Profile->Size)
    {
    case DSP_PROFILE::PROFILE_1024:
        Size = LARGE_PROFILE;
        break;
    case DSP_PROFILE::PROFILE_512:
        Size = MEDIUM_PROFILE;
        break;
    case DSP_PROFILE::PROFILE_256:
        Size = SMALL_PROFILE;
        break;
    }

    // Get Profile parameters
    this->CheckForDSPProfileSpace(Profile, ProfileNumber);
    int Address = this->Header->Profile[*ProfileNumber].Address;

    // Get the number of pages
    int Pages = ceil(Size / 64);

    // Malloc
    uint8_t *buf = (uint8_t *)malloc(Pages * 64);
    if (buf == nullptr)
        return -2;

    // Prepare data
    memcpy(buf, Profile, Size);

    // Write data per 64 bytes pages
    for (int i = 0; i < Pages; i++)
    {
        ret += this->Slave.Write((Address + (i * PAGE_SIZE)), &buf[i * PAGE_SIZE], PAGE_SIZE);
    }

    free(buf);

    if (ret != 0)
        return -3;
    return 0;
}

int EEPROM::RemoveDSPProfile(const int ProfileNumber)
{
    if (CheckProfileValue(ProfileNumber) != 0)
        return -1;

    this->Header->DSP_PROFILE_NUMBER &= ~PROFILES[ProfileNumber - 1]; // Clear the corresponding bit.
    this->Header->Profile[ProfileNumber - 1].CRC = 0x0000;            // Reset the CRC to invalidate any read to it.

    // Update the header.
    int ret = this->WriteHeaderV1();

    if (ret != 0)
        return -2;
    return 0;
}

int EEPROM::GetDSPProfileName(const int ProfileNumber, char ProfileName[MAX_PROFILE_CHAR])
{
    if (CheckProfileValue(ProfileNumber) != 0)
        return -1;

    // First, get the address
    int Address = this->Header->Profile[ProfileNumber - 1].Address;

    // Then, read
    uint8_t *buf = (uint8_t *)malloc(MAX_PROFILE_CHAR);
    if (buf == nullptr)
        return -1;

    int ret = this->Slave.Read(Address, buf, MAX_PROFILE_CHAR);
    if (ret != 0)
    {
        free(buf);
        return -2;
    }

    // Copy the data
    memcpy(ProfileName, buf, MAX_PROFILE_CHAR);
    free(buf);
    return 0;
}

int EEPROM::GetDSPProfile(const int ProfileNumber, DSP_PROFILE *const Profile)
{
    if (CheckProfileValue(ProfileNumber) != 0)
        return -1;

    // Allocate memory
    int Size = 0;
    switch (Profile->Size)
    {
    case DSP_PROFILE::PROFILE_1024:
        Size = LARGE_PROFILE;
        break;
    case DSP_PROFILE::PROFILE_512:
        Size = MEDIUM_PROFILE;
        break;
    case DSP_PROFILE::PROFILE_256:
        Size = SMALL_PROFILE;
        break;
    }

    // Get Profile parameters
    int Address = this->Header->Profile[ProfileNumber - 1].Address;
    int Len = this->Header->Profile[ProfileNumber - 1].Len;

    // Malloc
    uint8_t *buf = (uint8_t *)malloc(Size);
    if (buf == nullptr)
        return -2;

    // Read data
    this->Slave.Read(Address, buf, Len);
    memcpy(Profile, buf, Len);
    free(buf);

    return 0;
}

int EEPROM::GetDSPProfileSize(const int ProfileNumber, DSP_PROFILE *const Profile)
{
    if (CheckProfileValue(ProfileNumber) != 0)
        return -1;

    int Size = this->Header->Profile[ProfileNumber - 1].Len;

    switch (Size)
    {
    case SMALL_PROFILE:
        *Profile = DSP_PROFILE{DSP_PROFILE::PROFILE_256};
        break;
    case MEDIUM_PROFILE:
        *Profile = DSP_PROFILE{DSP_PROFILE::PROFILE_512};
        break;
    case LARGE_PROFILE:
        *Profile = DSP_PROFILE{DSP_PROFILE::PROFILE_1024};
        break;
    }
    return 0;
}