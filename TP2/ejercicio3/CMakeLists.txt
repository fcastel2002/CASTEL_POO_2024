cmake_minimum_required(VERSION 3.29)
project(ejercicio3)
set(CMAKE_CXX_STANDARD 23)
include_directories(ejercicio3)
add_executable(ej3 sensor.cpp sensor.h
        medicion.cpp
        medicion.h
        sensorA.cpp
        sensorA.h
        sensorB.cpp
        sensorB.h)
