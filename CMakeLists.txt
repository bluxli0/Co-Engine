cmake_minimum_required(VERSION 3.25)

project(CoEngine VERSION 1.0.0 LANGUAGES CXX)

# --- Standard C++20 Setup ---
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Apple Platform Architecture Fix ---
# This ensures macOS and iOS build for the correct processor (arm64/x86_64)
if(APPLE)
    if("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
        set(CMAKE_OSX_ARCHITECTURES "arm64")
    else()
        set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
    endif()
endif()

# --- Find Geode SDK ---
# The build-geode-mod action injects the paths; this command loads the logic
find_package(Geode REQUIRED)

# --- Collect Sources ---
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

# --- Define the Mod ---
# 'procedural.architect.co_engine' must match your mod.json id
add_geode_mod(
    procedural.architect.co_engine
    SOURCES ${SRC_FILES}
    RESOURCES 
        resources/PSM_Sheet.png 
        resources/PSM_Sheet.plist
)

# --- Link & Optimize ---
target_link_libraries(procedural.architect.co_engine PRIVATE Geode::geode)

# Production-grade optimization
if(MSVC)
    target_compile_options(procedural.architect.co_engine PRIVATE /O2 /W3)
else()
    target_compile_options(procedural.architect.co_engine PRIVATE -O3 -Wall -Wextra)
endif()
