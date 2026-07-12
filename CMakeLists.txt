cmake_minimum_required(VERSION 3.25)

# 1. Project Setup
project(CoEngine VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. SDK Discovery (Robust)
if (NOT DEFINED ENV{GEODE_SDK})
    message(FATAL_ERROR "GEODE_SDK environment variable is not set. Please ensure the GitHub Action has initialized the SDK.")
endif()

# We include the SDK's entry point to register commands like add_geode_mod
# Using include instead of add_subdirectory ensures commands are available immediately
list(APPEND CMAKE_MODULE_PATH "$ENV{GEODE_SDK}/cmake")
include(GeodeConfig)

# 3. Source Collection
file(GLOB_RECURSE SRC_FILES 
    CONFIGURE_DEPENDS 
    src/*.cpp
    src/*.hpp
)

# 4. Mod Definition
# This command is now guaranteed to be available because of include(GeodeConfig)
add_geode_mod(
    procedural.architect.co_engine
    SOURCES ${SRC_FILES}
    RESOURCES 
        resources/PSM_Sheet.png 
        resources/PSM_Sheet.plist
)

# 5. Build Configuration
# Optimization flags to ensure your engine runs smoothly
if(MSVC)
    target_compile_options(procedural.architect.co_engine PRIVATE /O2 /W3)
else()
    target_compile_options(procedural.architect.co_engine PRIVATE -O3 -Wall -Wextra)
endif()

# 6. Linking
target_link_libraries(procedural.architect.co_engine PRIVATE Geode::geode)
