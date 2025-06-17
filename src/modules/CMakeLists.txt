# ========================================================================================
# MODULES
# ========================================================================================
# Links
add_subdirectory(libcrc)
add_subdirectory(eeprom)

# Link all the libraries into the all lib 
target_link_libraries($ENV{NAME}::all_libs 
    INTERFACE 
    libcrc 
    eeprom 
)