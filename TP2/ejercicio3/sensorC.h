//
// Created by Usuario on 16/09/2024.
//

#ifndef SENSORC_H
#define SENSORC_H
#include "sensor.h"
#include "medicion.h"

class SensorC : public Sensor {
public:
    SensorC(int id, const std::string &ipAddress);
    Medicion medir() override;
};
#endif //SENSORC_H
