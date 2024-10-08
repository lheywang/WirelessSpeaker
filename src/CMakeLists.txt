# ========================================================================================
# PROJECT OPTION
# ========================================================================================
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project("Wireless Speaker")
set(AppName "WirelessSpeaker.arm")

# ========================================================================================
# FILES LISTS
# ========================================================================================
# Add files here, following the actual scheme.
# If you add a new functionnality, don't hesitate to add a new variable !

set(DeviceDrivers   ${CMAKE_SOURCE_DIR}/Drivers/Devices/ADS1015/ADS1015.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/AT42QT1070/AT42QT1070.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/DS1882/DS1882.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/INA219/INA219.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/MCP45HV51/MCP45HV51.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/MCP9808/MCP9808.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/MCP23009/MCP23009.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/PCA9633/PCA9633.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/PCM5252/PCM5252.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/STUBS4500/STUSB4500.cpp)
                    

set(PeripheralDrivers   ${CMAKE_SOURCE_DIR}/Drivers/I2C/includes/smbus.cpp\\
                        ${CMAKE_SOURCE_DIR}/Drivers/I2C/I2C_Engine.cpp\\
                        ${CMAKE_SOURCE_DIR}/Drivers/GPIO/GPIO_Engine.cpp\\
                        ${CMAKE_SOURCE_DIR}/Drivers/SPI/SPI_Engine.cpp)

# ========================================================================================
# CMAKES SETTINGS
# ========================================================================================
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++)

# ========================================================================================
# COMPILERS SETTINGS
# ========================================================================================
add_compile_options(-mcpu=cortex-a53 -O3 -MMD -std=c++20 -Wall -Wextra)

# ========================================================================================
# EXECUTABLES
# ========================================================================================
add_executable(${AppName} main.cpp ${DeviceDrivers} ${PeripheralDrivers})
