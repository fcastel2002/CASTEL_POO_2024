cmake_minimum_required(VERSION 3.29)
project(ejercicio2)

set(CMAKE_CXX_STANDARD 23)

include_directories(ejercicio2)

add_executable(EJ2_castel
        csvParser.cpp
        csvParser.h
        main.cpp
        xmlWriter.cpp
        xmlWriter.h
        controlador.cpp
        controlador.h)
