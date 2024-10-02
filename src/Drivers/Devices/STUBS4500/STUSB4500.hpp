/**
 * @file STUSB4500.hpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Base class for the STUSB4500 driver.
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

// =====================
// CUSTOM PDO OBJECTS
// =====================
/**
 * @brief Structure that store the elements that constitute a PDO object.
 *
 * @var PDO::Voltage The exact voltage requested.
 * @var PDO::Current The minimal current requestet.
 *
 */
struct PDO
{
    int Voltage;
    int Current;
};

struct RDO
{
    int t;
};

// ==============================================================================
// IC CLASS FUNCTIONS
// ==============================================================================

/**
 * @brief STUSB4500 base class, to exploit the basics functions of the USB-C Power delivery Interface.
 *
 */
class STUSB4500
{
private:
    uint8_t address;
    I2C_Bus I2C;

public:
    /**
     * @brief Construct a new STUSB4500 object
     *
     * @param[in] I2C A pointer to the I2C struct that is used to handle IO operation on this bus.
     * @param[in] address The address of the IC on the I2C bus.
     */
    STUSB4500(const I2C_Bus *I2C, const int address);

    /**
     * @brief Destroy the STUSB4500 object
     *
     */
    ~STUSB4500();

    /**
     * @brief Return the PD and USB-C norms versions
     *
     * @param[out] PD Pointer to an int to store the norm
     * @param[out] TYPEC ointer to an int to store the norm
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int GetNormsRevision(int *const PD, int *const TYPEC);

    /**
     * @brief Get the Port Status
     *
     * @param[out] Transition
     * @param[out] AttachedDeviceStatus
     * @param[out] LowPowerStatus
     * @param[out] PowerMode
     * @param[out] DataMode
     * @param[out] AttachStatus
     *
     * @return int
     */
    int GetPortStatus(int const *Transition,
                      int const *AttachedDeviceStatus,
                      int *const LowPowerStatus,
                      int *const PowerMode,
                      int *const DataMode,
                      int *const AttachStatus);

    /**
     * @brief Get the Power Delivery 3 Protocol status
     *
     * @param[out] VBUSHigh
     * @param[out] VBUSLow
     * @param[out] VBUSReady
     * @param[out] VBUSSafe
     * @param[out] VBUSValid
     * @return
     */
    int GetPD3Status(int *const VBUSHigh,
                     int *const VBUSLow,
                     int *const VBUSReady,
                     int *const VBUSSafe,
                     int *const VBUSValid);

    /**
     * @brief Get the Hardware status
     *
     * @param[out] OVP
     * @param[out] VPUValid
     * @param[out] VbusDischFault
     * @return
     */
    int GetHardwareFault(int *const OVP, int *const VPUValid, int *const VbusDischFault);

    /**
     * @brief Get the Type C Connection Status
     *
     * @param[out] TypeCStatus
     * @param[out] ConnectionOrientation
     * @param[out] FSMStatus
     * @return
     */
    int GetTypeCStatus(int *const TypeCStatus, int *const ConnectionOrientation, int *const FSMStatus);

    /**
     * @brief Configure the VBUS Monitoring Status
     *
     * @param[in] DischargeThreshold
     * @param[in] VbusComparator
     * @param[in] VBUSHighCompare
     * @param[in] VBUSLowCompare
     * @param[in] OVPLevel
     * @param[in] UVPLevel
     * @param[in] EnableReset
     * @return
     */
    int SetVBUSMonitoring(const int DischargeThreshold,
                          const int VbusComparator,
                          const int VBUSHighCompare,
                          const int VBUSLowCompare,
                          const int OVPLevel,
                          const int UVPLevel,
                          const int EnableReset);

    /**
     * @brief Configure the way the IC is going to drop the VBUS to the right level.
     *
     * @param[in] DischargeTo0V
     * @param[in] DischargeToNext
     * @param[in] EnableVBUSPath
     * @param[in] EnableVSRCPath
     * @param[in] ForceAssertion
     * @return
     */
    int SetVBUSDischarge(const int DischargeTo0V,
                         const int DischargeToNext,
                         const int EnableVBUSPath,
                         const int EnableVSRCPath,
                         const int ForceAssertion);

    /**
     * @brief Configure the state of the GPIO3
     *
     * @param[in] Status
     * @return
     */
    int SetGPIO3(const int Status);

    /**
     * @brief Return the RX Header
     *
     * @param[out] Header
     * @return
     */
    int GetRXHeader(int *const Header);

    /**
     * @brief Return a RXDataObject
     *
     * @param[in] ObjNumber
     * @param[out] OBJ
     * @return
     */
    int GetRXDataObj(const int ObjNumber, int *const OBJ);

    /**
     * @brief Return a PDO
     *
     * @param[in] PDONumber
     * @param[out] PDO
     * @return
     */
    int GetPDO(const int PDONumber, PDO *const PDO);

    /**
     * @brief Define a PDO
     *
     * @param[in] PDONumber
     * @param[out] PDO
     * @return
     */
    int SetPDO(const int PDONumber, const PDO PDO);

    /**
     * @brief Return the RDO
     *
     * @param[in] RDO
     * @return
     */
    int GetRDO(RDO *const RDO);

    /**
     * @brief Set the RDO
     * @param[out] RDO
     * @return
     */
    int SetRDO(const RDO RDO);
};