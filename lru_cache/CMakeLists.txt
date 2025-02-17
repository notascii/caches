cmake_minimum_required(VERSION 3.10)
project(template_project VERSION 0.1.0 LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -pedantic -pedantic-errors")

# --- Google Test ---
# Download and unpack googletest at configure time
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

# Set include directories
include_directories(include)

# Set source files
file(GLOB SOURCES
    src/*.cpp
)

add_executable(main src/main.cpp ${SOURCES})

# --- Useless ? ---
# Set test files
# file(GLOB TEST_SOURCES
#     test/*.cpp
# )
# include(GoogleTest)  # --> this is included in tests/ CMakelists.txt
# -----------------

# Enable testing for current directory and below
enable_testing()

# add test subdirectory
add_subdirectory(tests)
