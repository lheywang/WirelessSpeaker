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

#include "header.hpp"
#include "../../Drivers/SPI/SPI.hpp"

/**
 * @brief Write the header to the EEPROM. CRC is computed and wrote.
 *
 * @param[in] Header A reference to an header struct.
 *
 * @return  0 : OK
 * @return -1 : Write failed.
 */
int WriteHeaderV1(EEPROM_HEADER_V1 *const Header);

/**
 * @brief Read the header from the EEPROM. CRC is checked.
 *
 * @param[out] Header A reference to an header struct to be filled.
 *
 * @return  0 : OK
 * @return -1 : Read failed.
 * @return -2 : Invalid CRC.
 */
int ReadHeaderV1(EEPROM_HEADER_V1 *const Header);

/**
 * @brief Write the config to the EEPROM. Date and CRC are also updated.
 *
 * @param Data A reference to the Data structure to be wrote.
 *
 * @return  0 : OK
 * @return -1 : Write failed.
 */
int WriteConfigV1(ConfigV1 *const Data);

/**
 * @brief Read the config from the EEPROM. CRC is computed. An Header read is highly recommended to get the date.
 *
 * @param Data A reference to the Data structure to be filled.
 *
 * @return  0 : OK
 * @return -1 : Read failed.
 * @return -2 : Invalid CRC.
 */
int ReadConfigV1(ConfigV1 *const Data);

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
int UpdateConfigV1(ConfigV1 *Src, ConfigV1 *Dest);

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
