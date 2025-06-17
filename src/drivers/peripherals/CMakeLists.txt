# ========================================================================================
# PERIPHERALS
# ========================================================================================
add_subdirectory(gpio)
add_subdirectory(i2c)
add_subdirectory(spi)
add_subdirectory(uart)
add_subdirectory(usb)

# Update the shared variable for including libs and propagate to parent
list(APPEND ALL_APP_LIBS gpio i2c spi uart usb)
set(ALL_APP_LIBS "${ALL_APP_LIBS}" PARENT_SCOPE)

# Link all the libraries into the all lib 
target_link_libraries($ENV{NAME}::all_libs 
    INTERFACE 
    gpio 
    spi 
    uart 
    usb 
    i2c
)
