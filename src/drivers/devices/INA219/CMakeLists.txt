# ========================================================================================
# INA219
# ========================================================================================
# Add sources
set(INA219_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/INA219.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(ina219 ${INA219_SOURCES})

# Make the current directory and its 'includes' subdirectories available
target_link_libraries(ina219 PUBLIC i2c)