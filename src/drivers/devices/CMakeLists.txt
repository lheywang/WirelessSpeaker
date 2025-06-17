# ========================================================================================
# DEVICES
# ========================================================================================
# Bridging to sub sources
add_subdirectory(ADS1015)
add_subdirectory(AT42QT1070)
add_subdirectory(DS1882)
add_subdirectory(INA219)
add_subdirectory(MCP45HV51)
add_subdirectory(MCP9808)
add_subdirectory(MCP23009)
add_subdirectory(PCA9633)
add_subdirectory(PCM5252)
add_subdirectory(STUSB4500)
add_subdirectory(M95256)

# Update the shared variable for including libs and propagate to parent
list(APPEND ALL_APP_LIBS ads1015 at42qt1070 ds1882 ina219 mcp45hv51 mcp9808 mcp23009 pca9633 pcm5252 stusb4500 m95256)
set(ALL_APP_LIBS "${ALL_APP_LIBS}" PARENT_SCOPE)
