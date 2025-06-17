# ========================================================================================
# SPI
# ========================================================================================
# Add sources
set(UART_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/uart.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(uart ${UART_SOURCES})