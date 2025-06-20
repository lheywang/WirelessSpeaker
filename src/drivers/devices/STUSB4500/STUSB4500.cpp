/**
 * @file STUSB4500.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Source for the STUSB4500 class.
 * @version 0.1
 * @date 2024-10-02
 *
 * @copyright Copyright (c) 2024
 *
 */

// Header file
#include "drivers/devices/STUSB4500.hpp"

// Drivers
#include "drivers/peripherals/i2c.hpp"

// STD
#include <cstdint>
#include <math.h>
#include <stdio.h>

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================
constexpr int BASE_ADDRESS = 0x00;

// All addresses are expressed an an offset from the base !
constexpr int TYPEC_REV_LSB = BASE_ADDRESS + 0x06;
constexpr int TYPEC_REV_MSB = BASE_ADDRESS + 0x07;
constexpr int PD_REV_LSB = BASE_ADDRESS + 0x08;
constexpr int PD_REV_MSB = BASE_ADDRESS + 0x09;

constexpr int ALERT_STATUS_1 = BASE_ADDRESS + 0x0B;
constexpr int ALERT_STATUS_1_MASK = BASE_ADDRESS + 0x0C;
constexpr int PORT_STATUS_0 = BASE_ADDRESS + 0x0D;
constexpr int PORT_STATUS_1 = BASE_ADDRESS + 0x0E;
constexpr int TYPEC_STATUS_0 = BASE_ADDRESS + 0x0F;
constexpr int TYPEC_STATUS_1 = BASE_ADDRESS + 0x10;
constexpr int CCSTATUS = BASE_ADDRESS + 0x011;
constexpr int HW_FAULT_0 = BASE_ADDRESS + 0x12;
constexpr int HW_FAULT_1 = BASE_ADDRESS + 0x13;
constexpr int PD_STATUS = BASE_ADDRESS + 0x14;
constexpr int USB_STATUS = BASE_ADDRESS + 0x15;
constexpr int PRT_STATUS = BASE_ADDRESS + 0x16;

constexpr int MONITORING_CTRL_0 = BASE_ADDRESS + 0x20;

constexpr int MONITORING_CTRL_2 = BASE_ADDRESS + 0x22;
constexpr int MONITORING_RESET = BASE_ADDRESS + 0x23;

constexpr int VBUS_DISCHARGE_TIME = BASE_ADDRESS + 0x25;
constexpr int VBUS_DISCHARGE_CTRL = BASE_ADDRESS + 0x26;
constexpr int VBUS_CTRL = BASE_ADDRESS + 0x27;

constexpr int GPIO3_SW = BASE_ADDRESS + 0x2D;

constexpr int RX_HEADER_LSB = BASE_ADDRESS + 0x31;
constexpr int RX_HEADER_MSB = BASE_ADDRESS + 0x32;
constexpr int RX_DATA_OBJ1_0 = BASE_ADDRESS + 0x33; // OBJ1
constexpr int RX_DATA_OBJ1_1 = BASE_ADDRESS + 0x34;
constexpr int RX_DATA_OBJ1_2 = BASE_ADDRESS + 0x35;
constexpr int RX_DATA_OBJ1_3 = BASE_ADDRESS + 0x36;
constexpr int RX_DATA_OBJ2_0 = BASE_ADDRESS + 0x37; // OBJ2
constexpr int RX_DATA_OBJ2_1 = BASE_ADDRESS + 0x38;
constexpr int RX_DATA_OBJ2_2 = BASE_ADDRESS + 0x39;
constexpr int RX_DATA_OBJ2_3 = BASE_ADDRESS + 0x3A;
constexpr int RX_DATA_OBJ3_0 = BASE_ADDRESS + 0x3B; // OBJ3
constexpr int RX_DATA_OBJ3_1 = BASE_ADDRESS + 0x3C;
constexpr int RX_DATA_OBJ3_2 = BASE_ADDRESS + 0x3D;
constexpr int RX_DATA_OBJ3_3 = BASE_ADDRESS + 0x3E;
constexpr int RX_DATA_OBJ4_0 = BASE_ADDRESS + 0x3F; // OBJ4
constexpr int RX_DATA_OBJ4_1 = BASE_ADDRESS + 0x40;
constexpr int RX_DATA_OBJ4_2 = BASE_ADDRESS + 0x41;
constexpr int RX_DATA_OBJ4_3 = BASE_ADDRESS + 0x42;
constexpr int RX_DATA_OBJ5_0 = BASE_ADDRESS + 0x43; // OBJ5
constexpr int RX_DATA_OBJ5_1 = BASE_ADDRESS + 0x44;
constexpr int RX_DATA_OBJ5_2 = BASE_ADDRESS + 0x45;
constexpr int RX_DATA_OBJ5_3 = BASE_ADDRESS + 0x46;
constexpr int RX_DATA_OBJ6_0 = BASE_ADDRESS + 0x47; // OBJ6
constexpr int RX_DATA_OBJ6_1 = BASE_ADDRESS + 0x48;
constexpr int RX_DATA_OBJ6_2 = BASE_ADDRESS + 0x49;
constexpr int RX_DATA_OBJ6_3 = BASE_ADDRESS + 0x4A;
constexpr int RX_DATA_OBJ7_0 = BASE_ADDRESS + 0x4B; // OBJ7
constexpr int RX_DATA_OBJ7_1 = BASE_ADDRESS + 0x4C;
constexpr int RX_DATA_OBJ7_2 = BASE_ADDRESS + 0x4D;
constexpr int RX_DATA_OBJ7_3 = BASE_ADDRESS + 0x4E;

