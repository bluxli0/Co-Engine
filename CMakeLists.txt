cmake_minimum_required(VERSION 3.21)
project(CoEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Architecture handling
if ("${CMAKE_SYSTEM_NAME}" STREQUAL "iOS" OR IOS)
    set(CMAKE_OSX_ARCHITECTURES "arm64")
else()
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# 1. Glob your sources
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

# 2. Add your library
add_library(${PROJECT_NAME} SHARED ${SRC_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC "src")

# 3. Locate and add Geode
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "GEODE_SDK environment variable not found!")
endif()

add_subdirectory($ENV{GEODE_SDK} ${CMAKE_CURRENT_BINARY_DIR}/geode SYSTEM)

# 4. Set up the mod
# Geode automatically detects your resources folder if it is named 'resources'
# and is in the same directory as this CMakeLists.txt
setup_geode_mod(${PROJECT_NAME})

# 5. Compiler Warnings (Suppressed for sanity)
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4 /wd4267 /wd4244 /wd4018)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE
        -Wall 
        -Wextra 
        -Wno-unknown-pragmas
        -Wno-unused-parameter
        -Wno-unused-variable
        -Wno-sign-compare
        -Wno-dollar-in-identifier-extension
        -Wno-overloaded-virtual
        -Wno-gnu-statement-expression-from-macro-expansion
        -Wno-extra-semi
    )
endif()
