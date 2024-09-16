//
// Created by Usuario on 15/09/2024.
//

#include "sensorB.h"
#include <cstdlib>
#include <ctime>

SensorB::SensorB(const int id, const std::string &ipAddress) : Sensor(id, ipAddress) {
    std::srand (static_cast <unsigned int> (std::time(nullptr)));
}

Medicion SensorB::medir() {

    Medicion m("B", m_id, m_ipAddress);

    int lumens {90000 + std::rand() % 10000};
    int radiacionUV {0 + std::rand() % 15}; //indice uv
    m.addData("lumens", lumens);
    m.addData("radiacionUV", radiacionUV);

    return m;
}
