cmake_minimum_required(VERSION 3.31)
project(fallbox C)

set(CMAKE_C_STANDARD 11)

find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3)

add_executable(fallbox main.c
        cell.h
        cell.c
        game.h
        game.c)

target_link_libraries(fallbox PRIVATE SDL3::SDL3)
