/**
 * @file INA219.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Base class for the INA219 Power monitor
 * @version 0.1
 * @date 2024-10-02
 *
 * @copyright Copyright (c) 2024
 *
 */

// prevent multiple include
#pragma once

// type include
#include <cstdint>
#include "../../I2C/I2C.hpp"

// ==============================================================================
// IC CLASS FUNCTIONS
// ==============================================================================

/**
 * @brief INA219 base class, to exploit the basics functions of this power monitor
 *
 */
class INA219
{
private:
    uint8_t address;
    I2C_Bus I2C;

    float ConvertIntToFloat(const int Value);
    int ConvertFloatToInt(const float Value);

    // number of sign numbers.
    int PGASetting;

public:
    /**
     * @brief Construct a new INA219 object
     *
     * @param[in] I2C A pointer to the I2C struct that is used to handle IO operation on this bus.
     * @param[in] address The address of the IC on the I2C bus.
     */
    INA219(const I2C_Bus *I2C, const CURRENT_MONITOR address);

    /**
     * @brief Destroy the INA219 object
     *
     */
    ~INA219();

    /**
     * @brief Configure the INA219 voltage monitor
     *
     * @param[in] Reset If set to 1, trigger an IC Reset
     * @param[in] BusVoltageRange Set the voltage range for the measurement. 0 = 16V FS, 1= 32V FS.
     * @param[in] SetPGAGain Configure the PGA Gain to make measures more precise. 00 for a +- 40mV, 01 for a +-80 mV, 10 for a +-160mV, 11 for a +- 320mV.
     * @param[in] BusVoltageADCResolution Configure the integration time. 0000 : 84 us / 9b. 1111 : 68.10 ms / 128 * 12b.
     * @param[in] BusCurrentADCResolution Configure the integration time. 0000 : 84 us / 9b. 1111 : 68.10 ms / 128 * 12b.
     * @param[in] OperatingMode Configure the operating mode. 000 = Power down, 001-011: Triggered. 100 : ADC Off. 101-111 : Continous.
     *
     * @return  0 : OK
     * @return -1 : Incorrect PGA Gain
     * @return -2 : Incorrect Bus ADC Resolution
     * @return -3 : Incorrect Current ADC Resolution
     * @return -4 : Incorrect Mode.
     * @return -5 : IOCTL error
     *
     * @test Function to test !
     */
    int Configure(const int Reset, const int BusVoltageRange, const int SetPGAGain, const int BusVoltageADCResolution, const int BusCurrentADCResolution, const int OperatingMode);

    /**
     * @brief Read the voltage on the Shunt, thus the current.
     *
     * @param[out] Value A pointer to a float to store the shunt voltage.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     * @test Function to test !
     */
    int ReadShuntVoltage(float *const Value);

    /**
     * @brief Read the bus voltage, referenced from ground.
     *
     * @param[out] Value A pointer to a float to store the bus voltage.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     * @test Function to test !
     */
    int ReadBusVoltage(float *const Value);

    /**
     * @brief Read the power (current * voltage)
     *
     * @param[out] Value A pointer to a float to store the bus voltage.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     * @test Function to test !
     */
    int ReadPower(float *const Value);

    /**
     * @brief Read the bus current
     *
     * @param[out] Value A pointer to a float to store the bus voltage.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     *
     * @test Function to test !
     */
    int ReadCurrent(float *const Value);

    /**
     * @brief Store the value used for the calibration. This is the full scale voltage drop for the shunt resistor.
     *
     * @param[out] Value A pointer to a float to store the bus voltage.
     *
     * @return  0 : OK
     * @return -1 : Error while casting the number.
     * @return -2 : IOCTL error.
     *
     * @test Function to test !
     */
    int SetCalibration(const float Value);
};