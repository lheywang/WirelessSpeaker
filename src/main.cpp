// Main file for the Speaker project.
// Includes
#include <iostream>
#include <unistd.h>

#include "Drivers/I2C/I2C.hpp"
#include "Drivers/Devices/DS1882/DS1882.hpp"
#include "Drivers/Devices/AT42QT1070/AT42QT1070.hpp"
#include "Drivers/Devices/MCP9808/MCP9808.hpp"
#include "Drivers/Devices/PCM5252/PCM5252.hpp"
#include "Drivers/Devices/ADS1015/ADS1015.hpp"
#include "Drivers/Devices/MCP45HV51/MCP45HV51.hpp"
#include "Drivers/Devices/PCA9633/PCA9633.hpp"
#include "Drivers/SPI/SPI.hpp"

// entry point
int main()
{
    std::cout << "Hello World !" << std::endl;

    I2C_Bus *I2C = I2C_GetInfos();

    AT42QT1070 TOUCH0 = AT42QT1070(I2C);

    int Calibration = 0;
    int Overflow = 0;
    int Touch = 0;
    int Keys = 0;

    for (int i = 0; i < 10; i++)
    {
        std::cout << TOUCH0.GetKeysStatus(&Calibration, &Overflow, &Touch, &Keys) << std::endl;
        std::cout << Calibration << std::endl;
        std::cout << Overflow << std::endl;
        std::cout << Touch << std::endl;
        std::cout << std::hex << Keys << std::endl;

        usleep(500'000);
    }

    /*
     *
     *  MCP9808 TEMP0 = MCP9808(I2C, 0x1a);
     *
     *  std::cout << TEMP0.SetAlertTemperatures(-12.8256, 32.2589, 35.4736) << std::endl;
     *
     *  std::cout << TEMP0.SetAlertTemperatures(-12.8256, 32.2589, 35.4736) << std::endl;
     *
     *  float Temperature;
     *  int Status;
     *
     *  std::cout << TEMP0.ReadTemperature(&Temperature, &Status) << std::endl;
     *  std::cout << Temperature << " | " << Status << std::endl;
     *
     *  std::cout << TEMP0.ConfigureResolution(C0_0625) << std::endl; // OK
     *
     *  int DeviceID;
     *  int ManufacterID;
     *  int DeviceRevision;
     *
     *  std::cout << TEMP0.GetIDs(&DeviceID, &DeviceRevision, &ManufacterID) << std::endl;      // OK
     *  std::cout << DeviceID << " | " << ManufacterID << " | " << DeviceRevision << std::endl; // OK
     */

    return 0;
}