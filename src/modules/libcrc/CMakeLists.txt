# ========================================================================================
# LIBCRC
# ========================================================================================
# External libraries includes                       
set(CRC_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/crc8.c\\
                ${CMAKE_CURRENT_SOURCE_DIR}/crc16.c\\
                ${CMAKE_CURRENT_SOURCE_DIR}/crc32.c\\
                ${CMAKE_CURRENT_SOURCE_DIR}/crc64.c\\
                ${CMAKE_CURRENT_SOURCE_DIR}/crcccitt.c\\
                ${CMAKE_CURRENT_SOURCE_DIR}/crckrmit.c\\
                ${CMAKE_CURRENT_SOURCE_DIR}/crcsick.c\\
                ${CMAKE_CURRENT_SOURCE_DIR}/nmea-chk.c)


# Create the library target.
add_library(crc ${CRC_SOURCES})

# Expose its include directories to other targets.
target_include_directories(crc
  PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)
