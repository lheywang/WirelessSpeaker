// ==============================================================================
//                              I2C/I2C.hpp
//                              Wrote by lheywang
//
// Define our basic I2C settings on the boards, such as :
// - Addresses
// - Register adresses
// - Slave numbers
// ==============================================================================

// Only included one time
#pragma once

// ==============================================================================
// I2C PINS
// ==============================================================================

#define SDA 2
#define SCL 3

// ==============================================================================
// IC ADDRESSES
// ==============================================================================

// Define temperature sensor adresses. (MCP9808)
#define TEMPSENSOR_0 0x18
#define TEMPSENSOR_1 0x19
#define TEMPSENSOR_2 0x1A
#define TEMPSENSOR_3 0x1B
#define TEMPSENSOR_4 0x1C
#define TEMPSENSOR_5 0x1D
#define TEMPSENSOR_6 0x1E
#define TEMPSENSOR_7 0x1F

// Digital to Analog Converter
#define DAC_0 0x4C

// Capacitive touch sensors
#define TOUCHSENSOR_0 0x07
#define TOUCHSENSOR_1 0x10 // Not compatible with ADC used for VMON 0
#define TOUCHSENSOR_2 0x39
#define TOUCHSENSOR_3 0x75

// Voltage monitor
#define VMON_0 0x10 // Not compatible with Touch sensor 1
#define VMON_1 0x11
#define VMON_2 0x12
#define VMON_3 0x13
#define VMON_4 0x14
#define VMON_5 0X15
#define VMON_6 0x16
#define VMON_7 0x17

// Logarithmic potentiometer
#define POTI_0 0x28
#define POTI_1 0x29
#define POTI_2 0x2A
#define POTI_3 0x2B
#define POTI_4 0x2C
#define POTI_5 0x2D
#define POTI_6 0x2E
#define POTI_7 0x2F