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

#include "drivers/peripherals/gpio.hpp"
#include "drivers/peripherals/i2c.hpp"
#include "drivers/peripherals/spi.hpp"
#include "drivers/peripherals/uart.hpp"

#include "modules/eeprom/eeprom.hpp"

#include "drivers/devices/MCP9808.hpp"

#include <ctime>

// entry point
int main()
{

    /*

    Ideas :
    --> Initialization with async task since IO bounds.
        - One first task to start all software only initializations.
        - in // a task that run to configure statically defined components
        - In // an EEPROM read task and parse
        - Then we write to the IC the user defined values
        - Wait for write
        - Wait for software initialize
        - Lanch the threads that execute :
            - Device management
            - Audio playback
            - ...
     */

    // std::cout << "Hello World !" << std::endl;

    // SPI_Bus* SPI = SPI_GetInfos(SPI_SLAVES::DAC);
    // SPI_Configure(SPI, SPI_MODE_0, SPI_DEFAULT_WORDSIZE, 1000000);

    // int buf[4] = {0};
    // int res = 0;

    // buf[0] = 0x2A << 1 | 0; // Read to register 0x2A --> Shall return 0x11
    // buf[1] = 0xAA;
    // res = SPI_Transfer(SPI, buf, buf, 2);

    // buf[0] = 0x2A << 1 | 1; // Read to register 0x2A --> Shall return 0x11
    // buf[1] = 0;
    // res = SPI_Transfer(SPI, buf, buf, 4);

    // if(res != 0)
    //     return -1;

    // EEPROM Mem = EEPROM();

    // char Name[MAX_PROFILE_CHAR] = {0};
    // Name[0] = 'T';
    // Name[1] = 'H';
    // Name[2] = 'I';
    // Name[3] = 'S';
    // Name[4] = ' ';
    // Name[5] = 'I';
    // Name[6] = 'S';
    // Name[7] = ' ';
    // Name[8] = 'A';
    // Name[9] = ' ';
    // Name[10] = 'T';
    // Name[11] = 'E';
    // Name[12] = 'S';
    // Name[13] = 'T';
    // Name[14] = ' ';
    // Name[15] = 'F';
    // Name[16] = 'O';
    // Name[17] = 'R';
    // Name[18] = ' ';
    // Name[20] = 'W';
    // Name[21] = 'I';
    // Name[22] = 'R';
    // Name[23] = 'E';
    // Name[24] = 'L';
    // Name[25] = 'E';
    // Name[26] = 'S';
    // Name[27] = 'S';
    // Name[28] = ' ';
    // Name[29] = 'Y';
    // DSP_PROFILE Profile = DSP_PROFILE(Name, DSP_PROFILE_SIZE::LARGE);
    // float buf[256] = {0};
    // for (int i = 0; i < 256; i++)
    //     buf[i] = std::rand() % 3;
    // int instr[1024] = {0};
    // for (int i = 0; i < 1024; i++)
    //     buf[i] = std::rand();
    // Profile.WriteBufferA(buf, 256);
    // Profile.WriteBufferB(buf, 256);
    // Profile.WriteInstructions(instr, 1024);

    // uint8_t t[256 * 3] = {0};
    // int ret = Profile.ReturnBufferAValues(t);
    // std::cout << "ReturnName - func : " << ret << std::endl;
    // for (int i = 0; i < 256 * 3; i++)
    //     std::cout << std::hex << (int)t[i];
    // std::cout << std::endl;

    // int ID = 0;

    // ret = Mem.AddDSPProfile(&Profile, &ID);
    // std::cout << "AddDSPProfile - func : " << ret << std::endl;

    // DSP_PROFILE_SIZE Profile2;
    // Mem.GetDSPProfileSize(ID, &Profile2);

    // std::cout << (int)Profile2 << std::endl;

    // if (ret < 0)
    // {
    //     for (int i = 0; i < 8; i++)
    //         Mem.RemoveDSPProfile(i);
    // }

    // for (int i = 0; i < MAX_PROFILE_CHAR; i++)
    //     std::cout << t[i];
    // std::cout << std::endl;

    // for (int i = 0; i < 8; i++)
    //     Mem.RemoveDSPProfile(i);

    // std::cout << Mem.WriteConfigV1(&Config) << std::endl;
    // usleep(10000);
    // std::cout << Mem.ReadConfigV1(&Config) << std::endl;

    // int TX[100] = {0};
    // int RX[100] = {0};

    // std::cout << EEPROM.WriteStatus(0, EEPROM_WP::SOFT_WP_DISABLED) << std::endl;

    // int WriteProtec = 0,
    //     WriteEnable = 0,
    //     WriteStatus = 0;
    // EEPROM_WP WP;
    // EEPROM.ReadStatus(&WriteProtec, &WP, &WriteEnable, &WriteStatus);

    // std::cout << WriteProtec << " - " << WriteEnable << " - " << WriteStatus << " - " << (int)WP << std::endl;

    // for (int i = 0; i < 100; i++)
    //     TX[i] = i;

    // EEPROM.Write(0x0088, TX, 50);
    // EEPROM.Read(0x0088, RX, 50);

    // for (int i = 0; i < 50; i++)
    //     std::cout << TX[i] << "-";
    // std::cout << std::endl;

    // for (int i = 0; i < 50; i++)
    //     std::cout << RX[i] << "-";
    // std::cout << std::endl;

    // SPI_Close(SPI);

    // TX[0] = 0x06;
    // SPI_Transfer(SPI, TX, RX, 1);

    // std::cin >> buf;

    // TX[0] = 0x02;
    // TX[1] = 0x88;
    // TX[2] = 0x88;
    // TX[3] = 0x55;
    // TX[4] = 0x55;
    // TX[5] = 0x55;
    // TX[6] = 0x55;
    // SPI_Transfer(SPI, TX, RX, 25);
    // for (int i = 0; i < 25; i++)
    //     std::cout << TX[i] << "-";
    // std::cout << std::endl;
    // for (int i = 0; i < 25; i++)
    //     std::cout << RX[i] << "-";
    // std::cout << std::endl;

    // TX[0] = 0x05;
    // TX[1] = 0x00;
    // TX[2] = 0x00;
    // TX[3] = 0x00;
    // TX[4] = 0x00;
    // TX[5] = 0x00;
    // TX[6] = 0x00;
    // SPI_Transfer(SPI, TX, RX, 5);
    // for (int i = 0; i < 5; i++)
    //     std::cout << TX[i] << "-";
    // std::cout << std::endl;
    // for (int i = 0; i < 5; i++)
    //     std::cout << RX[i] << "-";
    // std::cout << std::endl;

    // std::cin >> buf;

    // TX[0] = 0x03;
    // TX[1] = 0x88;
    // TX[2] = 0x88;
    // TX[3] = 0x00;
    // TX[4] = 0x00;
    // TX[5] = 0x00;
    // TX[6] = 0x00;
    // SPI_Transfer(SPI, TX, RX, 25);
    // std::cin >> buf;
    // for (int i = 0; i < 25; i++)
    //     std::cout << TX[i] << "-";
    // std::cout << std::endl;
    // for (int i = 0; i < 25; i++)
    //     std::cout << RX[i] << "-";
    // std::cout << std::endl;

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

    /* GPIO
     *  struct gpiochip_info info;
     *  GetGPIOChipInfos(&info);
     *
     *  std::cout << info.label << std::endl;
     *
     *  struct GPIO GPIO;
     *  GPIO.PinNumber = 16;
     *  GetGPIOInfo(&GPIO);
     *
     *  std::cout << GPIO.Name << std::endl;
     *  std::cout << GPIO.InOut << std::endl;
     *  std::cout << GPIO.Polarity << std::endl;
     *  std::cout << GPIO.Type << std::endl;
     *  std::cout << GPIO.Kernel << std::endl;
     *
     *  int Status = 0;
     *  ReadGPIO(&GPIO, &Status);
     *  std::cout << Status << std::endl;
     *
     *  WriteGPIO(&GPIO, 1);
     */

    /* PCA9633
     *
     * PCA9633 LED0 = PCA9633(I2C, 0x62);
     * int buf[4] = {63, 127, 195, 255};
     *
     * std::cout << LED0.Configure(0, 1, 1, 1, 1, 1, 1, 1, 1, LED_ON) << std::endl;
     * std::cout << LED0.SetLedStatus(LED_PWM, LED_PWM_GLOB, LED_ON, LED_OFF) << std::endl;
     * std::cout << LED0.ConfigureDutyCycle(CHANNEL0, buf, 4) << std::endl;
     *
     */

    /*
     * MCP23009 GPIO0 = MCP23009(I2C, 0x20);
     *
     * int Inputs = 0;
     * int Port = 0;
     *
     * std::cout << GPIO0.ReadInputs(&Inputs) << std::endl;
     * std::cout << Inputs << std::endl;
     *
     * std::cout << GPIO0.Configure(1, 1) << std::endl;
     * std::cout << GPIO0.ConfigureGPIO(0x1F, 0x00, 0x00, 0x00, 0x00, 0x00) << std::endl;
     * std::cout << GPIO0.SetOutputs(0x00) << std::endl; // Inverted logic, set to 0 !
     * std::cout << GPIO0.ReadInterrupts(&Inputs, &Port) << std::endl; // To check hardware principle. Driver OK !
     * std::cout << Inputs << " | " << Port << std::endl;
     */

    /*
     * PCA9633 LED0 = PCA9633(I2C, 0x61);
     *
     * int buf[4] = {200, 150, 100, 50};
     * std::cout << LED0.Configure(1, 0, 0, 0, 0, 1, 0, 0, 0, LED_OFF) << std::endl;
     * std::cout << LED0.SetLedStatus(LED_PWM_GLOB, LED_PWM_GLOB, LED_PWM_GLOB, LED_PWM_GLOB) << std::endl;
     * std::cout << LED0.ConfigureDutyCycle(CHANNEL0, buf, 4) << std::endl;
     * std::cout << LED0.ConfigureGlobalDimming(50, 128) << std::endl; // A bit confusing to use, but OK !
     * std::cout << LED0.ConfigureSubAddress(ADDRESS1, 0x50) << std::endl; // OK
     */

    /* GPCLK0
     *
     * initClock(2, 18, 0, 0); // Output a 12 MHz square.
     * usleep(3'000'000);
     * termClock();
     */

    /*
     * ADS1015 ADC = ADS1015(I2C, 0x48);
     * ADC.Configure_ADC(0, ADC_CHANNEL_3, ADC_GAIN_4V00, 1, ADC_SPS_3300, 0, 1, 0, 0);
     *
     * float value = 0;
     * ADC.Read_Voltage(ADC_CHANNEL_0, &value);
     * std::cout << value << std::endl;
     * ADC.Read_Voltage(ADC_CHANNEL_1, &value);
     * std::cout << value << std::endl;
     * ADC.Read_Voltage(ADC_CHANNEL_2, &value);
     * std::cout << value << std::endl;
     * ADC.Read_Voltage(ADC_CHANNEL_3, &value);
     * std::cout << value << std::endl;
     *
     * // Devboard values !
     * // AIN 0 : 3.17 V
     * // AIN 1 : 0.110
     * // AIN 2 : 2.487 V
     * // AIN 3 : 0.816 V
     *
     */

    /*
     * UART_Bus *Serial = UART_GetInfos(0);
     * UART_Configure(Serial, UART_PARITY::OFF, UART_STOP::ONE, UART_DATA_WIDTH::EIGHT, UART_CTRL::NONE, UART_BAUD::BD_115K2);
     *
     * char buf[] = "Hello World \n";
     * UART_Write(Serial, buf, sizeof(buf));
     * UART_Read(Serial, buf, 10);
     * for (int i = 0; i < 10; i++)
     *     std::cout << buf[i];
     * std::cout << std::endl;
     * UART_Close(Serial);
     *
     */

    return 0;
}