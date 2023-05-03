cmake_minimum_required(VERSION 3.25)
project(Projeto_Continente C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Projeto_Continente
        clients.h
        clientsInCheckout.h
        clientsInStore.h
        employee.h
        eventHorizon.h
        filesFunctions.h
        functions.h
        genericList.h
        main.c)
