cmake_minimum_required(VERSION 3.25)

project(CoEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Glob sources
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

# 2. Modern Geode Mod Definition
# This command automatically handles linking, library creation, and SDK integration
add_geode_mod(
    procedural.architect.co_engine
    SOURCES ${SOURCES}
    RESOURCES 
        resources/PSM_Sheet.png 
        resources/PSM_Sheet.plist
)

# 3. Link to the Geode SDK
target_link_libraries(procedural.architect.co_engine PRIVATE Geode::geode)

# 4. Optimization flags
if(MSVC)
    target_compile_options(procedural.architect.co_engine PRIVATE /O2 /W3)
else()
    target_compile_options(procedural.architect.co_engine PRIVATE -O3 -Wall -Wextra)
endif()
