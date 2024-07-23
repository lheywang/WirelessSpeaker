// ==============================================================================
//                              I2C/Devices/TLA2528/TLA2528.hpp
//                              Wrote by lheywang
//
// Define functions to interface with the IC
// ==============================================================================

// prevent multiple include
#pragma once

// type include
#include <cstdint>

// ==============================================================================
// IC REGISTER ADDRESSES
// ==============================================================================
#define TLA2528_DATA_SIZE 8 // 8b register here

// Registers
#define SYSTEM_STATUS 0x00
#define GENERAL_CFG 0x01
#define DATA_CFG 0x02
#define OSR_CFG 0x03
#define OPMODE_CFG 0x04
#define PIN_CFG 0x05
#define GPIO_CFG 0x07
#define GPO_VALUE 0x0B
#define GPI_VALUE 0x0D
#define SEQUENCE_CFG 0x10
#define CHANNEL_SEL 0x11
#define AUTO_SEQ_CH_SEL 0x12

// Channels codes
#define CHANNEL_0 0x00
#define CHANNEL_1 0x01
#define CHANNEL_2 0x02
#define CHANNEL_3 0x03
#define CHANNEL_4 0x04
#define CHANNEL_5 0x05
#define CHANNEL_6 0x06
#define CHANNEL_7 0x07

// ==============================================================================
// IC CLASS FUNCTIONS
// ==============================================================================

class TLA2528
{
private:
    uint8_t address;

public:
    // constructors
    TLA2528(int address);

    // destructors
    ~TLA2528();

    // Standard functions
    double ReadAnalogValue();
    int SelectChannel(int Channel);
};