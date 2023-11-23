cmake_minimum_required(VERSION 3.26)
project(Projeto_de_C C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Projeto_de_C
        despesa.c
        despesa.h
        primo_rico.c
        utilitario.h
        utilitario.c
        utilitario.c)
