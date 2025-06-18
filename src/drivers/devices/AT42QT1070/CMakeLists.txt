# ========================================================================================
# AT42QT1070
# ========================================================================================
# Add sources
set(AT42QT1070_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/AT42QT1070.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(at42qt1070 ${AT42QT1070_SOURCES})

# Make the current directory and its 'includes' subdirectories available
target_link_libraries(at42qt1070 PUBLIC i2c)