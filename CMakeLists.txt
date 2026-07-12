cmake_minimum_required(VERSION 3.25)
project(procedural.architect.co_engine VERSION 1.0.0 LANGUAGES CXX)

# The build-geode-mod action automatically sets up the Geode find-package path.
# We just need to find it correctly.
find_package(Geode REQUIRED)

# Glob sources
file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)

# Define the mod
add_geode_mod(
    procedural.architect.co_engine
    SOURCES ${SRC_FILES}
    RESOURCES 
        resources/PSM_Sheet.png 
        resources/PSM_Sheet.plist
)

# Link
target_link_libraries(procedural.architect.co_engine PRIVATE Geode::geode)
