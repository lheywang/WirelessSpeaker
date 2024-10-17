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

constexpr int HEADER_SIZE = 64;        /*!< Define the size in bytes of the header.*/
constexpr int HEADER_ADDRESS = 0x0000; /*!< Define the base address of the header*/

/**
 * @brief Write the header to the EEPROM. CRC is computed and wrote.
 *
 * @param[in] Header A reference to an header struct.
 * @param[in] Slave The M95256 SPI Slave to which the operation shall take.
 *
 * @return  0 : OK
 * @return -1 : Write failed.
 */
int EEPROM_WriteHeaderV1(M95256 Slave, EEPROM_HEADER_V1 *const Header);

/**
 * @brief Read the header from the EEPROM. CRC is checked.
 *
 * @param[out] Header A reference to an header struct to be filled.
 * @param[in] Slave The M95256 SPI Slave to which the operation shall take.
 *
 * @return  0 : OK
 * @return -1 : Read failed.
 * @return -2 : Invalid CRC.
 */
int EEPROM_ReadHeaderV1(M95256 Slave, EEPROM_HEADER_V1 *const Header);

/**
 * @brief Write the config to the EEPROM. Date and CRC are also updated.
 *
 * @param Data A reference to the Data structure to be wrote.
 * @param[in] Slave The M95256 SPI Slave to which the operation shall take.
 *
 * @return  0 : OK
 * @return -1 : Write failed.
 */
int EEPROM_WriteConfigV1(M95256 Slave, CONFIG_V1 *const Data);

/**
 * @brief Read the config from the EEPROM. CRC is computed. An Header read is highly recommended to get the date.
 *
 * @param Data A reference to the Data structure to be filled.
 * @param[in] Slave The M95256 SPI Slave to which the operation shall take.
 *
 * @return  0 : OK
 * @return -1 : Read failed.
 * @return -2 : Invalid CRC.
 */
int EEPROM_ReadConfigV1(M95256 Slave, CONFIG_V1 *const Data);

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
int EEPROM_UpdateConfigV1(CONFIG_V1 *Src, CONFIG_V1 *Dest);

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
int EEPROM_UpdateHeaderV1(EEPROM_HEADER_V1 *Src, EEPROM_HEADER_V1 *Dest);
