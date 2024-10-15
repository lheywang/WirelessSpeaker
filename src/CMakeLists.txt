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
                        ${CMAKE_SOURCE_DIR}/Drivers/I2C/includes/smbus.cpp)

# Modules 
set(Modules ${CMAKE_SOURCE_DIR}/Modules/EEPROM/reader.cpp\\
            ${CMAKE_SOURCE_DIR}/Modules/EEPROM/writter.cpp\\
            ${CMAKE_SOURCE_DIR}/Modules/EEPROM/updater.cpp)

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

# ========================================================================================
# EXECUTABLES
# ========================================================================================
add_executable(${AppName} main.cpp ${DeviceDrivers} ${PeripheralDrivers} ${Modules} ${ExternalIncludes})

# ${CMAKE_SOURCE_DIR}/Drivers/USB/includes/sync.c\\
#                         ${CMAKE_SOURCE_DIR}/Drivers/USB/includes/strerror.c\\
#                         ${CMAKE_SOURCE_DIR}/Drivers/USB/includes/io.c\\
#                         ${CMAKE_SOURCE_DIR}/Drivers/USB/includes/hotplug.c\\
#                         ${CMAKE_SOURCE_DIR}/Drivers/USB/includes/descriptor.c\\
#                         ${CMAKE_SOURCE_DIR}/Drivers/USB/includes/core.c\\
#                         ${CMAKE_SOURCE_DIR}/Drivers/USB/includes/os/linux_netlink.c\\
#                         ${CMAKE_SOURCE_DIR}/Drivers/USB/includes/os/linux_udev.c\\
#                         ${CMAKE_SOURCE_DIR}/Drivers/USB/includes/os/linux_usbfs.c\\
#                         ${CMAKE_SOURCE_DIR}/Drivers/USB/includes/os/threads_posix.c
