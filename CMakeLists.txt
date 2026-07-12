cmake_minimum_required(VERSION 3.25)

project(CoEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Architecture & Platform Safety Checks ---
if(APPLE)
    if("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
        set(CMAKE_OSX_ARCHITECTURES "arm64")
    else()
        set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
    endif()
elseif(ANDROID)
    # Ensure Android uses appropriate shared STL
    set(ANDROID_STL c++_shared)
elseif(WIN32)
    # Ensure Windows uses correct CRT settings
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
endif()

# --- Force Geode Discovery (Fallback) ---
# If cmake-args doesn't catch it, we try the environment variable
if(NOT Geode_DIR AND DEFINED ENV{GEODE_SDK})
    message(STATUS "Geode_DIR not set via args, falling back to ENV{GEODE_SDK}")
    set(Geode_DIR "$ENV{GEODE_SDK}")
endif()

# Now find the package
find_package(Geode REQUIRED)

# --- Mod Configuration ---
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

# Define the mod (matches mod.json ID: procedural.architect.co_engine)
add_geode_mod(
    procedural.architect.co_engine
    SOURCES ${SRC_FILES}
    RESOURCES 
        resources/PSM_Sheet.png 
        resources/PSM_Sheet.plist
)

# Link Geode
target_link_libraries(procedural.architect.co_engine PRIVATE Geode::geode)

# --- Performance Optimization ---
if(MSVC)
    target_compile_options(procedural.architect.co_engine PRIVATE /O2 /W3)
else()
    target_compile_options(procedural.architect.co_engine PRIVATE -O3 -Wall -Wextra)
endif()
