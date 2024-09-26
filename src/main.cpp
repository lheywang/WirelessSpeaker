// Main file for the Speaker project.
// Includes
#include <iostream>
#include "Drivers/I2C/I2C.hpp"
#include "Drivers/Devices/DS1882/DS1882.hpp"
#include "Drivers/Devices/AT42QT1070/AT42QT1070.hpp"
#include "Drivers/Devices/MCP9808/MCP9808.hpp"
#include "Drivers/Devices/PCM5252/PCM5252.hpp"
#include "Drivers/Devices/ADS1015/ADS1015.hpp"
#include "Drivers/Devices/MCP45HV51/MCP45HV51.hpp"
#include "Drivers/Devices/PCA9633/PCA9633.hpp"
#include "Drivers/SPI/SPI.hpp"
#include "Drivers/I2C/I2C_Engine.hpp"

// entry point
int main(int argc, char *argv[])
{
    std::cout << "Hello World !" << std::endl;

    DS1882 POTI0 = DS1882(LOG_POTI_0);
    POTI0.ReadWiper(WIPER_0);

    return 0;
}