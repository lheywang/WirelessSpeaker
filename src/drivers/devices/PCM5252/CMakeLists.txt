# ========================================================================================
# PCM5252
# ========================================================================================
# Add sources
set(PCM5252_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/PCM5252.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(pcm5252 ${PCM5252_SOURCES})

# Make the current directory and its 'includes' subdirectories available
target_link_libraries(pcm5252 PUBLIC i2c)