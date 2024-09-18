# Include FetchContent module for downloading dependencies
include(FetchContent)

# Declare GoogleTest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/release-1.12.1.zip
)

# Prevent overriding the parent project's compiler/linker settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Make available to the parent
FetchContent_MakeAvailable(googletest)

# Add the test executables
add_executable(wordladder_tests
    word_finder_test.cpp
    word_ladder_test.cpp
    word_parser_test.cpp
    neighbor_generator_test.cpp
    ../src/word_finder.cpp
    ../src/word_ladder.cpp
    ../src/word_parser.cpp
    ../src/neighbor_generator.cpp
)

# Link test executable against GoogleTest libraries and wordladder_lib
target_link_libraries(wordladder_tests
    PRIVATE
    GTest::gtest
    GTest::gtest_main
    wordladder_lib
)

# Discover and register tests
include(GoogleTest)
gtest_discover_tests(wordladder_tests)