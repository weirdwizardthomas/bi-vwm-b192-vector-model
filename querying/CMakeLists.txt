cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 17)

set(TARGET_NAME Querying)

project(${TARGET_NAME})

# Check the build type and ask the user to set concrete one
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE RelWithDebInfo)
    message(WARNING "CMAKE_BUILD_TYPE is not set, forcing to RelWithDebInfo")
endif ()

# Set compiler flags
if (${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3")
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g3")
    set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os")
endif ()

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

# Add subdirectory SQLiteCpp with all necessary files
add_subdirectory(lib/SQLiteCpp)


# Source files
set(SOURCES
        src/calculation/Computor.cpp src/calculation/Computor.h
        src/calculation/InvertedIndex.cpp src/calculation/InvertedIndex.h
        src/calculation/Query.cpp src/calculation/Query.h
        src/calculation/Space.cpp src/calculation/Space.h
        src/calculation/WeightedDocument.cpp src/calculation/WeightedDocument.h
        src/database/Database.cpp src/database/Database.h
        src/database/Document.cpp src/database/Document.h
        src/enum/EInvertedIndex.h
        src/ui/Page.cpp src/ui/Page.h
        src/util/ArgumentParser.cpp src/util/ArgumentParser.h
        src/util/InvertedIndexJSONParser.cpp src/util/InvertedIndexJSONParser.h
        src/util/QueryJSONParser.cpp src/util/QueryJSONParser.h
        src/main.cpp
        )

# Shared libraries
set(LIBRARIES
        SQLiteCpp
        wt
        wthttp
        )

# Set target
add_executable(${TARGET_NAME} ${SOURCES})

# Link with libraries
target_link_libraries(${TARGET_NAME} ${LIBRARIES})
