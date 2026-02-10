add_library(lcxp STATIC
    src/lcxp.cpp
)

target_compile_options(lcxp PRIVATE -Wall -Wextra)

target_include_directories(lcxp PUBLIC 
    include
)