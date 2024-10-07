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
// PUBLIC DEFINES
// =====================
#define FAST_SWAP_DISABLED 0x00
#define DEFAULT_USB_POWER 0x01
#define V5_A1_5 0x02
#define V5_A3 0x03

#define ENABLE_PPS 0x01
#define FIXED_PD2 0x00

// =====================
// CUSTOM PDO OBJECTS
// =====================
/**
 * @struct PDO
 * @brief Structure that store the elements that constitute a PDO object.
 *
 * @var PDO::Voltage The exact voltage requested.
 * @var PDO::Current The minimal current requestet.
 *
 * @var PDO::FixedSupply Select the working mode of the IC.
 * @var PDO::DualRole Can the IC source current ?
 * @var PDO::HighCapability Enable 5A profile.
 * @var PDO::UnconstrainedPower Remove any constraints for the POWER
 * @var PDO::USBCommCapable Enable USB Communication
 * @var PDO::DualRoleData Enable DFP or UFP Data mode.
 * @var PDO::FastSwap Enable fast swap on defined profile.
 *
 */
struct PDO
{
    int FixedSupply = FIXED_PD2;
    bool DualRole = false;
    bool HighCapability = false;
    bool UnconstrainedPower = false;
    bool USBCommCapable = true;
    bool DualRoleData = false;

    int FastSwap = FAST_SWAP_DISABLED;

    float Voltage;
    float Current;
};

/**
 * @struct RDO
 * @brief Structure that store the elements that constitute a PDO object.
 *
 * @var PDO::MinimalCurrent The exact voltage requested.
 * @var PDO::NominalCurrent The minimal current requestet.
 *
 * @var PDO::RequestedPDOID Select the working mode of the IC.
 * @var PDO::RequestedPDO PDO Object that has been requested.
 *
 * @var PDO::GiveBackFlag Can the IC source current ?
 * @var PDO::CapabilityMismatch Enable 5A profile.
 * @var PDO::USBSuspend Enable fast swap on defined profile.
 * @var PDO::UnchunkedMessages Enable fast swap on defined profile.
 *
 */
struct RDO
{
    int RequestedPDOID;
    PDO RequestedPDO;

    bool GiveBackFlag;
    bool CapabilityMismatch;
    bool USBCommCapable;
    bool USBSuspend;
    bool UnchunkedMessages;

