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