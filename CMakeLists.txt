cmake_minimum_required(VERSION 3.13)  # CMake version check

project(PerfTimer_example)               # Create project "simple_example"
set(CMAKE_CXX_STANDARD 14)            # Enable c++14 standard

find_package( Threads )

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(PerfTimer_example 
    example/main.cpp
    src/PerfTimer.cpp
)

target_link_libraries( PerfTimer_example ${CMAKE_THREAD_LIBS_INIT} )