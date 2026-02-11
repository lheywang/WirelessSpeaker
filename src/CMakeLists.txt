cmake_minimum_required(VERSION 3.16)
project(WirelessSpeaker VERSION 0.1 LANGUAGES CXX)

# Configure bases
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TESTS_BUILDS_LXCP "Build the main.cpp file associated with the LXCP tests" OFF)

# Add the common sources
add_subdirectory(common)