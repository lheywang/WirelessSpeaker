add_library(lcxp_main STATIC
    src/main.cpp
)

add_executable(lxcp_main)

target_compile_options(lcxp_main PRIVATE -Wall -Wextra)

target_sources(lxcp_main
    PRIVATE
    src/main.cpp
)

target_include_directories(lcxp_main PUBLIC 
    include
    lxcp
    lcap
    lcip
)