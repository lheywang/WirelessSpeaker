# ========================================================================================
# MCP23009
# ========================================================================================
# Add sources
set(MCP23009_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/MCP23009.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(mcp23009 ${MCP23009_SOURCES})

# Make the current directory and its 'includes' subdirectories available
target_link_libraries(mcp23009 PUBLIC i2c)