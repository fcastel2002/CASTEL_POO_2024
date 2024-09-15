//
// Created by Usuario on 15/09/2024.
//

#ifndef SENSORB_H
#define SENSORB_H
#include "sensor.h"
#include "medicion.h"

class SensorB : public Sensor {

public:
    SensorB(int id, const std::string &ipAddress);
    Medicion medir() override;
};
#endif //SENSORB_H
