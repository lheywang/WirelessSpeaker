# ========================================================================================
# STUSB4500
# ========================================================================================
# Add sources
set(STUSB4500_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/STUSB4500.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(stusb4500 ${STUSB4500_SOURCES})

# Make the current directory and its 'includes' subdirectories available
target_link_libraries(stusb4500 PUBLIC i2c)