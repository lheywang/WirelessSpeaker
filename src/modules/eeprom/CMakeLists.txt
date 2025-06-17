# ========================================================================================
# EEPROM
# ========================================================================================
# Set sources
set(EEPROM_SOURCES  ${CMAKE_CURRENT_SOURCE_DIR}/eeprom.cpp\\
                    ${CMAKE_CURRENT_SOURCE_DIR}/dsp_profile/dsp_profile.cpp)

add_library(eeprom ${EEPROM_SOURCES})

# This module needs access to its own headers.
target_include_directories(eeprom
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Link this module to its dependencies.
target_link_libraries(eeprom
  PUBLIC
    crc
    m95256
)
