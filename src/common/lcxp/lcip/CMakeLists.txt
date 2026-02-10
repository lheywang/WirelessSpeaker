add_library(lcip STATIC
    src/lcip.cpp
)

target_compile_options(lcip PRIVATE -Wall -Wextra)

target_link_libraries(lcip PRIVATE lxcp)

target_include_directories(lcip PUBLIC 
    include
)