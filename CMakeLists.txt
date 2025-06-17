# ========================================================================================
# PROJECT OPTIONS
# ========================================================================================
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project($ENV{NAME})

# ========================================================================================
# FILES INCLUDES
# ========================================================================================
# Adding headers files
include_directories(inc/)

add_subdirectory(src/drivers)
add_subdirectory(src/modules)

# Internal libraries
set(LIBS    ${CMAKE_BINARY_DIR}/bin/config.o\\
            ${CMAKE_BINARY_DIR}/bin/header.o)

# ========================================================================================
# COMPILERS SETTINGS
# ========================================================================================
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-a53 -O3 -MMD -Wall -Wextra ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=cortex-a53 -O3 -std=c++20 -MMD -Wall -Wextra ")

# ========================================================================================
# EXECUTABLES
# ========================================================================================
add_executable($ENV{APPNAME} src/main.cpp ${LIBS})

# Link the executable against the libraries it needs.
target_link_libraries($ENV{APPNAME}
  PRIVATE
    eeprom
    devices
)