    float MinimalCurrent;
    float NominalCurrent;
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
     *  Value  | Status
     *  ------ | ------
     *    0    | None
     *    1    | Sink
     *    2    | Source
     *    3    | Debug Device
     *    4    | Audio Device
     *    5    | Powered device
     *    6-7  | /
     *
     * @param[out] Transition A transisition of the attached status has been detected.
     * @param[out] AttachedDeviceStatus Give infos about the port status. Check table.
     * @param[out] LowPowerStatus Return the device operating mode (0 for LP, 1 for normal)
     * @param[out] PowerMode 0 for Power Sink, 1 for Power Source
     * @param[out] DataMode 0 for UFP, 1 for DFP
     * @param[out] AttachStatus 0 for unattached, 1 for attached
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int GetPortStatus(int *const Transition,
                      int *const AttachedDeviceStatus,
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
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int GetPD3Status(int *const VBUSHigh,
                     int *const VBUSLow,
                     int *const VBUSReady,
                     int *const VBUSSafe,
                     int *const VBUSValid);

    /**
     * @brief Get the Hardware status
     *
     * @param[out] OVPTrans
     * @param[out] VPUValidTrans
     * @param[out] VbusDischFaultTrans
     * @param[out] OVPFault
     * @param[out] VPUValid
     * @param[out] VbusDischFault
     * @param[out] VsrcDischFault
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int GetHardwareFault(int *const OVPTrans,
                         int *const VPUValidTrans,
                         int *const VbusDischFaultTrans,
                         int *const OVPFault,
                         int *const VPUValid,
                         int *const VbusDischFault,
                         int *const VsrcDischFault);

    /**
     * @brief Get the Type C Connection Status
     *
     *  Value  | TypeC Status
     *  ------ | ------
     *    0    | UNATTACHED_SNK
     *    1    | ATTACHWAIT_SNK
     *    2    | ATTACHED_SN
     *    3    | DEBUGACCESSORY_SNK
     *  4-11   | /
     *    12   | TRY_SRC
     *    13   | UNATTACHED_ACCESSOR
     *    14   | ATTACHWAIT_ACCESSORY
     * 15-18   | /
     *    19   | TYPEC_ERRORRECOVERY
     *  20-31  | /
     *
     *  Value  | FSM Status
     *  ------ | ------
     *    0    | UNATTACHED_SNK
     *    1    | ATTACHWAIT_SNK
     *    2    | ATTACHED_SNK
     *    3    | DEBUGACCESSORY_SNK
     *    4-5  | /
     *    6    | Intermediate state during PR Swap from sink to source
     *    7    | TRYWAIT_SNK
     *    8    | UNATTACHED_SRC
     *    9    | ATTACHWAIT_SRC
     *    10   | ATTACHED_SRC
     *    11   | Intermediate state during PR Swap from source to sink
     *    12   | TRY_SRC
     *    13   | UNATTACHED_ACCESSORY
     *    14   | ATTACHWAIT_ACCESSORY
     *    15   | AUDIOACCESSORY
     *    16   | UNORIENTEDDEBUGACCESSORY_SRC
     *    17   | POWERED_ACCESSORY
     *    18   | UNSUPPORTED_ACCESSORY
     *    19   | TYPEC_ERRORRECOVERY
     *    20   | Intermediate state towards TRY_SNK state
     *    21   | TRY_SNK
     *    22   | /
     *    23   | TRYWAIT_SRC
     *    24   | UNATTACHEDWAIT_SRC
     *    25   | ORIENTEDDEBUGACCESSORY_SRC
     *    26   | Intermediate state during PR Swap from source to sink
     *
     * @param[out] TypeCStatus TypeC status. Check table 1.
     * @param[out] ConnectionOrientation Return the orientation of the USB-C port.
     * @param[out] FSMStatus Return the Type C state machine status. Check table 2.
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int GetTypeCStatus(int *const TypeCStatus, int *const ConnectionOrientation, int *const FSMStatus);

    /**
     * @brief Configure the VBUS Monitoring Status
     *
     * @param[in] DischargeThreshold
     * @param[in] OVPLevel
     * @param[in] UVPLevel
     * @param[in] EnableReset
     *
     * @return  0 : OK
     * @return -1 : Incorrect OVP Value
     * @return -2 : Incorrect UVP Value
     * @return -3 : IOCTL error.
     */
    int SetVBUSMonitoring(const int DischargeThreshold,
                          const int OVPLevel,
                          const int UVPLevel,
                          const int EnableReset);

    /**
     * @brief Configure the way the IC is going to drop the VBUS to the right level.
     *
     * @param[in] DischargeTo0V
     * @param[in] DischargeToNext
     * @param[in] EnableVBUSPath
     * @param[in] ForceAssertion
     *
     * @return  0 : OK
     * @return -1 : Incorrect Discharge to 0V Value
     * @return -2 : Incorrect Dischagre to next value
     * @return -3 : IOCTL error.
     */
    int SetVBUSDischarge(const int DischargeTo0V,
                         const int DischargeToNext,
                         const int EnableVBUSPath,

                         const int ForceAssertion);

    /**
     * @brief Configure the state of the GPIO3
     *
     * @param[in] Status
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int SetGPIO3(const int Status);

    /**
     * @brief Return the RX Header
     *
     * @param[out] Header
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int GetRXHeader(int *const Header);

    /**
     * @brief Return a PDO
     *
     * @param[in] PDONumber
     * @param[out] PDO
     *
     * @return  0 : OK
     * @return -1 : Wrong PDO Number
     * @return -2 : IOCTL error.
     */
    int GetPDO(const int PDONumber, PDO *const PDO);

    /**
     * @brief Define a PDO
     *
     * @param[in] PDONumber
     * @param[out] PDO
     *
     * @return  0 : OK
     * @return -1 : Wrong PDO Number
     * @return -2 : IOCTL error.
     */
    int SetPDO(const int PDONumber, const PDO PDO);

    /**
     * @brief Return the RDO and read the selected PDO.
     *
     * @param[in] RDO
     *
     * @return  0 : OK
     * @return -1 : IOCTL error.
     */
    int GetRDO(RDO *const RDO);
};