constexpr int DPM_PDO_NUMB = BASE_ADDRESS + 0x70;

constexpr int DPM_SNK_PDO1_0 = BASE_ADDRESS + 0x85; // PD01
constexpr int DPM_SNK_PDO1_1 = BASE_ADDRESS + 0x86;
constexpr int DPM_SNK_PDO1_2 = BASE_ADDRESS + 0x87;
constexpr int DPM_SNK_PDO1_3 = BASE_ADDRESS + 0x88;
constexpr int DPM_SNK_PDO2_0 = BASE_ADDRESS + 0x89; // PDO2
constexpr int DPM_SNK_PDO2_1 = BASE_ADDRESS + 0x8A;
constexpr int DPM_SNK_PDO2_2 = BASE_ADDRESS + 0x8B;
constexpr int DPM_SNK_PDO2_3 = BASE_ADDRESS + 0x8C;
constexpr int DPM_SNK_PDO3_0 = BASE_ADDRESS + 0x8D; // PDO3
constexpr int DPM_SNK_PDO3_1 = BASE_ADDRESS + 0x8E;
constexpr int DPM_SNK_PDO3_2 = BASE_ADDRESS + 0x8F;
constexpr int DPM_SNK_PDO3_3 = BASE_ADDRESS + 0x90;

constexpr int DPM_SNK_RDO3_0 = BASE_ADDRESS + 0x91; // RDO3
constexpr int DPM_SNK_RDO3_1 = BASE_ADDRESS + 0x92;
constexpr int DPM_SNK_RDO3_2 = BASE_ADDRESS + 0x93;
constexpr int DPM_SNK_RDO3_3 = BASE_ADDRESS + 0x94;

constexpr float VOLTAGE_MINIMAL_STEP = 0.050;
constexpr float CURRENT_MINIMAL_STEP = 0.010;

// =====================
// CONSTRUCTORS
// =====================

STUSB4500::STUSB4500(const I2C_Bus* I2C, const USB_PD address)
{
    this->address = (uint8_t)address;
    this->I2C = *I2C;
    return;
}

// =====================
// DESTRUCTORS
// =====================

STUSB4500::~STUSB4500()
{
    return;
}

// =====================
// FUNCTIONS
// =====================

int STUSB4500::GetNormsRevision(int* const PD, int* const TYPEC)
{
    int buf[4] = {0};
    int res = 0;

    res += I2C_Read(&this->I2C, this->address, TYPEC_REV_LSB, &buf[0]);
    res += I2C_Read(&this->I2C, this->address, TYPEC_REV_MSB, &buf[1]);
    res += I2C_Read(&this->I2C, this->address, PD_REV_LSB, &buf[2]);
    res += I2C_Read(&this->I2C, this->address, PD_REV_MSB, &buf[3]);

    if(res != 0)
        return -1;

    *TYPEC = (buf[1] << 8) | buf[0];
    *PD = (buf[3] << 8) | buf[2];
    return 0;
}

