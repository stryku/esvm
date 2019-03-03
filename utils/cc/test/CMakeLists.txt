project(esvm_cross_compiler_test)

set(SOURCES
    main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME}
    gtest_main
    gmock_main
)
