cmake_minimum_required(VERSION 3.25)
project(CoEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Instead of find_package, include Geode's helper.
# This file is provided by the SDK automatically.
include(Geode) 

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

add_geode_mod(
    procedural.architect.co_engine
    SOURCES ${SRC_FILES}
    RESOURCES 
        resources/PSM_Sheet.png 
        resources/PSM_Sheet.plist
)

# This target is created by add_geode_mod
target_link_libraries(procedural.architect.co_engine PRIVATE Geode::geode)
