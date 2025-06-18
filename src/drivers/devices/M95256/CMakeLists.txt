# ========================================================================================
# M95256
# ========================================================================================
# Add sources
set(M95256_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/M95256.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(m95256 ${M95256_SOURCES})

# Make the current directory and its 'includes' subdirectories available
target_link_libraries(m95256 PUBLIC spi)