int STUSB4500::GetPortStatus(int* const Transition,
                             int* const AttachedDeviceStatus,
                             int* const LowPowerStatus,
                             int* const PowerMode,
                             int* const DataMode,
                             int* const AttachStatus)
{
    int buf[2] = {0};
    int res = 0;

    res += I2C_Read(&this->I2C, this->address, PORT_STATUS_0, &buf[0]);
    res += I2C_Read(&this->I2C, this->address, PORT_STATUS_1, &buf[1]);

    if(res != 0)
        return -1;

    *Transition = buf[0] & 0x01;
    *AttachedDeviceStatus = (buf[1] & 0xE0) >> 5;
    *LowPowerStatus = (buf[1] & 0x10) >> 4;
    *PowerMode = (buf[1] & 0x08) >> 3;
    *DataMode = (buf[1] & 0x04) >> 2;
    *AttachStatus = buf[1] & 0x01;
    return 0;
}

int STUSB4500::GetPD3Status(int* const VBUSHigh,
                            int* const VBUSLow,
                            int* const VBUSReady,
                            int* const VBUSSafe,
                            int* const VBUSValid)
{
    int buf = 0;
    int res = 0;

    res += I2C_Read(&this->I2C, this->address, TYPEC_STATUS_0, &buf);

    if(res != 0)
        return -1;

    *VBUSHigh = (buf & 0x20) >> 5;
    *VBUSLow = (buf & 0x10) >> 4;
    *VBUSReady = (buf & 0x08) >> 3;
    *VBUSSafe = (buf & 0x04) >> 2;
    *VBUSValid = (buf & 0x02) >> 1;
    return 0;
}

int STUSB4500::GetHardwareFault(int* const OVPTrans,
                                int* const VPUValidTrans,
                                int* const VbusDischFaultTrans,
                                int* const OVPFault,
                                int* const VPUValid,
                                int* const VbusDischFault,
                                int* const VsrcDischFault)
{
    int res = 0;
    int buf[2] = {0};

    res += I2C_Read(&this->I2C, this->address, HW_FAULT_0, &buf[0]);
    res += I2C_Read(&this->I2C, this->address, HW_FAULT_0, &buf[1]);

    if(res != 0)
        return -1;

    *OVPTrans = (buf[0] & 0x20) >> 5;
    *VPUValidTrans = (buf[0] & 0x10) >> 4;
    *VbusDischFaultTrans = (buf[0] & 0x08) >> 3;
    *OVPFault = (buf[1] & 0x80) >> 7;
    *VPUValid = (buf[1] & 0x40) >> 6;
    *VbusDischFault = (buf[1] & 0x10) >> 4;
    *VsrcDischFault = (buf[1] & 0x08) >> 3;
    return 0;
}

int STUSB4500::GetTypeCStatus(int* const TypeCStatus,
                              int* const ConnectionOrientation,
                              int* const FSMStatus)
{
    int res = 0;
    int buf[2] = {0};

    res += I2C_Read(&this->I2C, this->address, USB_STATUS, &buf[0]);
    res += I2C_Read(&this->I2C, this->address, PRT_STATUS, &buf[0]);

    if(res != 0)
        return -1;

    *ConnectionOrientation = (buf[0] & 0x80) >> 7;
    *FSMStatus = buf[0] & 0x1F;
    *TypeCStatus = buf[1] & 0x1F;

    return 0;
}

int STUSB4500::SetVBUSMonitoring(const int DischargeThreshold,
                                 const int OVPLevel,
                                 const int UVPLevel,
                                 const int EnableReset)
{
    if((0 > OVPLevel) | (OVPLevel > 0x0F))
        return -1;
    if((0 > UVPLevel) | (UVPLevel > 0x0F))
        return -2;

    int res = 0;
    int buf[3] = {0};

    buf[0] = (bool)DischargeThreshold << 3;

    buf[1] = (OVPLevel << 4) | UVPLevel;

    buf[2] = (bool)EnableReset;

    res += I2C_Write(&this->I2C, this->address, MONITORING_CTRL_0, &buf[0]);
    res += I2C_Write(&this->I2C, this->address, MONITORING_CTRL_2, &buf[1]);
    res += I2C_Write(&this->I2C, this->address, MONITORING_RESET, &buf[2]);

    if(res != 0)
        return -3;
    return 0;
}

