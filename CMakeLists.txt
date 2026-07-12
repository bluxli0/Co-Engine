cmake_minimum_required(VERSION 3.25)
project(CoEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- THE FIX ---
# We force CMake to look ONLY in the GEODE_SDK directory.
# This bypasses the need for FindGeode.cmake and stops the 404 search error.
if(DEFINED ENV{GEODE_SDK})
    message(STATUS "Locating Geode at: $ENV{GEODE_SDK}")
    find_package(Geode REQUIRED PATHS "$ENV{GEODE_SDK}" NO_DEFAULT_PATH)
else()
    # Fallback for local development if the env var isn't set
    find_package(Geode REQUIRED)
endif()

# --- Everything Else ---
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

add_geode_mod(
    procedural.architect.co_engine
    SOURCES ${SRC_FILES}
    RESOURCES 
        resources/PSM_Sheet.png 
        resources/PSM_Sheet.plist
)

target_link_libraries(procedural.architect.co_engine PRIVATE Geode::geode)

if(APPLE)
    if("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
        set(CMAKE_OSX_ARCHITECTURES "arm64")
    else()
        set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
    endif()
endif()
