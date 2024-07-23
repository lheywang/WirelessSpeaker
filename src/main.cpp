// Main file for the Speaker project.
// Includes
#include <iostream>
#include "I2C/Addresses.hpp"
#include "I2C/Devices/DS1882/DS1882.hpp"
#include "I2C/Devices/AT42QT1244/AT42QT1244.hpp"
#include "I2C/Devices/MCP9808/MCP9808.hpp"
#include "I2C/Devices/PCM5252/PCM5252.hpp"
#include "I2C/Devices/TLA2528/TLA2528.hpp"


// entry point
int main(int argc, char* argv[])
{
    std::cout << "Hello World !" << std::endl;

    DS1882 POTI0 = DS1882(POTI_0);
    POTI0.ReadWiper(WIPER_0);

    return 0;
}