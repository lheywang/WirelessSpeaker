if (TESTS_BUILDS_LCXP)
    add_executable(lcxp_main src/main.cpp)

    target_compile_options(lcxp_main PRIVATE -Wall -Wextra)

    target_link_libraries(lcxp_main PRIVATE
        lcxp
        lcap
        lcip
    )

    target_include_directories(lcxp_main PRIVATE include)

endif(TESTS_BUILDS_LCXP)