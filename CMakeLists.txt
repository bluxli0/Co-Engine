cmake_minimum_required(VERSION 3.25)

# Initialize Geode project configuration
project(CoEngine VERSION 1.0.0 LANGUAGES CXX)

include(FetchContent)

# Automatically link Geode SDK framework configuration modules
find_package(Geode REQUIRED)

# Define source directories mapping core architecture splits
file(GLOB_RECURSE SRC_FILES 
    src/main.cpp 
    src/core/*.cpp 
    src/ui/*.cpp 
    src/hooks/*.cpp
)

# Set runtime target build configuration
add_geode_mod(
    procedural.architect.co_engine
    RESOURCES 
        resources/PSM_Sheet.png 
        resources/PSM_Sheet.plist
    SOURCES 
        ${SRC_FILES}
)

# Cross-platform compiler flags optimization pass logic
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /O2 /W3)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -O3 -Wall -Wextra -std=c++20)
endif()
