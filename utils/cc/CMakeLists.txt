project(esvm_cross_compiler)

set(CC_LIB_SOURCES
    lexer.cpp
    lexer.hpp
)

set(SOURCES
    main.cpp
        token.hpp)

add_library(${PROJECT_NAME}_lib STATIC ${CC_LIB_SOURCES})
target_include_directories(${PROJECT_NAME}_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_lib)

add_subdirectory(test)
