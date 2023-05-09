cmake_minimum_required(VERSION 3.25)
project(Projeto_Continente C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Projeto_Continente
        filesFunctions.h
        clients.h
        employee.h
        eventHorizon.h
        checkout.h
        checkoutList.h
        functions.h
        genericList.h
        main.c)
