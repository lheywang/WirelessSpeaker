# ========================================================================================
# MCP9808
# ========================================================================================
# Add sources
set(MCP9808_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/MCP9808.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(mcp9808 ${MCP9808_SOURCES})

# Make the current directory and its 'includes' subdirectories available
target_link_libraries(mcp9808 PUBLIC i2c)