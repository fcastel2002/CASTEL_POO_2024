//
// Created by Usuario on 16/09/2024.
//

#include "sensorC.h"
#include <cstdlib>
#include <ctime>

SensorC::SensorC(const int id, const std::string &ipAddress) : Sensor(id, ipAddress) {
    std::srand (static_cast <unsigned int> (std::time(nullptr)));
}

Medicion SensorC::medir() {

    Medicion m("C", m_id, m_ipAddress);

    double anemometer {0.0 + static_cast <double> (std::rand()) / RAND_MAX * 100.0};
    m.addData("anemometer", anemometer);

    return m;
}