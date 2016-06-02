cmake_minimum_required(VERSION 2.8.12)
project(s2mg)

# s2mg Library

file(GLOB_RECURSE S2MG_SOURCE_FILES src/*.cpp)
file(GLOB_RECURSE S2MG_HEADER_FILES src/*.hpp)

add_library(s2mg ${S2MG_SOURCE_FILES} ${S2MG_HEADER_FILES})
target_compile_options(s2mg PUBLIC "-std=c++11")
target_compile_options(s2mg PRIVATE "-Wall")
target_compile_options(s2mg PRIVATE "-Wpedantic")
target_compile_options(s2mg PRIVATE "-Werror")
target_include_directories(s2mg PUBLIC src)

# Test Executable

file(GLOB_RECURSE S2MG_TEST_SOURCE_FILES test/*.cpp)
file(GLOB_RECURSE S2MG_TEST_HEADER_FILES test/*.hpp)

add_subdirectory(extern/googletest)
add_executable(s2mg-test ${S2MG_TEST_SOURCE_FILES} ${S2MG_TEST_HEADER_FILES})
target_link_libraries(s2mg-test PRIVATE s2mg gtest_main)
target_compile_options(s2mg-test PRIVATE "-std=c++11")
target_compile_options(s2mg-test PRIVATE "-Wall")
target_compile_options(s2mg-test PRIVATE "-Wpedantic")
target_compile_options(s2mg-test PRIVATE "-Werror")
