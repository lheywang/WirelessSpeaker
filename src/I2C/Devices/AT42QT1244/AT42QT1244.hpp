// ==============================================================================
//                              I2C/Devices/AT42QT1244/AT42QT1244.hpp
//                              Wrote by lheywang
//
// Define our basic I2C settings on the boards, such as :
// - Register Addresses
// ==============================================================================

// prevent multiple include
#pragma once

// type include
#include <cstdint>

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

#define AT42QT1244_DATA_SIZE 8 // 8b register here

// =====================
// STATUS
// =====================

#define COUNTER_100MS 0x02
#define SIGNAL_FAIL_COUNTER 0x03
#define MATRIX_SCAN_COUNTER 0x04
#define STATUS 0x05
#define DETECT_STATUS_0_7 0x6
#define DETECT_STATUS_8_15 0x07
#define DETECT_STATUS_16_23 0x08
#define CURRENT_FREQUENCY 0x0A
#define CURRENT_PULSE_SPACING 0x0B

// =====================
// KEY
// =====================

// KEY 0
#define DATA_KEY0_MSB 0x0C
#define DATA_KEY0_LSB 0x0D

// KEY 1
#define DATA_KEY1_MSB 0x0C
#define DATA_KEY1_LSB 0x0D

// KEY 2
#define DATA_KEY2_MSB 0x0C
#define DATA_KEY2_LSB 0x0D

// KEY 3
#define DATA_KEY3_MSB 0x0C
#define DATA_KEY3_LSB 0x0D

// KEY 4
#define DATA_KEY4_MSB 0x0C
#define DATA_KEY4_LSB 0x0D

// KEY 5
#define DATA_KEY5_MSB 0x0C
#define DATA_KEY5_LSB 0x0D

// KEY 6
#define DATA_KEY6_MSB 0x0C
#define DATA_KEY6_LSB 0x0D

// KEY 7
#define DATA_KEY7_MSB 0x0C
#define DATA_KEY7_LSB 0x0D

// KEY 8
#define DATA_KEY8_MSB 0x0C
#define DATA_KEY8_LSB 0x0D

// KEY 9
#define DATA_KEY9_MSB 0x0C
#define DATA_KEY9_LSB 0x0D

// KEY 10
#define DATA_KEY10_MSB 0x0C
#define DATA_KEY10_LSB 0x0D

// KEY 11
#define DATA_KEY11_MSB 0x0C
#define DATA_KEY11_LSB 0x0D

// KEY 12
#define DATA_KEY12_MSB 0x0C
#define DATA_KEY12_LSB 0x0D

// KEY 13
#define DATA_KEY13_MSB 0x0C
#define DATA_KEY13_LSB 0x0D

// KEY 14
#define DATA_KEY14_MSB 0x0C
#define DATA_KEY14_LSB 0x0D

// KEY 15
#define DATA_KEY15_MSB 0x0C
#define DATA_KEY15_LSB 0x0D

// KEY 16
#define DATA_KEY16_MSB 0x0C
#define DATA_KEY16_LSB 0x0D

// KEY 17
#define DATA_KEY17_MSB 0x0C
#define DATA_KEY17_LSB 0x0D

// KEY 18
#define DATA_KEY18_MSB 0x0C
#define DATA_KEY18_LSB 0x0D

// KEY 19
#define DATA_KEY19_MSB 0x0C
#define DATA_KEY19_LSB 0x0D

// KEY 20
#define DATA_KEY20_MSB 0x0C
#define DATA_KEY20_LSB 0x0D

// KEY 21
#define DATA_KEY21_MSB 0x0C
#define DATA_KEY21_LSB 0x0D

// KEY 22
#define DATA_KEY22_MSB 0x0C
#define DATA_KEY22_LSB 0x0D

// KEY 23
#define DATA_KEY23_MSB 0x0C
#define DATA_KEY23_LSB 0x0D

// =====================
// SETUP
// =====================
#define COMMAND 0x8C

// Thresholds settings for each keys
#define NTHR_PTHR_BL_NDRIFT_KEY0 0x8D
#define NTHR_PTHR_BL_NDRIFT_KEY1 0x8E
#define NTHR_PTHR_BL_NDRIFT_KEY2 0x8F
#define NTHR_PTHR_BL_NDRIFT_KEY3 0x90
#define NTHR_PTHR_BL_NDRIFT_KEY4 0x91
#define NTHR_PTHR_BL_NDRIFT_KEY5 0x92
#define NTHR_PTHR_BL_NDRIFT_KEY6 0x93
#define NTHR_PTHR_BL_NDRIFT_KEY7 0x94
#define NTHR_PTHR_BL_NDRIFT_KEY8 0x95
#define NTHR_PTHR_BL_NDRIFT_KEY9 0x96
#define NTHR_PTHR_BL_NDRIFT_KEY10 0x97
#define NTHR_PTHR_BL_NDRIFT_KEY11 0x98
#define NTHR_PTHR_BL_NDRIFT_KEY12 0x99
#define NTHR_PTHR_BL_NDRIFT_KEY13 0x9A
#define NTHR_PTHR_BL_NDRIFT_KEY14 0x9B
#define NTHR_PTHR_BL_NDRIFT_KEY15 0x9C
#define NTHR_PTHR_BL_NDRIFT_KEY16 0x9D
#define NTHR_PTHR_BL_NDRIFT_KEY17 0x9E
#define NTHR_PTHR_BL_NDRIFT_KEY18 0x9F
#define NTHR_PTHR_BL_NDRIFT_KEY19 0xA0
#define NTHR_PTHR_BL_NDRIFT_KEY20 0xA1
#define NTHR_PTHR_BL_NDRIFT_KEY21 0xA2
#define NTHR_PTHR_BL_NDRIFT_KEY22 0xA3
#define NTHR_PTHR_BL_NDRIFT_KEY23 0xA4

