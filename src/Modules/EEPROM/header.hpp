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

#include <cstdint>

/*! This struct represent the memory layout for the Header, as defined in the PDF file. */
struct EEPROM_HEADER_V1
{
    uint8_t __padding0; /*!< First byte of padding. Prevent write to address 0x0000*/

    /*! This first struct expose DATA Revisions to parse the correct data, even if an update has occured since. */
    struct DATA_VERSION
    {
        uint8_t Major;  /*!< Major decimal of the data revision : 1.x.x*/
        uint8_t Median; /*!< Median decimal of the data revision : x.0.x*/
        uint8_t Minor;  /*!< Minor decimal of the data revision : x.x.0*/
    };

    /*! This second struct store the value of the last write to the EEPROM. */
    struct TIMESTAMP
    {
        uint8_t Year[2]; /*!< Year value, expressed as a natural integer 0-65535*/
        uint8_t Month;   /*!< Month value, expressed from 0-12*/
        uint8_t Day;     /*!< Day value, expressed from 0-31*/
        uint8_t Hour;    /*!< Hour value, expressed from 0-60*/
        uint8_t Minutes; /*!< Minutes values, expressed from 0-60*/
        uint8_t Seconds; /*!< Seconds values, expressed from 0-60*/
    };

    /*! This third struct define the hardware version of the PCB. */
    struct HARDWARE_VERSION
    {
        uint8_t Major; /*!< Major hardware revision*/
        uint8_t Minor; /*!< Minor hardware revision*/
    };

    /*! This fourth struct define the BOM version of the speaker. */
    struct BOM_VERSION
    {
        uint8_t Major; /*!< Major component revision*/
        uint8_t Minor; /*!< Minor component revision*/
    };

    /*! This fifth struct store a serial number. */
    struct SERIAL_NB
    {
        uint8_t Letters[2];  /*!< Two letters for the Serial number*/
        uint8_t Decimals[6]; /*!< Six natural decimals for the Serial number*/
    };

    uint8_t __padding1; /*!< Padding value. Reserved for future usage (SN Extension ?)*/

    /*! This sixth struct store a fabrication date, in the same format as the eeprom write date. */
    struct DESIGN_DATE
    {
        uint8_t Year[2]; /*!< Year value, expressed as a natural integer 0-65535*/
        uint8_t Month;   /*!< Month value, expressed from 0-12*/
        uint8_t Day;     /*!< Day value, expressed from 0-31*/
        uint8_t Hour;    /*!< Hour value, expressed from 0-60*/
        uint8_t Minutes; /*!< Minutes values, expressed from 0-60*/
        uint8_t Seconds; /*!< Seconds values, expressed from 0-60*/
    };

    uint8_t HeaderCRC8[2]; /*!< CRC8 value (9 bits)*/
    uint8_t __padding3;    /*!< Padding value. Reserved for future usage.*/

    uint8_t DATA_CRC_ADD[2]; /*!< Address of the CRC block for the data*/
    uint8_t DATA_CRC_LEN[2]; /*!< Length of the CRC block for the data*/

    uint8_t __padding2[7]; /*!< Padding values. Reserved for future usage.*/

    uint8_t DATA_ADD[2]; /*!< Address of the DATA Block*/
    uint8_t DATA_LEN[2]; /*!< Length of the DATA Block*/
};
