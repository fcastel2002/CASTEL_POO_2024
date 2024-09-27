cmake_minimum_required(VERSION 3.28.6)
project(L13784_TP2_3)
set(CMAKE_CXX_STANDARD 23)
include_directories(codigo)
add_executable(L13784_TP2_3 sensor.h
        medicion.cpp
        medicion.h
        sensorA.cpp
        sensorA.h
        sensorB.cpp
        sensorB.h
        sensorC.cpp
        sensorC.h
        controladorSensores.cpp
        controladorSensores.h
        main.cpp
        logger.h
        consoleLogger.h)
add_executable(genera_cfg cfgFile.cpp)
