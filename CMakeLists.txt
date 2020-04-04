cmake_minimum_required(VERSION 3.0)
project(Algorithms)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-Werror -Wall -Wextra -pedantic -O2)

add_subdirectory(Geil-Shapley)
include_directories(Geil-Shapley)

add_library(algorithms SHARED algorithm.cpp)
target_link_libraries(algorithms GeilShapley)

add_executable(main main.cpp)
target_link_libraries(main algorithms)