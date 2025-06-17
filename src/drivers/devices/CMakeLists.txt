# ========================================================================================
# DEVICES
# ========================================================================================
# Add sources
set(DEVICES_SOURCES     ${CMAKE_CURRENT_SOURCE_DIR}/ADS1015/ADS1015.cpp\\
                        ${CMAKE_CURRENT_SOURCE_DIR}/AT42QT1070/AT42QT1070.cpp\\
                        ${CMAKE_CURRENT_SOURCE_DIR}/DS1882/DS1882.cpp\\
                        ${CMAKE_CURRENT_SOURCE_DIR}/INA219/INA219.cpp\\
                        ${CMAKE_CURRENT_SOURCE_DIR}/MCP45HV51/MCP45HV51.cpp\\
                        ${CMAKE_CURRENT_SOURCE_DIR}/MCP9808/MCP9808.cpp\\
                        ${CMAKE_CURRENT_SOURCE_DIR}/MCP23009/MCP23009.cpp\\
                        ${CMAKE_CURRENT_SOURCE_DIR}/PCA9633/PCA9633.cpp\\
                        ${CMAKE_CURRENT_SOURCE_DIR}/PCM5252/PCM5252.cpp\\
                        ${CMAKE_CURRENT_SOURCE_DIR}/STUBS4500/STUSB4500.cpp\\
                        ${CMAKE_CURRENT_SOURCE_DIR}/M95256/M95256.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(devices ${DEVICES_SOURCES})

# Make the current directory and its 'includes' subdirectories available
target_link_libraries(devices PUBLIC peripherals)