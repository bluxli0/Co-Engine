cmake_minimum_required(VERSION 3.25)

project(CoEngine VERSION 1.0.0 LANGUAGES CXX)

# Attempt to find Geode, if it fails, provide a hint to the environment
find_package(Geode REQUIRED)

# Glob all source files in the modular structure
file(GLOB_RECURSE SRC_FILES 
    src/*.cpp
)

add_geode_mod(
    procedural.architect.co_engine
    RESOURCES 
        resources/PSM_Sheet.png 
        resources/PSM_Sheet.plist
    SOURCES 
        ${SRC_FILES}
)

# Crucial: Ensure the mod links correctly to the SDK
target_link_libraries(procedural.architect.co_engine PRIVATE Geode::geode)

# Optimization flags
if(MSVC)
    target_compile_options(procedural.architect.co_engine PRIVATE /O2 /W3)
else()
    target_compile_options(procedural.architect.co_engine PRIVATE -O3 -Wall -Wextra -std=c++20)
endif()
