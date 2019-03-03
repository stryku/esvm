set(SOURCES
    main.cpp
    lexer_test.cpp
)

add_executable(${PROJECT_NAME}_test ${SOURCES})
target_link_libraries(${PROJECT_NAME}_test
    gtest_main
    gmock_main
    ${PROJECT_NAME}_lib
)
