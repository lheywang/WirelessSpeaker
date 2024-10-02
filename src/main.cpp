/**
 * @file main.cpp
 * @author l.heywang (leonard.heywang@gmail.com)
 * @brief Entry point for the global software.
 * @version 0.1
 * @date 2024-10-02
 *
 * @copyright Copyright (c) 2024
 *
 */

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

    PCA9633 LED0 = PCA9633(I2C, 0x62);
    int buf[4] = {63, 127, 195, 255};

    std::cout << LED0.Configure(0, 1, 1, 1, 1, 1, 1, 1, 1, LED_ON) << std::endl;
    std::cout << LED0.SetLedStatus(LED_PWM, LED_PWM_GLOB, LED_ON, LED_OFF) << std::endl;
    std::cout << LED0.ConfigureDutyCycle(CHANNEL0, buf, 4) << std::endl;
    // std::cout << LED0.ConfigureGlobalDimming(50, 127) << std::endl;
    // std::cout << LED0.ConfigureSubAddress(SUBADDR1, 0x50) << std::endl;

    /* MCP 9808
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

    /* AT42QT1070
     *
     *  AT42QT1070 TOUCH0 = AT42QT1070(I2C);
     *
     *  int Firmware;
     *  int ID;
     *
     *  TOUCH0.GetIDs(&ID, &Firmware);
     *  std::cout << ID << " | " << Firmware << std::endl;
     *
     *  std::cout << TOUCH0.SetReferenceThreshold(NEGATIVE_THRESHOLD_KEY_0, 127) << std::endl;
     *  std::cout << TOUCH0.SetAdjacentKeySuppresion(ADJACENT_SUPPRESSION_LEVEL_KEY_0, 127) << std::endl;
     *  std::cout << TOUCH0.SetDetectionIntegrator(DETECTION_INTEGRATOR_COUNTER_KEY_0, 6) << std::endl;
     *
     *  int buf;
     *  TOUCH0.GetKeyReferenceSignal(REFERENCE_DATA_0, &buf);
     *  std::cout << buf << std::endl;
     *  TOUCH0.GetReferenceThreshold(NEGATIVE_THRESHOLD_KEY_0, &buf);
     *  std::cout << buf << std::endl;
     *  TOUCH0.GetAdjacentKeySuppresion(ADJACENT_SUPPRESSION_LEVEL_KEY_0, &buf);
     *  std::cout << buf << std::endl;
     *  TOUCH0.GetDetectionIntegrator(DETECTION_INTEGRATOR_COUNTER_KEY_0, &buf);
     *  std::cout << buf << std::endl;
     *
     *  int Calibration = 0;
     *  int Overflow = 0;
     *  int Touch = 0;
     *  int Keys = 0;
     *
     *  for (int i = 0; i < 20; i++)
     *  {
     *      TOUCH0.GetKeysStatus(&Calibration, &Overflow, &Touch, &Keys);
     *
     *      std::cout << "__________________________________________________________________" << std::endl;
     *      std::cout << "| KEY 7  | KEY 6 | KEY 5 | KEY 4 | KEY 3 | KEY 2 | KEY 1 | KEY 0 |" << std::endl;
     *      std::cout << "|   " << ((Keys & 0x80) >> 7) << "   |   " << ((Keys & 0x40) >> 6) << "   |   " << ((Keys & 0x20) >> 5) << "   |   " << ((Keys & 0x00) >> 4) << "   |   " << ((Keys & 0x08) >> 3) << "   |   " << ((Keys & 0x04) >> 2) << "   |   " << ((Keys & 0x02) >> 1) << "   |   " << (Keys & 0x01) << "    |" << std::endl;
     *
     *      usleep(500'000);
     *   }
     * }

     */

    return 0;
}