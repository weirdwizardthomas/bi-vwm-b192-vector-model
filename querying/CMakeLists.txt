cmake_minimum_required(VERSION 3.15)
project(Querying)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib/SQLiteCpp)

SET(CMAKE_CXX_FLAGS "-g -Wall -pedantic -Wextra")

add_executable(main src/main.cpp src/inverted_index/InvertedIndex.cpp src/inverted_index/InvertedIndex.h src/inverted_index/InputParser.cpp src/inverted_index/InputParser.h src/space/Space.cpp src/space/Space.h src/space/Query.cpp src/space/Query.h src/Computor.cpp src/Computor.h src/Document.cpp src/Document.h src/exceptions/Exceptions.h)

target_link_libraries(main SQLiteCpp)
