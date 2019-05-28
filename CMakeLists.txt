# cmake_minimum_required(VERSION <specify CMake version here>)
project(fundamentos2 C)

set(CMAKE_C_STANDARD 99)

add_executable(fundamentos2 boletin4/exercise2/main.c boletin4/exercise2/model/structs.h boletin4/exercise2/functions/City.c boletin4/exercise2/functions/City.h)