//
// Created by Usuario on 15/09/2024.
//

#include "sensorA.h"
#include <cstdlib>
#include <ctime>
#include <iostream>

SensorA::SensorA(const int id, const std::string &ipAddress) : Sensor(id, ipAddress) {
    std::srand (static_cast <unsigned int> (std::time(nullptr)));
}

Medicion SensorA::medir() {

    Medicion m("A", m_id, m_ipAddress);

    double temperature {15.0 + static_cast <double> (std::rand()) / RAND_MAX * 20.0};
    double humidity {50.0 + static_cast <double> (std::rand()) / RAND_MAX * 50.0};
    double pressure {1000.0 + static_cast <double> (std::rand()) / RAND_MAX * 50.0};
    m.addData("temperature", temperature);
    m.addData("humidity", humidity);
    m.addData("pressure", pressure);

    return m;
}