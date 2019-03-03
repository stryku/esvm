project(esvm_cross_compiler)

set(SOURCES
    main.cpp
    lexer.cpp
    lexer.hpp
)

add_executable(esvm_cross_compiler ${SOURCES})

add_subdirectory(test)
