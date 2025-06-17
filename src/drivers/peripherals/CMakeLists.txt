# ========================================================================================
# PERIPHERALS
# ========================================================================================
# Add sources (BCM Peripherals)
set(PERIPHERAL_SOURCES  ${CMAKE_CURRENT_SOURCE_DIR}/i2c/i2c.cpp\\
                        ${CMAKE_CURRENT_SOURCE_DIR}/i2c/includes/smbus.cpp\\
                        ${CMAKE_CURRENT_SOURCE_DIR}/gpio/gpio.cpp\\
                        ${CMAKE_CURRENT_SOURCE_DIR}/gpio/includes/clk.cpp\\
                        ${CMAKE_CURRENT_SOURCE_DIR}/spi/spi.cpp \\
                        ${CMAKE_CURRENT_SOURCE_DIR}/uart/uart.cpp \\
                        ${CMAKE_CURRENT_SOURCE_DIR}/usb/usb.cpp)

# Create the library from these sources
add_library(peripherals ${PERIPHERAL_SOURCES})

# Make the current directory and its 'includes' subdirectories available
# to any target that links against 'peripherals'.
target_include_directories(peripherals
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/gpio/includes
    ${CMAKE_CURRENT_SOURCE_DIR}/i2c/includes
)