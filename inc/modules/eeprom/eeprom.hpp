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

// ==============================================================================
// INCLUDES
// ==============================================================================
// Config file
#include "config/config.hpp"

// Drivers
#include "drivers/devices/M95256.hpp"
#include "drivers/peripherals/spi.hpp"

// Other elements
#include "dsp_profile/dsp_profile.hpp"
#include "header/header.hpp"

// ==============================================================================
// HEADER CONSTANTS
// ==============================================================================
constexpr int HEADER_SIZE = 128; /*!< Define the size in bytes of the header.*/
constexpr int HEADER_ADDRESS = 0x0000; /*!< Define the size of the header*/

// ==============================================================================
// CONFIG CONSTANTS
// ==============================================================================
constexpr int CONFIG_SIZE = 256; /*!< Define the base address of the config*/
constexpr int CONFIG_ADDRESS = 0x0080; /*!< Define the size of the config*/

// ==============================================================================
// EEPROM CONSTANTS
// ==============================================================================
constexpr int EEPROM_MAX_ADDRESS = 0x7FFF; /*!< Define the end of the EEPROM*/

// ==============================================================================
// CLASS
// ==============================================================================
/**
 * @brief Base class for the usage of the EEPROM.
 *        This class provide an high level interraction to the EEPROM with masked addressing procedures.
 *
 */
class EEPROM
{

private:
    M95256 Slave;
    EEPROM_HEADER_V1* Header;
    SPI_Bus* SPI;
    int ReadHeaderV1();
    int WriteHeaderV1();
    int SetConfigCRC(const uint16_t CRC);
    int GetConfigCRC(uint16_t* const CRC);

public:
    // ==============================================================================
    // CONSTRUCTORS
    // ==============================================================================
    /**
     * @brief Construct a new EEPROM
     *
     * @param[in] ForceWrite Ignore the read issues and force the write of a new header. Will be logged.
     *
     */
    EEPROM(bool ForceWrite = false);

    // ==============================================================================
    // DESTRUCTORS
    // ==============================================================================
    /**
     * @brief Destruct an EEPROM class.
     *
     */
    ~EEPROM();

    // ==============================================================================
    // GLOBAL MANAGEMENT
    // ==============================================================================

    /**
     * @brief Read the header from the EEPROM. CRC is checked.
     *
     * @param[out] Header A reference to an header struct to be filled.
     *
     * @return  0 : OK
     */
    int GetHeaderV1(EEPROM_HEADER_V1* const Header);

    /**
     * @brief Write the config to the EEPROM. Date and CRC are also updated.
     *
     * @param[in] Data A reference to the Data structure to be wrote.
     *
     * @return  0 : OK.
     * @return -1 : Memory allocation failed.
     * @return -2 : Write failed.
     */
    int WriteConfigV1(CONFIG_V1* const Data);

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
    int ReadConfigV1(CONFIG_V1* const Data);

    /**
     * @brief Ask for the software to load the default configuration.
     *
     * @return  0 : OK
     * @return -1 : Incorrect file size. Note : This error take it's root on the compilation steps. Cannot be easily debugged.
     * @return -2 : IOCTL error.
     */
    int LoadDefaultConfigV1();

    // ==============================================================================
    // DSP PROFILE FUNCTIONS
    // ==============================================================================

    /**
     * @brief Check if there is enough space of a DSP Profile of Len Size.
     *
     * @param[in] Profile A DSP_PROFILE Struct.
     * @param[out] PossibleProfileID Return the ID of the possible profile ID.
     *
     * @return  0 : OK
     * @return -1 : Not enough space.
     */
    int CheckForDSPProfileSpace(DSP_PROFILE* const Profile, int* const PossibleProfileID);

    /**
     * @brief Write a new DSP Profile to the EEPROM, if there is enough space for it.
     *
     * @param[in] Profile A pointer to a DSP_PROFILE struct member.
     * @param[out] ProfileNumber The function return the number of the DSP Profile that has been given to this profile.
     *
     * @return  0 : OK
     * @return -1 : Not enough space
     * @return -2 : Invalid pointer
     * @return -3 : IOCTL error.
     */
    int AddDSPProfile(DSP_PROFILE* const Profile, int* const ProfileNumber);

    /**
     * @brief Delete on the EEPROM (on the header only, the values remains until the next write)
     *
     * @param[in] ProfileNumber The number of the DSP Profile.
     *
     * @return  0 : OK
     * @return -1 : Invalid profile number value.
     * @return -2 : IOCTL error.
     */
    int RemoveDSPProfile(const int ProfileNumber);

    /**
     * @brief Return the name of a specific DSP Profile
     *
     * @param[in] ProfileNumber An integer to select a profile number.
     * @param[out] ProfileName A char array of MAX_PROFILE_CHAR length to be filled.
     *
     * @test To test with real data to ensure correct working...
     *
     * @return  0 : OK
     * @return -1 : Invalid profile number value.
     * @return -2 : IOCTL error.
     */
    int GetDSPProfileName(const int ProfileNumber, char ProfileName[MAX_PROFILE_CHAR]);

    /**
     * @brief Read the DSP Profile in memory and return it.
     *
     * @param[in] ProfileNumber An integer to select a profile number
     * @param[out] Profile A DSP_PROFILE object filled with the right size.
     *
     * @test To test with real data to ensure correct working...
     *
     * @return  0 : OK
     * @return -1 : Invalid profile number value.
     * @return -2 : Failed to allocate memory
     * @return -3 : IOCTL error.
     */
    int GetDSPProfile(const int ProfileNumber, DSP_PROFILE* const Profile);

    /**
     * @brief Return the size of a DSP Profile
     *
     * @param[in] ProfileNumber An integer to select a profile number
     * @param[out] Profile A member of the DSP_PROFILE_TYPE enum that evalute the size.
     *
     * @test To test with real data to ensure correct working...
     *
     * @return  0 : OK
     * @return -1 : Invalid profile number value.
     */
    int GetDSPProfileSize(const int ProfileNumber, DSP_PROFILE_SIZE* const Profile);
};
