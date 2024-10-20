/**
 * @file header.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define the struct for the header
 * @version 0.1
 * @date 2024-10-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#pragma once
#include <cstdint>

/*!< Stores the infos about where and how to find a DSP Profile*/
struct DSP_PROFILE_INFO
{
    uint16_t Address; /*!< Address of the DSP Profile*/
    uint16_t Len;     /*!< Length in bytes of the DSP Profile*/
    uint32_t CRC;     /*!< CRC-32 of this profile to ensure integrity*/
};

/*! This struct represent the memory layout for the Header, as defined in the PDF file. */
struct EEPROM_HEADER_V1
{
    uint8_t __padding0 = 0x00; /*!< MEMORY PADDING. DO NOT TOUCH*/

    /*! This first struct expose DATA Revisions to parse the correct data, even if an update has occured since. */
    struct DATA_VERSION
    {
        uint8_t Major;  /*!< Major decimal of the data revision : 1.x.x*/
        uint8_t Median; /*!< Median decimal of the data revision : x.0.x*/
        uint8_t Minor;  /*!< Minor decimal of the data revision : x.x.0*/
    } DATA_VERSION;     /*!< Store an indicator of the header version*/

    /*! This second struct store the value of the last write to the EEPROM. */
    struct TIMESTAMP
    {
        uint8_t Year[2]; /*!< Year value, expressed as two 8b integer : 20-24*/
        uint8_t Month;   /*!< Month value, expressed from 0-12*/
        uint8_t Day;     /*!< Day value, expressed from 0-31*/
        uint8_t Hour;    /*!< Hour value, expressed from 0-60*/
        uint8_t Minutes; /*!< Minutes values, expressed from 0-60*/
        uint8_t Seconds; /*!< Seconds values, expressed from 0-60*/
    } LAST_WRITE;        /*!< Store an indicator of the timestam of the last header write*/

    /*! This third struct define the hardware version of the PCB. */
    struct HARDWARE_VERSION
    {
        uint8_t Major;  /*!< Major hardware revision*/
        uint8_t Minor;  /*!< Minor hardware revision*/
    } HARDWARE_VERSION; /*!< Store an indicator about the hardware version of the speaker*/

    /*! This fourth struct define the BOM version of the speaker. */
    struct BOM_VERSION
    {
        uint8_t Major; /*!< Major component revision*/
        uint8_t Minor; /*!< Minor component revision*/
    } BOM_VERSION;     /*!< Store an indicator about the component version of the speaker*/

    /*! This fifth struct store a serial number. */
    struct SERIAL_NB
    {
        uint8_t Letters[2];  /*!< Two letters for the Serial number*/
        uint8_t Decimals[6]; /*!< Six natural decimals for the Serial number*/
    } SERIAL_NB;             /*!< Store the serial number of the speaker*/

    // May be for further usage...
    uint8_t __padding1[8] = {0x00}; /*!< MEMORY PADDING. DO NOT TOUCH*/

    /*! This sixth struct store a fabrication date, in the same format as the eeprom write date. */
    struct PRODUCTION_DATE
    {
        uint8_t Year[2]; /*!< Year value, expressed as two 8b integer : 20-24*/
        uint8_t Month;   /*!< Month value, expressed from 0-12*/
        uint8_t Day;     /*!< Day value, expressed from 0-31*/
        uint8_t Hour;    /*!< Hour value, expressed from 0-60*/
        uint8_t Minutes; /*!< Minutes values, expressed from 0-60*/
        uint8_t Seconds; /*!< Seconds values, expressed from 0-60*/
    } PRODUCTION_DATE;   /*!< Store the timestam of the design date of this speaker, or more accuratly it's production date*/

    uint16_t HeaderCRC16 = 0x0000; /*!< CRC16 value for the header*/
    uint16_t ConfigCRC16 = 0x0000; /*!< CRC16 value for the config*/

    uint8_t __padding3[8] = {0x00}; /*!< MEMORY PADDING. DO NOT TOUCH*/

    uint8_t DSP_PROFILE_NUMBER; /*!< Used DSP Profiles. Each bit correspond to a DSP Profile*/

    uint8_t __padding4[12] = {0x00}; /*!< MEMORY PADDING. DO NOT TOUCH*/

    // END OF PAGE 0

    struct DSP_PROFILE_INFO Profile[8]; /*!< DSP Profile 0-15*/

    // END OF PAGE 1
};

/*! Define defaults values for the base header */
constexpr struct EEPROM_HEADER_V1 DEFAULT_HEADER_V1
{
    .DATA_VERSION{
        .Major = 1,
        .Median = 0,
        .Minor = 0,
    },
        .LAST_WRITE{
            .Year = {19, 70},
            .Month = 01,
            .Day = 01,
            .Hour = 00,
            .Minutes = 00,
            .Seconds = 01,
        },
        .HARDWARE_VERSION{
            .Major = 1,
            .Minor = 0,
        },
        .BOM_VERSION{
            .Major = 1,
            .Minor = 0,
        },
        .SERIAL_NB{
            .Letters = {'S', 'P'},
            .Decimals = {'0', '0', '0', '0', '0', '0'},
        },
        .PRODUCTION_DATE{
            .Year = {19, 70},
            .Month = 01,
            .Day = 01,
            .Hour = 00,
            .Minutes = 00,
            .Seconds = 01,
        },
        .DSP_PROFILE_NUMBER = 0x00,
        .Profile = {
            {
                .Address = 0x01C0,
                .Len = 0x0000,
                .CRC = 0x00000000,
            },
            {
                .Address = 0x0000,
                .Len = 0x0000,
                .CRC = 0x00000000,
            },
            {
                .Address = 0x0000,
                .Len = 0x0000,
                .CRC = 0x00000000,
            },
            {
                .Address = 0x0000,
                .Len = 0x0000,
                .CRC = 0x00000000,
            },
            {
                .Address = 0x0000,
                .Len = 0x0000,
                .CRC = 0x00000000,
            },
            {
                .Address = 0x0000,
                .Len = 0x0000,
                .CRC = 0x00000000,
            },
            {
                .Address = 0x0000,
                .Len = 0x0000,
                .CRC = 0x00000000,
            },
            {
                .Address = 0x0000,
                .Len = 0x0000,
                .CRC = 0x00000000,
            },
    },
};
