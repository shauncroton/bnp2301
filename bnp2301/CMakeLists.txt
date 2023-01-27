cmake_minimum_required(VERSION 3.22)
project(bnp)

set(CMAKE_CXX_STANDARD 20)
include_directories("${PROJECT_SOURCE_DIR}")

add_executable(median median/median.cpp median/median.hpp common.hpp)
add_executable(squares squares/squares.cpp common.hpp)
add_executable(coins coins/coins.cpp common.hpp)
add_executable(supersale supersale/supersale.cpp common.hpp)
