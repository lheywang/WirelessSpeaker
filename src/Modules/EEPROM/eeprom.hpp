/**
 * @file eeprom.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Define the eeprom global header file.
 * @version 0.1
 * @date 2024-10-15
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "header/header.hpp"
#include "structs/StructV1.hpp"
#include "../../Drivers/Devices/M95256/M95256.hpp"

// HEADER CONSTANTS
constexpr int HEADER_SIZE = 128;       /*!< Define the size in bytes of the header.*/
constexpr int HEADER_ADDRESS = 0x0000; /*!< Define the base address of the header*/

// CONFIG CONSTANTS
constexpr int CONFIG_SIZE = 256;
constexpr int CONFIG_ADDRESS = 0x080;

class EEPROM
{
private:
    M95256 Slave;
    EEPROM_HEADER_V1 *Header;
    SPI_Bus *SPI;
    int ReadHeaderV1();
    int WriteHeaderV1();
    int SetConfigCRC(const uint16_t CRC);
    int GetConfigCRC(uint16_t *const CRC);

public:
    /**
     * @brief Construct a new EEPROM
     *
     * @param[in] ForceWrite Ignore the read issues and force the write of a new header. Will be logged.
     *
     */
    EEPROM(bool ForceWrite);

    /**
     * @brief Destruct an EEPROM class.
     *
     */
    ~EEPROM();

    /**
     * @brief Read the header from the EEPROM. CRC is checked.
     *
     * @param[out] Header A reference to an header struct to be filled.
     *
     * @return  0 : OK
     */
    int GetHeaderV1(EEPROM_HEADER_V1 *const Header);

    /**
     * @brief Write the config to the EEPROM. Date and CRC are also updated.
     *
     * @param[in] Data A reference to the Data structure to be wrote.
     * @param[in] Data The data to be wrotten
     *
     * @return  0 : OK.
     * @return -1 : Memory allocation failed.
     * @return -2 : Write failed.
     */
    int WriteConfigV1(CONFIG_V1 *const Data);

    /**
     * @brief Read the config from the EEPROM. CRC is computed. An Header read is highly recommended to get the date.
     *
     * @param[in] Data The data to be rode
     *
     * @return  0 : OK
     * @return -1 : Memory allocation failed.
     * @return -2 : Read failed.
     * @return -3 : Invalid CRC.
     */
    int ReadConfigV1(CONFIG_V1 *const Data);

    /**
     * @brief Convert an ConfigV1 struct to a ConfigV.. struct.
     *
     * @warning This function isn't implemented for now and won't be until a Rev2 has been defined.
     *
     * @param Src A reference to the input Config struct.
     * @param Dest A reference to the output Config struct.
     *
     * @return  0 : OK
     * @return -1 : Update failed.
     */
    int UpdateConfigV1(CONFIG_V1 *Src, CONFIG_V1 *Dest);

    /**
     * @brief Convert an HeaderV1 struc to a HeaderV.. struct.
     *
     * @warning This function isn't implemented for now and won't be until a Rev2 has been defined.
     *
     * @param Src A reference to the input header struct.
     * @param Dest A reference to the output header struct.
     *
     * @return  0 : OK
     * @return -1 : Update failed.
     */
    int UpdateHeaderV1(EEPROM_HEADER_V1 *Src, EEPROM_HEADER_V1 *Dest);
};
