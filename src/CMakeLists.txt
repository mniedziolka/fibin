cmake_minimum_required(VERSION 3.15)
project(src)

set(CMAKE_CXX_STANDARD 17)
set( CMAKE_CXX_FLAGS "-Wall -Wextra -std=c++17 -O2 -lstdc++" )
add_executable(example fibin_example.cc)
