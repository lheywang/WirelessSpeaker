/**
 * @file MCP9808.hpp
 * @authorl.heywang (leonard.heywang@gmail.com)
 * @brief Define a class and functions to exploit the MCP9808 Temperature Sensor.
 * @version 1.0
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 * @remark Class was tested successfully on 01/10/2024.
 *
 */
// prevent multiple include
#pragma once

// type include
#include <cstdint>
#include "../../I2C/I2C.hpp"

// ==============================================================================
// PUBLIC DEFINES
// ==============================================================================

// Resolution
#define C0_5 0x00
#define C0_25 0x01
#define C0_125 0x02
#define C0_0625 0x03

// Hysteresis Settings
#define HYST_0 0x00
#define HYST_1 0x01
#define HYST_3 0x02
#define HYST_6 0x03

// ==============================================================================
// IC CLASS FUNCTIONS
// ==============================================================================

/**
 * @brief Base class of the MCP808 Temp sensor. Contain functions to execute actions on it.
 *
 */
class MCP9808
{
private:
    uint8_t address;
    I2C_Bus I2C;

public:
    /**
     * @brief Construct a new MCP9808 object
     *
     * @param[in] I2C A pointer to the I2C struct that is used to handle IO operation on this bus.
     * @param[in] address The address of the IC on the I2C bus.
     */
    MCP9808(const I2C_Bus *I2C, const int address);

    /**
     * @brief Destroy the MCP9808 object
     *
     */
    ~MCP9808();

    /**
     * @brief Configure the device measurement resolution.
     *
     * @param[in] Resolution
     *
     * @return  0 : OK
     * @return -1 : Wrong resolution value
     * @return -2 : IOCTL error
     *
     */
    int ConfigureResolution(const int Resolution);

    /**
     * @brief Configure the temperature sensor with various parameters.
     *
     * @param[in] Hysteresis Configure Tupper and Tlower hystereris values. Used defined macros.
     * @param[in] Mode Configure Operation mode of the sensor ( 0 = Continous Conversion, 1 = Shutdown).
     * @param[in] Lock Block updates to Tlower, Tupper, Tcrit registers as well as some parameters here (0 = unlocked, 1 = locked).
     * @param[in] ClearInterrupt Clear actual interrupt. (1 = clear).
     * @param[in] AlertStatus Enable or Disable Output Interrupt pin (Asserted or High Z) ( 1= asserted, 0 = HighZ).
     * @param[in] AlertControl Enable or Disable the Interrupt subsystem (1 = Enabled, 0 = Disabled).
     * @param[in] AlertSelection Select the criteria for the Interrupt (1 = Ta > Tcrit, 0 = Tlower < Ta < Tupper + Ta < Tcrit).
     * @param[in] AlertPolarity Select the polarity of the Interrupt (1 = Active High, 0 = Active Low).
     * @param[in] AlertMode Select the Alter Mode (0 = Comparator Output, 1 = Interrupt Output).
     *
     * @return  0 : OK
     * @return -1 : Wrong Hysteresis value.
     * @return -2 : IOCTL error.
     *
     */
    int Configure(const int Hysteresis,
                  const int Mode,
                  const int Lock,
                  const int ClearInterrupt,
                  const int AlertStatus,
                  const int AlertControl,
                  const int AlertSelection,
                  const int AlertPolarity,
                  const int AlertMode);

    /**
     * @brief Returns the differents ID's of the device.
     *
     * @param[out] DeviceID Return a *int that contain the DeviceID.
     * @param[out] DeviceRevision Return a *int that contain the DeviceRevision.
     * @param[out] ManufacturerID Return a *int that contain the ManufacturerID.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error
     *
     */
    int GetIDs(int *const DeviceID, int *const DeviceRevision, int *const ManufacturerID);

    /**
     * @brief Set the Alert Temperatures object. Values are within the range -128 +127 °C
     *
     * @param[in] Minimal
     * @param[in] Maximal
     * @param[in] Critical
     *
     * @return  0 : OK
     * @return -1 : Out of range Minimal value.
     * @return -2 : Out of range Maximal value.
     * @return -3 : Out of range Critical value.
     * @return -4 : IOCTL error.
     *
     */
    int SetAlertTemperatures(const float Minimal, const float Maximal, const float Critical);

    /**
     * @brief Return the temperature read from the sensor.
     *
     * @param[out] Temperature Return a *float that contain the temperature.
     * @param[out] Status Return a *int for the device altert status.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     * @test Verify correct conversion.
     */
    int ReadTemperature(float *const Temperature, int *const Status);
};