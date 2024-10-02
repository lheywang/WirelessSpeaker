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
#include "STUSB4500.hpp"

// Cpp modules
#include <cstdint>
#include <stdio.h>
#include "../../I2C/I2C.hpp"

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================
#define TYPEC_REV_LSB 0x06
#define TYPEC_REV_MSB 0x07
#define PD_REV_LSB 0x08
#define PD_REV_MSB 0x09

#define ALERT_STATUS_1 0x0B
#define ALERT_STATUS_1_MASK 0x0C
#define PORT_STATUS_0 0x0D
#define PORT_STATUS_1 0x0E
#define TYPEC_STATUS_0 0x0F
#define TYPEC_STATUS_1 0x10
#define CCSTATUS 0x011
#define HW_FAULT_0 0x12
#define HW_FAULT_1 0x13
#define PD_STATUS 0x14
#define USB_STATUS 0x15
#define PRT_STATUS 0x16

#define MONITORING_CTRL_0 0x20

#define MONITORING_CTRL_2 0x22
#define MONITORING_RESET 0x23

#define VBUS_DISCHARGE_TIME 0x25
#define VBUS_DISCHARGE_CTRL 0x26
#define VBUS_CTRL 0x27

#define GPIO3_SW 0x2D

#define RX_HEADER_LSB 0x31
#define RX_HEADER_MSB 0x32
#define RX_DATA_OBJ1_0 0x33 // OBJ1
#define RX_DATA_OBJ1_1 0x34
#define RX_DATA_OBJ1_2 0x35
#define RX_DATA_OBJ1_3 0x36
#define RX_DATA_OBJ2_0 0x37 // OBJ2
#define RX_DATA_OBJ2_1 0x38
#define RX_DATA_OBJ2_2 0x39
#define RX_DATA_OBJ2_3 0x3A
#define RX_DATA_OBJ3_0 0x3B // OBJ3
#define RX_DATA_OBJ3_1 0x3C
#define RX_DATA_OBJ3_2 0x3D
#define RX_DATA_OBJ3_3 0x3E
#define RX_DATA_OBJ4_0 0x3F // OBJ4
#define RX_DATA_OBJ4_1 0x40
#define RX_DATA_OBJ4_2 0x41
#define RX_DATA_OBJ4_3 0x42
#define RX_DATA_OBJ5_0 0x43 // OBJ5
#define RX_DATA_OBJ5_1 0x44
#define RX_DATA_OBJ5_2 0x45
#define RX_DATA_OBJ5_3 0x46
#define RX_DATA_OBJ6_0 0x47 // OBJ6
#define RX_DATA_OBJ6_1 0x48
#define RX_DATA_OBJ6_2 0x49
#define RX_DATA_OBJ6_3 0x4A
#define RX_DATA_OBJ7_0 0x4B // OBJ7
#define RX_DATA_OBJ7_1 0x4C
#define RX_DATA_OBJ7_2 0x4D
#define RX_DATA_OBJ7_3 0x4E

#define DPM_PDO_NUMB 0x70

#define DPM_SNK_PDO1_0 0x85 // PD01
#define DPM_SNK_PDO1_1 0x86
#define DPM_SNK_PDO1_2 0x87
#define DPM_SNK_PDO1_3 0x88
#define DPM_SNK_PDO2_0 0x89 // PDO2
#define DPM_SNK_PDO2_1 0x8A
#define DPM_SNK_PDO2_2 0x8B
#define DPM_SNK_PDO2_3 0x8C
#define DPM_SNK_PDO3_0 0x8D // PDO3
#define DPM_SNK_PDO3_1 0x8E
#define DPM_SNK_PDO3_2 0x8F
#define DPM_SNK_PDO3_3 0x90

#define DPM_SNK_RDO3_0 0x91 // RDO3
#define DPM_SNK_RDO3_1 0x92
#define DPM_SNK_RDO3_2 0x93
#define DPM_SNK_RDO3_3 0x94

// =====================
// CONSTRUCTORS
// =====================

STUSB4500::STUSB4500(const I2C_Bus *I2C, const int address)
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

int STUSB4500::GetNormsRevision(int *const PD, int *const TYPEC)
{
    return 0;
}

int STUSB4500::GetPortStatus(int const *Transition,
                             int const *AttachedDeviceStatus,
                             int *const LowPowerStatus,
                             int *const PowerMode,
                             int *const DataMode,
                             int *const AttachStatus)
{
    return 0;
}

int STUSB4500::GetPD3Status(int *const VBUSHigh,
                            int *const VBUSLow,
                            int *const VBUSReady,
                            int *const VBUSSafe,
                            int *const VBUSValid)
{
    return 0;
}

int STUSB4500::GetHardwareFault(int *const OVP, int *const VPUValid, int *const VbusDischFault)
{
    return 0;
}

int STUSB4500::GetTypeCStatus(int *const TypeCStatus, int *const ConnectionOrientation, int *const FSMStatus)
{
    return 0;
}

int STUSB4500::SetVBUSMonitoring(const int DischargeThreshold,
                                 const int VbusComparator,
                                 const int VBUSHighCompare,
                                 const int VBUSLowCompare,
                                 const int OVPLevel,
                                 const int UVPLevel,
                                 const int EnableReset)
{
    return 0;
}

int STUSB4500::SetVBUSDischarge(const int DischargeTo0V,
                                const int DischargeToNext,
                                const int EnableVBUSPath,
                                const int EnableVSRCPath,
                                const int ForceAssertion)
{
    return 0;
}

int STUSB4500::SetGPIO3(const int Status)
{
    return 0;
}

int STUSB4500::GetRXHeader(int *const Header)
{
    return 0;
}

int STUSB4500::GetRXDataObj(const int ObjNumber, int *const OBJ)
{
    return 0;
}

int STUSB4500::GetPDO(const int PDONumber, PDO *const PDO)
{
    return 0;
}

int STUSB4500::SetPDO(const int PDONumber, const PDO PDO)
{
    return 0;
}

int STUSB4500::GetRDO(RDO *const RDO)
{
    return 0;
}

int STUSB4500::SetRDO(const RDO RDO)
{
    return 0;
}