cmake_minimum_required(VERSION 3.0)
project(Algorithms)

set(CMAKE_CXX_STANDARD 20)
add_definitions(-Werror -Wall -Wextra -pedantic -O2)

add_subdirectory(Geil-Shapley)
include_directories(Geil-Shapley)

add_executable(algorithms main.cpp)
target_link_libraries(algorithms Geil-Shapley)