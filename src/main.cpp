// Main file for the Speaker project.
// Includes
#include <iostream>
#include "I2C/I2C.hpp"
#include "I2C/Devices/DS1882/DS1882.hpp"
#include "I2C/Devices/AT42QT1070/AT42QT1070.hpp"
#include "I2C/Devices/MCP9808/MCP9808.hpp"
#include "I2C/Devices/PCM5252/PCM5252.hpp"
#include "I2C/Devices/ADS1015/ADS1015.hpp"
#include "I2C/Devices/MCP45HV51/MCP45HV51.hpp"

// entry point
int main(int argc, char *argv[])
{
    std::cout << "Hello World !" << std::endl;

    DS1882 POTI0 = DS1882(LOG_POTI_0);
    POTI0.ReadWiper(WIPER_0);

    return 0;
}