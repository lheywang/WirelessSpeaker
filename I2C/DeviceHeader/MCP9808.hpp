// ==============================================================================
//                              I2C/DeviceHeader/MCP9808.hpp
//                              Wrote by lheywang
//
// Define our basic I2C settings on the boards, such as : 
// - Register Addresses
// ==============================================================================

// Only included one time
#pragma once

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================

#define     REG_WIDTH       16 // 16b register here
#define     CONFIG          0x01
#define     UPPER_TEMP      0x02
#define     LOWER_TEMP      0x03
#define     CRIT_TEMP       0x04
#define     READ_TEMP       0x05
#define     MANUFACTURER    0x06