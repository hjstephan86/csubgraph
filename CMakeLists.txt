cmake_minimum_required(VERSION 3.10)
project(SubgraphAlgorithm)

# C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Flags für Windows/MSVC
if(MSVC)
    add_compile_options(/W4 /permissive-)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Hauptbibliothek
add_library(subgraph_lib
    SubgraphAlgorithm.cpp
    SubgraphAlgorithm.h
)

target_include_directories(subgraph_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Google Test einbinden
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Test-Executable
add_executable(subgraph_tests SubgraphTest.cpp)
target_link_libraries(subgraph_tests PRIVATE subgraph_lib gtest gtest_main)

# Code Coverage aktivieren
if(MSVC)
    # Visual Studio / OpenCppCoverage
    target_compile_options(subgraph_tests PRIVATE /Zi)
    target_link_options(subgraph_tests PRIVATE /DEBUG)
else()
    # GCC / Clang mit gcov
    target_compile_options(subgraph_lib PRIVATE --coverage)
    target_link_libraries(subgraph_lib PRIVATE --coverage)
    target_compile_options(subgraph_tests PRIVATE --coverage)
    target_link_libraries(subgraph_tests PRIVATE --coverage)
endif()

# Test-Ziel
enable_testing()
add_test(NAME SubgraphTests COMMAND subgraph_tests)
