cmake_minimum_required(VERSION 3.10)
project(my_console_utility)
set(CMAKE_C_STANDARD 11)

add_executable(my_console_utility main.c users.c processes.c)
