# CMakeLists.txt
cmake_minimum_required(VERSION 3.14)
project(WordLadder)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Ensure Release build
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Add include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Add source files
add_library(wordladder_lib
    src/word_finder.cpp
    src/word_ladder.cpp
    src/word_parser.cpp
    src/neighbor_generator.cpp
)

# Add main executable
add_executable(wordladder src/main.cpp)
target_link_libraries(wordladder PRIVATE wordladder_lib)

# Add subdirectory for tests
add_subdirectory(tests)

# Post-build message to indicate where the executable is located
add_custom_command(TARGET wordladder POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Executable is located in: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)