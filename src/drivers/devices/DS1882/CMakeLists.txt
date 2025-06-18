# ========================================================================================
# DS1882
# ========================================================================================
# Add sources
set(DS1882_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/DS1882.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(ds1882 ${DS1882_SOURCES})

# Make the current directory and its 'includes' subdirectories available
target_link_libraries(ds1882 PUBLIC i2c)