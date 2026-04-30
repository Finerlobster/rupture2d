cmake_minimum_required(VERSION 3.20)
project(rupture2d VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(rupture2d 
    src/placeholder.cpp
    src/Logger.cpp
)

target_include_directories(rupture2d PUBLIC include)
target_compile_definitions(rupture2d PUBLIC RUPTURE_DEBUG)

add_executable(demo demos/main.cpp)
target_link_libraries(demo PRIVATE rupture2d)

