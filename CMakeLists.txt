# ========================================================================================
# PROJECT OPTIONS
# ========================================================================================
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project($ENV{NAME})

# ========================================================================================
# FILES LISTS
# ========================================================================================
# Adding headers files
include_directories(inc/)

# Add files here, following the actual scheme.
# If you add a new functionnality, don't hesitate to add a new variable !

# Devices drivers
set(DeviceDrivers   ${CMAKE_SOURCE_DIR}/src/drivers/devices/ADS1015/ADS1015.cpp\\
                    ${CMAKE_SOURCE_DIR}/src/drivers/devices/AT42QT1070/AT42QT1070.cpp\\
                    ${CMAKE_SOURCE_DIR}/src/drivers/devices/DS1882/DS1882.cpp\\
                    ${CMAKE_SOURCE_DIR}/src/drivers/devices/INA219/INA219.cpp\\
                    ${CMAKE_SOURCE_DIR}/src/drivers/devices/MCP45HV51/MCP45HV51.cpp\\
                    ${CMAKE_SOURCE_DIR}/src/drivers/devices/MCP9808/MCP9808.cpp\\
                    ${CMAKE_SOURCE_DIR}/src/drivers/devices/MCP23009/MCP23009.cpp\\
                    ${CMAKE_SOURCE_DIR}/src/drivers/devices/PCA9633/PCA9633.cpp\\
                    ${CMAKE_SOURCE_DIR}/src/drivers/devices/PCM5252/PCM5252.cpp\\
                    ${CMAKE_SOURCE_DIR}/src/drivers/devices/STUBS4500/STUSB4500.cpp\\
                    ${CMAKE_SOURCE_DIR}/src/drivers/devices/M95256/M95256.cpp)
                    

# BCM peripheral drivers
set(PeripheralDrivers   ${CMAKE_SOURCE_DIR}/src/drivers/i2c/I2C_Engine.cpp\\
                        ${CMAKE_SOURCE_DIR}/src/drivers/gpio/GPIO.cpp\\
                        ${CMAKE_SOURCE_DIR}/src/drivers/spi/SPI_Engine.cpp\\
                        ${CMAKE_SOURCE_DIR}/src/drivers/uart/UART.cpp\\
                        ${CMAKE_SOURCE_DIR}/src/drivers/usb/USB.cpp)

# External libraries includes                       
set(ExternalIncludes    ${CMAKE_SOURCE_DIR}/src/drivers/gpio/includes/clk.cpp\\
                        ${CMAKE_SOURCE_DIR}/src/drivers/i2c/includes/smbus.cpp\\
                        ${CMAKE_SOURCE_DIR}/src/modules/libcrc/crc8.c\\
                        ${CMAKE_SOURCE_DIR}/src/modules/libcrc/crc16.c\\
                        ${CMAKE_SOURCE_DIR}/src/modules/libcrc/crc32.c\\
                        ${CMAKE_SOURCE_DIR}/src/modules/libcrc/crc64.c\\
                        ${CMAKE_SOURCE_DIR}/src/modules/libcrc/crcccitt.c\\
                        ${CMAKE_SOURCE_DIR}/src/modules/libcrc/crckrmit.c\\
                        ${CMAKE_SOURCE_DIR}/src/modules/libcrc/crcsick.c\\
                        ${CMAKE_SOURCE_DIR}/src/modules/libcrc/nmea-chk.c)

# Modules 
set(Modules ${CMAKE_SOURCE_DIR}/src/modules/eeprom/eeprom.cpp\\
            ${CMAKE_SOURCE_DIR}/src/modules/eeprom/dsp_profile/dsp_profile.cpp)

# Internal libraries
set(LIBS    ${CMAKE_BINARY_DIR}/bin/config.o\\
            ${CMAKE_BINARY_DIR}/bin/header.o)

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
add_executable($ENV{APPNAME} src/main.cpp ${DeviceDrivers} ${PeripheralDrivers} ${Modules} ${ExternalIncludes} ${LIBS})