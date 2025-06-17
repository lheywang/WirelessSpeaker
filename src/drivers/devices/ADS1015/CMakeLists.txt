# ========================================================================================
# ADS1015
# ========================================================================================
# Add sources
set(ADS1015_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/ADS1015.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(ads1015 ${ADS1015_SOURCES})

# Make the current directory and its 'includes' subdirectories available
target_link_libraries(ads1015 PUBLIC i2c)