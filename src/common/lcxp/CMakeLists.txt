add_subdirectory(lcxp)
add_subdirectory(lcap)
add_subdirectory(lcip)

if (TESTS_BUILDS_LXCP)
    add_subdirectory(test)
endif(TESTS_BUILDS_LXCP)