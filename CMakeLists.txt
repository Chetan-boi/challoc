cmake_minimum_required(VERSION 3.10)
project(challoc LANGUAGES C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_executable(challoc src/main.c)
target_include_directories(challoc PRIVATE include)
