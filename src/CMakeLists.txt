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

# Devices drivers
set(DeviceDrivers   ${CMAKE_SOURCE_DIR}/Drivers/Devices/ADS1015/ADS1015.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/AT42QT1070/AT42QT1070.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/DS1882/DS1882.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/INA219/INA219.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/MCP45HV51/MCP45HV51.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/MCP9808/MCP9808.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/MCP23009/MCP23009.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/PCA9633/PCA9633.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/PCM5252/PCM5252.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/STUBS4500/STUSB4500.cpp\\
                    ${CMAKE_SOURCE_DIR}/Drivers/Devices/M95256/M95256.cpp)
                    

# BCM peripheral drivers
set(PeripheralDrivers   ${CMAKE_SOURCE_DIR}/Drivers/I2C/I2C_Engine.cpp\\
                        ${CMAKE_SOURCE_DIR}/Drivers/GPIO/GPIO.cpp\\
                        ${CMAKE_SOURCE_DIR}/Drivers/SPI/SPI_Engine.cpp\\
                        ${CMAKE_SOURCE_DIR}/Drivers/UART/UART.cpp\\
                        ${CMAKE_SOURCE_DIR}/Drivers/USB/USB.cpp)

# External libraries includes                       
set(ExternalIncludes    ${CMAKE_SOURCE_DIR}/Drivers/GPIO/includes/clk.cpp\\
                        ${CMAKE_SOURCE_DIR}/Drivers/I2C/includes/smbus.cpp\\
                        ${CMAKE_SOURCE_DIR}/Modules/libcrc/crc8.c\\
                        ${CMAKE_SOURCE_DIR}/Modules/libcrc/crc16.c\\
                        ${CMAKE_SOURCE_DIR}/Modules/libcrc/crc32.c\\
                        ${CMAKE_SOURCE_DIR}/Modules/libcrc/crc64.c\\
                        ${CMAKE_SOURCE_DIR}/Modules/libcrc/crcccitt.c\\
                        ${CMAKE_SOURCE_DIR}/Modules/libcrc/crckrmit.c\\
                        ${CMAKE_SOURCE_DIR}/Modules/libcrc/crcsick.c\\
                        ${CMAKE_SOURCE_DIR}/Modules/libcrc/nmea-chk.c)

# Modules 
set(Modules ${CMAKE_SOURCE_DIR}/Modules/EEPROM/eeprom.cpp\\
            ${CMAKE_SOURCE_DIR}/Modules/EEPROM/dsp_profile/dsp_profile.cpp)

# Internal libraries
set(LIBS    ${CMAKE_BINARY_DIR}/bin/config.o\\
            ${CMAKE_BINARY_DIR}/bin/header.o)

# ========================================================================================
# CMAKES SETTINGS
# ========================================================================================
set(CMAKE_SYSTEM_PROCESSOR aarch64)
set(CMAKE_C_COMPILER /usr/bin/aarch64-linux-gnu-gcc)
set(CMAKE_CXX_COMPILER /usr/bin/aarch64-linux-gnu-g++)

# ========================================================================================
# COMPILERS SETTINGS
# ========================================================================================
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-a53 -O3 -MMD -Wall -Wextra ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=cortex-a53 -O3 -std=c++20 -MMD -Wall -Wextra ")

# Comment to disable debug
add_compile_options(-g)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# ========================================================================================
# EXECUTABLES
# ========================================================================================
add_executable(${AppName} main.cpp ${DeviceDrivers} ${PeripheralDrivers} ${Modules} ${ExternalIncludes} ${LIBS})