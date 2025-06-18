# ========================================================================================
# SPI
# ========================================================================================
# Add sources
set(SPI_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/spi.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(spi ${SPI_SOURCES})