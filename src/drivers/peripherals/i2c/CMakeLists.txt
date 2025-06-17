# ========================================================================================
# I2C
# ========================================================================================
# Add sources
set(I2C_SOURCES     ${CMAKE_CURRENT_SOURCE_DIR}/i2c.cpp \\
                    ${CMAKE_CURRENT_SOURCE_DIR}/includes/smbus.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(i2c ${I2C_SOURCES})