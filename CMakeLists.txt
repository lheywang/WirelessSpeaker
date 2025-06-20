# ========================================================================================
# PROJECT OPTIONS
# ========================================================================================
cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project($ENV{NAME})

# Setting colors variables for further usage
if(NOT WIN32)
  string(ASCII 27 Esc)
  set(ColourReset "${Esc}[m")
  set(ColourBold  "${Esc}[1m")
  set(Red         "${Esc}[31m")
  set(Green       "${Esc}[32m")
  set(Yellow      "${Esc}[33m")
  set(Blue        "${Esc}[34m")
  set(Magenta     "${Esc}[35m")
  set(Cyan        "${Esc}[36m")
  set(White       "${Esc}[37m")
  set(BoldRed     "${Esc}[1;31m")
  set(BoldGreen   "${Esc}[1;32m")
  set(BoldYellow  "${Esc}[1;33m")
  set(BoldBlue    "${Esc}[1;34m")
  set(BoldMagenta "${Esc}[1;35m")
  set(BoldCyan    "${Esc}[1;36m")
  set(BoldWhite   "${Esc}[1;37m")
endif()

# ========================================================================================
# FILES INCLUDES
# ========================================================================================
# Prepare for storing all of the libs
add_library(MasterLibs INTERFACE)

# Adding headers files
include_directories(inc/)

# Adding sources for standard build
add_subdirectory(src/drivers)
add_subdirectory(src/modules)

# Internal libraries
set(LIBS    ${CMAKE_BINARY_DIR}/bin/config.o\\
            ${CMAKE_BINARY_DIR}/bin/header.o)

# ========================================================================================
# USER LOGIC
# ========================================================================================
# Ask for the BUILD mode
option(BUILD_TESTS "Build the unit test executable instead of the main application." OFF)
option(COVERAGE "Build the coverage flags inside of the executable." OFF)

# ========================================================================================
# EXECUTABLES
# ========================================================================================
if (BUILD_TESTS)
    # Building the mocks library
    add_subdirectory(tests)

    # User infos
    message("${BoldCyan}Configuring for Unit Test build (Host: x86_64) ${ColourReset}")

    # Add some compiler flags for the final usage
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Wextra ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -std=c++20 -Wall -Wextra ")

    if (COVERAGE)
        message("${BoldCyan}Addind coverage flags ${ColourReset}")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage ")

        # Add linker options
        add_link_options("-lgcov")
    endif()
    
    # Add some headers search path
    include_directories(tools/cpputest/include/)
    include_directories(tools/cpputest/include/CppUTest/)

    # Including the build of the CppUTest framework
    add_subdirectory(tools/cpputest)

    file(GLOB_RECURSE TEST_SOURCE_FILES
         "${CMAKE_CURRENT_SOURCE_DIR}/*TEST_*.cpp"
    )

    # Create an executable
    add_executable(UnitsTests tests/tester.cpp ${TEST_SOURCE_FILES})

    # Link the executable against the libraries it needs.
    target_link_libraries(UnitsTests
        PRIVATE
        CppUTest
        CppUTestExt
        MasterLibs
    )

else()
    # User info
    message(STATUS "${BoldCyan}Configuring for Main Application build (Target: AARCH64) ${ColourReset}")

    # Add some compiler flags for the final usage
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -mcpu=cortex-a53 -O3 -MMD -Wall -Wextra ")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mcpu=cortex-a53 -O3 -std=c++20 -MMD -Wall -Wextra ")

    # Add an executable
    add_executable($ENV{APPNAME} src/main.cpp)

    # Link the executable against the libraries it needs.
    target_link_libraries($ENV{APPNAME}
        PRIVATE
        MasterLibs
        ${LIBS}
    )

endif()