int STUSB4500::SetVBUSDischarge(const int DischargeTo0V,
                                const int DischargeToNext,
                                const int EnableVBUSPath,
                                const int ForceAssertion)
{
    if((0 > DischargeTo0V) | (DischargeTo0V > 0x0F))
        return -1;
    if((0 > DischargeToNext) | (DischargeToNext > 0x0F))
        return -2;

    int buf[3] = {0};
    int res = 0;

    buf[0] = (DischargeTo0V & 0x0F) << 4;
    buf[0] |= (DischargeToNext & 0x0F);

    buf[1] = (bool)EnableVBUSPath << 7;

    buf[2] = (bool)ForceAssertion << 1;

    res += I2C_Write(&this->I2C, this->address, VBUS_DISCHARGE_TIME, &buf[0]);
    res += I2C_Write(&this->I2C, this->address, VBUS_DISCHARGE_CTRL, &buf[1]);
    res += I2C_Write(&this->I2C, this->address, VBUS_CTRL, &buf[2]);

    if(res != 0)
        return -3;
    return 0;
}

int STUSB4500::SetGPIO3(const int Status)
{
    int res = 0;
    int buf = 0;

    buf = (bool)Status;

    res += I2C_Write(&this->I2C, this->address, GPIO3_SW, &buf);

    if(res != 0)
        return -1;
    return 0;
}

int STUSB4500::GetRXHeader(int* const Header)
{
    int res = 0;
    int buf[2] = {0};

    res += I2C_Read(&this->I2C, this->address, RX_HEADER_LSB, &buf[0]);
    res += I2C_Read(&this->I2C, this->address, RX_HEADER_MSB, &buf[1]);

    if(res != 0)
        return -1;
    *Header = (buf[1] << 8) | buf[0];
    return 0;
}

int STUSB4500::GetPDO(const int PDONumber, PDO* const PDO)
{
    int res = 0;
    int buf[4] = {0};

    int offset = 0;
    switch(PDONumber)
    {
    case 1:
        offset = 0;
        break;
    case 2:
        offset = 4;
        break;
    case 3:
        offset = 8;
        break;
    default:
        return -1;
    }

    res += I2C_Read(&this->I2C, this->address, DPM_SNK_PDO1_0 + offset, &buf[0]); // reg 0 (0-7)
    res += I2C_Read(&this->I2C, this->address, DPM_SNK_PDO1_1 + offset, &buf[1]); // reg 1 (8-15)
    res += I2C_Read(&this->I2C, this->address, DPM_SNK_PDO1_2 + offset, &buf[2]); // reg 2 (16-23)
    res += I2C_Read(&this->I2C, this->address, DPM_SNK_PDO1_3 + offset, &buf[3]); // reg 3 (24-31)

    if(res != 0)
        return -2;

    PDO->FixedSupply = (buf[3] & 0xC0) >> 6;
    PDO->DualRole = (bool)((buf[3] & 0x20) >> 5);
    PDO->HighCapability = (bool)((buf[3] & 0x10) >> 4);
    PDO->UnconstrainedPower = (bool)((buf[3] & 0x08) >> 3);
    PDO->USBCommCapable = (bool)((buf[3] & 0x04) >> 2);
    PDO->DualRoleData = (bool)((buf[3] & 0x02) >> 1);
    PDO->FastSwap = ((buf[3] & 0x01) << 1) | ((buf[2] & 0x80) >> 7);

    PDO->Voltage =
        (float)((((buf[2] & 0x0F) << 6) | ((buf[1] & 0xFC) >> 2)) * VOLTAGE_MINIMAL_STEP);
    PDO->Current = (float)((((buf[2] & 0x03) << 8) | (buf[0])) * CURRENT_MINIMAL_STEP);
    return 0;
}

