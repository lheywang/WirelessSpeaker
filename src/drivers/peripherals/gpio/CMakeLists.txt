# ========================================================================================
# GPIO
# ========================================================================================
# Add sources
set(GPIO_SOURCES    ${CMAKE_CURRENT_SOURCE_DIR}/gpio.cpp \\
                    ${CMAKE_CURRENT_SOURCE_DIR}/includes/clk.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(gpio ${GPIO_SOURCES})
