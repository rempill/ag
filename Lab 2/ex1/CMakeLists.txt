cmake_minimum_required(VERSION 3.28.3)
project(nicer)

set(CMAKE_CXX_STANDARD 20)
add_executable(nicer main.cpp)
set_target_properties(nicer PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
