cmake_minimum_required(VERSION 3.15)
project(Querying)

set(CMAKE_CXX_STANDARD 17)

SET(CMAKE_CXX_FLAGS "-g -Wall -pedantic -Wextra")

add_executable(main
        src/main.cpp
        src/inverted_index/InvertedIndex.cpp src/inverted_index/InvertedIndex.h
        src/inverted_index/InvertedIndexJSONParser.cpp src/inverted_index/InvertedIndexJSONParser.h
        src/space/Space.cpp src/space/Space.h
        src/query/Query.cpp src/query/Query.h
        src/Computor.cpp src/Computor.h
        src/Document.cpp src/Document.h
        src/exceptions/Exceptions.h src/query/QueryJSONParser.cpp src/query/QueryJSONParser.h src/argument_parser/argument_parser.cpp)

target_link_libraries(main)
