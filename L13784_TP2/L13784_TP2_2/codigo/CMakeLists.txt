cmake_minimum_required(VERSION 3.29.6)
project(L13784_TP2_2)

set(CMAKE_CXX_STANDARD 23)
include_directories(codigo)
add_executable(L13784_TP2_2
        controlador.cpp
        controlador.h
        main.cpp
        csvParser.cpp
        csvParser.h
        xmlWriter.cpp
        xmlWriter.h
        )