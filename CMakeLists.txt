cmake_minimum_required(VERSION 3.10)
project(expr)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SRCS
        *.h
        *.cpp
        )

link_libraries(
        pthread
        -fsanitize=address
)

add_definitions(
        -fsanitize=address
        -fno-omit-frame-pointer
        -g
)

add_executable(expr ${SRCS})