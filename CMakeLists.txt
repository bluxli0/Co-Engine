cmake_minimum_required(VERSION 3.25)
project(CoEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- THE FIX ---
# Tell CMake to search the directory defined by the Geode action
if(DEFINED ENV{GEODE_SDK})
    list(APPEND CMAKE_PREFIX_PATH "$ENV{GEODE_SDK}")
endif()

find_package(Geode REQUIRED)

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
