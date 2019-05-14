# cmake_minimum_required(VERSION <specify CMake version here>)
project(fundamentos2 C)

set(CMAKE_C_STANDARD 99)

add_executable(fundamentos2 boletin3/main.c boletin3/function/Component.h boletin3/function/Item.h boletin3/function/Component.c boletin3/function/Item.c boletin3/model/structs.h)