int STUSB4500::SetPDO(const int PDONumber, const PDO PDO)
{
    if(((int)USB_PSU_MODE::FIXED > PDO.FixedSupply) | (PDO.FixedSupply > (int)USB_PSU_MODE::PPS))
        return -1;
    if(((int)USB_SWAP::FAST_SWAP_DISABLED > PDO.FastSwap) | (PDO.FastSwap > (int)USB_SWAP::V5_A3))
        return -2;
    if(!PDO.HighCapability) // Check if we go higher than 3A without enabling High Capability bool
    {
        if(round(PDO.Current) > 3.0)
            return -4;
    }

    int res = 0;
    int buf[4] = {0};

    int offset = 0;
    switch(PDONumber)
    {
    case 1:
        offset = 0;
        break;
    case 2:
        offset = 4;
        break;
    case 3:
        offset = 8;
        break;
    default:
        return -1;
    }

    // Reg 3
    buf[3] = PDO.FixedSupply;
    buf[3] = buf[3] << 2 | PDO.DualRole;
    buf[3] = buf[3] << 1 | PDO.HighCapability;
    buf[3] = buf[3] << 1 | PDO.UnconstrainedPower;
    buf[3] = buf[3] << 1 | PDO.USBCommCapable;
    buf[3] = buf[3] << 1 | PDO.DualRoleData;
    buf[3] = buf[3] << 1 | ((PDO.FastSwap & 0x02) >> 1);

    // Reg 2
    buf[2] = (PDO.FastSwap & 0x01);
    buf[2] = buf[2] << 3;
    buf[2] = buf[2] | ((int)(PDO.Voltage / VOLTAGE_MINIMAL_STEP) & 0x0F00);

    // Reg 1
    buf[1] = ((int)(PDO.Voltage / VOLTAGE_MINIMAL_STEP) & 0x00FC) << 2;
    buf[1] = buf[1] | ((int)(PDO.Current / CURRENT_MINIMAL_STEP) & 0x0300);

    // Reg 0
    buf[0] = ((int)(PDO.Current / CURRENT_MINIMAL_STEP) & 0x00FF);

    res += I2C_Write(&this->I2C, this->address, DPM_SNK_PDO1_0 + offset, &buf[0]);
    res += I2C_Write(&this->I2C, this->address, DPM_SNK_PDO1_1 + offset, &buf[1]);
    res += I2C_Write(&this->I2C, this->address, DPM_SNK_PDO1_2 + offset, &buf[2]);
    res += I2C_Write(&this->I2C, this->address, DPM_SNK_PDO1_3 + offset, &buf[3]);

    if(res != 0)
        return -5;
    return 0;
}

int STUSB4500::GetRDO(RDO* const RDO)
{
    int res = 0;
    int buf[4] = {0};

    res += I2C_Read(&this->I2C, this->address, DPM_SNK_PDO1_0, &buf[0]); // reg 0 (0-7)
    res += I2C_Read(&this->I2C, this->address, DPM_SNK_PDO1_1, &buf[1]); // reg 1 (8-15)
    res += I2C_Read(&this->I2C, this->address, DPM_SNK_PDO1_2, &buf[2]); // reg 2 (16-23)
    res += I2C_Read(&this->I2C, this->address, DPM_SNK_PDO1_3, &buf[3]); // reg 3 (24-31)

    if(res != 0)
        return -1;

    RDO->RequestedPDOID = (buf[3] & 0x70) >> 4;
    this->GetPDO(RDO->RequestedPDOID, &RDO->RequestedPDO);
    RDO->GiveBackFlag = (buf[3] & 0x08) >> 3;
    RDO->CapabilityMismatch = (buf[3] & 0x04) >> 2;
    RDO->USBCommCapable = (buf[3] & 0x02) >> 1;
    RDO->USBSuspend = buf[3] & 0x01;

    RDO->NominalCurrent =
        (float)((((buf[2] & 0x0F) << 6) | ((buf[1] & 0xFC) >> 2)) * CURRENT_MINIMAL_STEP);
    RDO->MinimalCurrent = (float)((((buf[2] & 0x03) << 8) | (buf[0])) * CURRENT_MINIMAL_STEP);
    return 0;
}
