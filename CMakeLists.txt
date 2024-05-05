cmake_minimum_required(VERSION 3.28)
project(Projeto_02 C)

set(CMAKE_C_STANDARD 11)

add_library(Projeto_02 STATIC library.c
        main.c)
