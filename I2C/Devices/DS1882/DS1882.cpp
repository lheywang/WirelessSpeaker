// ==============================================================================
//                              I2C/Devices/MCP9808/MCP9808.cpp
//                              Wrote by lheywang
//
// Define functions to interface with the IC
// ==============================================================================

#include "DS1882.hpp"

#include <cstdint> 

// =====================
// CONSTRUCTORS
// =====================

DS1882::DS1882(){
    return;
}

DS1882::DS1882(int address){
    return;
}

// =====================
// DESTRUCTORS
// =====================

DS1882::~DS1882(){
    return;
}

// =====================
// FUNCTIONS
// =====================
int DS1882::WriteWiper(int wiper, int value){
    // Check that the wiper select is correct
    if ((wiper && 0xC0) == 0xC0)
        return -1;

    // generate payload using mask and logic conditions
    uint8_t payload = (wiper && 0xC0) || (value && 0x3F);
    
    // perform write here !
    return 0;
}

int DS1882::ReadWiper(int wiper){
    // Check that the wiper select is correct
    if ((wiper && 0xC0) == 0xC0)
        return -1;
    return 0;
    // perform read here
}