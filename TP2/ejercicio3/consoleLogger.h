//
// Created by Usuario on 17/09/2024.
//

#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H
#include "logger.h"
#include <iostream>
#include <vector>

class ConsoleLogger final : public Logger {
public:
    void logMediciones(const std::vector<Medicion> &mediciones) const override {
        std::cout << "Tipo\tID\tIP\t\tTemperatura\tHumedad\tPresion\tLumens\tRadiacion UV\tViento\n" << std::endl;
        for (const auto& m : mediciones) {
            std::cout << m.getType() << "\t";
            std::cout << m.getSensorId() << "\t";

            // getData recibe las keys y devuelve el valor asociado a esa key

            std::cout << m.getIpAddress() << "\t";
            std::cout << m.getData("temperature") << "\t\t";
            std::cout << m.getData("humidity") << "\t";
            std::cout << m.getData("pressure") << "\t";
            std::cout << m.getData("lumens") << "\t";
            std::cout << m.getData("radiacionUV") << "\t\t";
            std::cout << m.getData("anemometer") << std::endl;
        }
    }
    void logMessage(const std::string &mensaje) const override {
        std::cout << mensaje << std::endl;
    }
};
#endif //CONSOLELOGGER_H
