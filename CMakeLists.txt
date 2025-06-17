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

# Prepare for storing all of the libs
set(ALL_APP_LIBS "")

# ========================================================================================
# USER LOGIC
# ========================================================================================
# Ask for the BUILD mode
option(BUILD_TESTS "Build the unit test executable instead of the main application." OFF)

# ========================================================================================
# EXECUTABLES
# ========================================================================================
if (BUILD_TESTS)
    # User infos
    message(STATUS "Configuring for Unit Test build (Host: x86_64)")

    # Add some headers search path
    include_directories(tools/cpputest/include/)
    include_directories(tools/cpputest/include/CppUTest/)

    # Including the build of the CppUTest framework
    add_subdirectory(tools/cpputest)

    # Create an executable
    add_executable(UnitsTests tests/tester.cpp)

    # Link the executable against the libraries it needs.
    target_link_libraries(UnitsTests
        PRIVATE
        ${ALL_APP_LIBS}
        CppUTest
        CppUTestExt
    )

else()
    # User info
    message(STATUS "Configuring for Main Application build (Target: AARCH64)")

    # Add some compiler flags for the final usage
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-a53 -O3 -MMD -Wall -Wextra ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=cortex-a53 -O3 -std=c++20 -MMD -Wall -Wextra ")

    # Add an executable
    add_executable($ENV{APPNAME} src/main.cpp ${LIBS})

    # Link the executable against the libraries it needs.
    target_link_libraries($ENV{APPNAME}
        PRIVATE
        ${ALL_APP_LIBS}
    )

endif()