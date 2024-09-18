//
// Created by Usuario on 15/09/2024.
//

#ifndef SENSORA_H
#define SENSORA_H
#include "sensor.h"
#include "medicion.h"

class SensorA : public Sensor {

public:
    SensorA(int id, const std::string &ipAddress);
    Medicion medir() override;
};
#endif //SENSORA_H