// Detection Integratos
#define NDIL_FDIL_AKS_WAKE_KEY0 0xA5
#define NDIL_FDIL_AKS_WAKE_KEY1 0xA6
#define NDIL_FDIL_AKS_WAKE_KEY2 0xA7
#define NDIL_FDIL_AKS_WAKE_KEY3 0xA8
#define NDIL_FDIL_AKS_WAKE_KEY4 0xA9
#define NDIL_FDIL_AKS_WAKE_KEY5 0xAA
#define NDIL_FDIL_AKS_WAKE_KEY6 0xAB
#define NDIL_FDIL_AKS_WAKE_KEY7 0xAC
#define NDIL_FDIL_AKS_WAKE_KEY8 0xAD
#define NDIL_FDIL_AKS_WAKE_KEY9 0xAE
#define NDIL_FDIL_AKS_WAKE_KEY10 0xAF
#define NDIL_FDIL_AKS_WAKE_KEY11 0xB0
#define NDIL_FDIL_AKS_WAKE_KEY12 0xB1
#define NDIL_FDIL_AKS_WAKE_KEY13 0xB2
#define NDIL_FDIL_AKS_WAKE_KEY14 0xB3
#define NDIL_FDIL_AKS_WAKE_KEY15 0xB4
#define NDIL_FDIL_AKS_WAKE_KEY16 0xB5
#define NDIL_FDIL_AKS_WAKE_KEY17 0xB6
#define NDIL_FDIL_AKS_WAKE_KEY18 0xB7
#define NDIL_FDIL_AKS_WAKE_KEY19 0xB8
#define NDIL_FDIL_AKS_WAKE_KEY20 0xB9
#define NDIL_FDIL_AKS_WAKE_KEY21 0xBA
#define NDIL_FDIL_AKS_WAKE_KEY22 0xBB
#define NDIL_FDIL_AKS_WAKE_KEY23 0xBC

// CFO1
#define CFO1_KEY0 0xBD
#define CFO1_KEY1 0xBE
#define CFO1_KEY2 0xBF
#define CFO1_KEY3 0xC0
#define CFO1_KEY4 0xC1
#define CFO1_KEY5 0xC2
#define CFO1_KEY6 0xC3
#define CFO1_KEY7 0xC4
#define CFO1_KEY8 0xC5
#define CFO1_KEY9 0xC6
#define CFO1_KEY10 0xC7
#define CFO1_KEY11 0xC8
#define CFO1_KEY12 0xC9
#define CFO1_KEY13 0xCA
#define CFO1_KEY14 0xCB
#define CFO1_KEY15 0xCC
#define CFO1_KEY16 0xCD
#define CFO1_KEY17 0xCE
#define CFO1_KEY18 0xCF
#define CFO1_KEY19 0xD0
#define CFO1_KEY20 0xD1
#define CFO1_KEY21 0xD2
#define CFO1_KEY22 0xD3
#define CFO1_KEY23 0xD4

// CFO2
#define CFO2_KEY0 0xD5
#define CFO2_KEY1 0xD6
#define CFO2_KEY2 0xD7
#define CFO2_KEY3 0xD8
#define CFO2_KEY4 0xD9
#define CFO2_KEY5 0xDA
#define CFO2_KEY6 0xDB
#define CFO2_KEY7 0xDC
#define CFO2_KEY8 0xDD
#define CFO2_KEY9 0xDE
#define CFO2_KEY10 0xDF
#define CFO2_KEY11 0xE0
#define CFO2_KEY12 0xE1
#define CFO2_KEY13 0xE2
#define CFO2_KEY14 0xE3
#define CFO2_KEY15 0xE4
#define CFO2_KEY16 0xE5
#define CFO2_KEY17 0xE6
#define CFO2_KEY18 0xE7
#define CFO2_KEY19 0xE8
#define CFO2_KEY20 0xE9
#define CFO2_KEY21 0xEA
#define CFO2_KEY22 0xEB
#define CFO2_KEY23 0xEC

// Misc.
#define NRD 0xED
#define SLEEP_MSYNC_NHYST_DEBUG 0xEE
#define AWAKE 0xEF
#define DHT 0xF0
#define SSYNC_PDRIFT 0xF1
#define LSL_MSB 0xF2
#define KGTT_LSL_LSB 0xF3
#define DWELL_RIB_THRM_FHM 0xF4
#define FREQ0 0xF5
#define FREQ1 0xF6
#define FREQ2 0xF7
#define NSTHR_NIL 0xF8
#define CRC_MSB 0xF9
#define CRC_LSB 0xFA

// ==============================================================================
// IC CLASS FUNCTIONS
// ==============================================================================

class AT42QT1244
{
private:
    uint8_t address;

public:
    // Constructor
    AT42QT1244(int address);

    // Destructor
    ~AT42QT1244();
};