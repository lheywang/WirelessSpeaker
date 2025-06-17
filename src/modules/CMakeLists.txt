# ========================================================================================
# MODULES
# ========================================================================================
# Links
add_subdirectory(libcrc)
add_subdirectory(eeprom)

# Link all the libraries into the all lib 
target_link_libraries(MasterLibs
    INTERFACE 
    libcrc 
    eeprom 
)