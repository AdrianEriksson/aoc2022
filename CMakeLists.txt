cmake_minimum_required(VERSION 3.16.3)

project(aoc2022)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(parser)
add_subdirectory(solutions)

target_link_libraries(${PROJECT_NAME} PUBLIC parser PUBLIC solutions)

target_include_directories(${PROJECT_NAME} 
    PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/parser"
    PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}/solutions")
