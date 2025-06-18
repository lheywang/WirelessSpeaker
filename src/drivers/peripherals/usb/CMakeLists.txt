# ========================================================================================
# USB
# ========================================================================================
# Add sources
set(USB_SOURCES     ${CMAKE_CURRENT_SOURCE_DIR}/usb.cpp)

# Create a library for all of theses sources (we may even split them in sub libraries ...)
add_library(usb ${USB_SOURCES})