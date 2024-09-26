/**
 * @file MCP9808.cpp
 * @author l.heywang
 * @brief Source of the functions for the MCP9808 Temperature Sensor.
 * @version 0.1
 * @date 2024-09-25
 *
 * @copyright Copyright (c) 2024
 *
 */

// Header file
#include "MCP9808.hpp"

// Cpp modules
#include <cstdint>
#include "../../I2C/I2C.hpp"

// =====================
// CONSTRUCTORS
// =====================

MCP9808::MCP9808(I2C_Bus *I2C, int address)
{
    this->address = (uint8_t)address;
    this->I2C = *I2C;
    return;
}

// =====================
// DESTRUCTORS
// =====================

MCP9808::~MCP9808()
{
    return;
}

// =====================
// FUNCTIONS
// =====================

int MCP9808::ConfigureResolution(int Resolution)
{
}

int MCP9808::ConfigureThermometer(int Hysteresis, int Mode, int Lock, int ClearInterrupt, int AlertStatus, int AlterControl, int AlterSelection, int AlterPolarity, int AltertMode)
{
}

int MCP9808::GetIDs(int *DeviceID, int *DeviceRevision, int *ManufacturerID)
{
}

int MCP9808::SetAlertTemperatures(float Minimal, float Maximal, float Critical)
{
}

int MCP9808::ReadTemperature(float *Temperature, int *Status)
{
    int buf[2] = {0};
    int res = I2C_Read(&this->I2C, this->address, this->ComputeRegister(READ_TEMP), buf, 2);

    *Status = (buf[0] & 0xE0) >> 5; // Fetch the status bits
}

// PRIVATE
uint8_t MCP9808::ComputeRegister(int Register)
{
    uint8_t TempRegister = (uint8_t)Register;
    TempRegister &= 0x0F; // Clear the last 4 bits
    return TempRegister;
}