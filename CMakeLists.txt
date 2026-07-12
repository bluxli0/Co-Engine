cmake_minimum_required(VERSION 3.25)

# Setup C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(CoEngine VERSION 1.0.0 LANGUAGES CXX)

# Glob source files
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# Ensure the GEODE_SDK environment variable is present
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "GEODE_SDK environment variable is not set. Geode SDK was not found.")
endif()

message(STATUS "Using Geode SDK from: $ENV{GEODE_SDK}")

# Add the SDK as a subdirectory
add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode)

# Define the mod and its resources
add_geode_mod(
    procedural.architect.co_engine
    SOURCES ${SOURCES}
    RESOURCES 
        resources/PSM_Sheet.png 
        resources/PSM_Sheet.plist
)

# Optional: Add your custom optimization flags
if(MSVC)
    target_compile_options(procedural.architect.co_engine PRIVATE /O2)
else()
    target_compile_options(procedural.architect.co_engine PRIVATE -O3 -Wall -Wextra)
endif()
