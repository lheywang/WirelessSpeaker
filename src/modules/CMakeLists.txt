# ========================================================================================
# MODULES
# ========================================================================================
# Links
add_subdirectory(libcrc)
add_subdirectory(eeprom)

# Update the shared variable for including libs and propagate to parent
list(APPEND ALL_APP_LIBS libcrc eeprom)
set(ALL_APP_LIBS "${ALL_APP_LIBS}" PARENT_SCOPE)