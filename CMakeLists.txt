cmake_minimum_required(VERSION 3.20)
project(rupture2d VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dependencies
include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.4.0
)
FetchContent_MakeAvailable(Catch2)

# Library
add_library(rupture2d
    src/placeholder.cpp
    src/Logger.cpp
    src/Physics/AABB.cpp
    src/Physics/NarrowPhase.cpp
    src/Physics/RigidBody.cpp
    src/Shapes/Circle.cpp
    src/Shapes/Polygon.cpp
)
target_include_directories(rupture2d PUBLIC include)
target_compile_definitions(rupture2d PUBLIC RUPTURE_DEBUG)

# Demo
add_executable(demo demos/main.cpp)
target_link_libraries(demo PRIVATE rupture2d)

# Tests
add_executable(tests
    #tests/test_aabb.cpp
    tests/test_narrowphase.cpp
    #tests/test_rigidbody.cpp
    #tests/test_shapes.cpp
    #tests/test_vec2.cpp
)
target_link_libraries(tests PRIVATE rupture2d Catch2::Catch2WithMain)