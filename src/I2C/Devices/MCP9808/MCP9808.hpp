// ==============================================================================
//                              I2C/Devices/MCP9808/MCP9808.hpp
//                              Wrote by lheywang
//
// Define functions to interface with the IC
// ==============================================================================

// Only included one time
#pragma once

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

#define     MCP9808_DATA_SIZE      16 // 16b register here
#define     MCP9808_CONFIG         0x01
#define     UPPER_TEMP             0x02
#define     LOWER_TEMP             0x03
#define     CRIT_TEMP              0x04
#define     READ_TEMP              0x05
#define     MANUFACTURER           0x06

// ==============================================================================
// IC STANDARD FUNCTIONS
// ==============================================================================