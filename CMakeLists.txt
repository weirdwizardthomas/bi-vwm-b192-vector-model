# Minimum CMake version, project name and project version
cmake_minimum_required(VERSION 3.1)
project(VectorModel VERSION 1.0)

# C++ 11 compiler is required
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectory SQLiteCpp with all necessary files
add_subdirectory(./lib/SQLiteCpp)

add_executable(main ./src/weight_calculation/main.cpp)

target_link_libraries(main SQLiteCpp)
