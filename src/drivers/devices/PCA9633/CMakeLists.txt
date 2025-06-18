# ========================================================================================
# PCA9633
# ========================================================================================
# Add sources
set(PCA9633_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/PCA9633.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(pca9633 ${PCA9633_SOURCES})

# Make the current directory and its 'includes' subdirectories available
target_link_libraries(pca9633 PUBLIC i2c)