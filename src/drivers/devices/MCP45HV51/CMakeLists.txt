# ========================================================================================
# MCP45HV51
# ========================================================================================
# Add sources
set(MCP45HV51_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/MCP45HV51.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(mcp45hv51 ${MCP45HV51_SOURCES})

# Make the current directory and its 'includes' subdirectories available
target_link_libraries(mcp45hv51 PUBLIC i2c)