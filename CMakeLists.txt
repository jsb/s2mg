cmake_minimum_required(VERSION 2.8.12)
project(s2mg)

file(GLOB S2MG_SOURCE_FILES *.cpp)
file(GLOB S2MG_HEADER_FILES *.hpp)

add_executable(s2mg ${S2MG_SOURCE_FILES} ${S2MG_HEADER_FILES})
target_compile_options(s2mg PRIVATE "-std=c++11")
target_compile_options(s2mg PRIVATE "-Wall")
target_compile_options(s2mg PRIVATE "-Wpedantic")
target_compile_options(s2mg PRIVATE "-Werror")
