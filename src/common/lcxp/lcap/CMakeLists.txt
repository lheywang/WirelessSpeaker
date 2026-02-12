add_library(lcap STATIC
    src/lcap.cpp
)

target_compile_options(lcap PRIVATE -Wall -Wextra)

target_link_libraries(lcap PRIVATE lcxp)

target_include_directories(lcap PUBLIC 
    include
)