cmake_minimum_required(VERSION 3.15)
project(Querying)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-g -Wall -pedantic -Wextra")

add_executable(main
        src/main.cpp
        src/calculation/InvertedIndex.cpp src/calculation/InvertedIndex.h
        src/util/InvertedIndexJSONParser.cpp src/util/InvertedIndexJSONParser.h
        src/calculation/Space.cpp src/calculation/Space.h
        src/calculation/Query.cpp src/calculation/Query.h
        src/calculation/Computor.cpp src/calculation/Computor.h
        src/calculation/Document.cpp src/calculation/Document.h
        src/util/QueryJSONParser.cpp src/util/QueryJSONParser.h
        src/exceptions/Exceptions.h)

target_link_libraries(main)
