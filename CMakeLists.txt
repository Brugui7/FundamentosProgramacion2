# cmake_minimum_required(VERSION <specify CMake version here>)
project(fundamentos2 C)

set(CMAKE_C_STANDARD 99)

add_executable(fundamentos2 boletin2/main.c boletin2/model/Component.h boletin2/model/Item.h boletin2/function/Component.c boletin2/function/Item.c)