cmake_minimum_required(VERSION 3.25)
project(CoEngine VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Geode REQUIRED)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp src/*.hpp)

add_geode_mod(
    procedural.architect.co_engine
    SOURCES ${SRC_FILES}
    RESOURCES 
        resources/PSM_Sheet.png 
        resources/PSM_Sheet.plist
)

target_link_libraries(procedural.architect.co_engine PRIVATE Geode::geode)
