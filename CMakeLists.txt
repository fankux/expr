cmake_minimum_required(VERSION 3.10)
project(expr)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SRCS
        *.h
        *.hpp
        *.cpp
        )
add_executable(expr ${SRCS})