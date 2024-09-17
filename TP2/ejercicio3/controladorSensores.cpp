//
// Created by Usuario on 16/09/2024.
//

#include "controladorSensores.h"
#include "sensorA.h"
#include "sensorB.h"
#include "sensorC.h"
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <chrono>

#include "consoleLogger.h"

ControladorSensores::ControladorSensores(std::shared_ptr<Logger> logger) : m_logger{logger}{}


bool ControladorSensores::cargarSensores(const std::string &cfgNombreArchivo) {
    std::ifstream configFile{cfgNombreArchivo};
    if(!configFile.is_open()) {
        m_logger->logMessage("Error al abrir el archivo de configuración");

        return false;
    }

    char tipoSensor{};
    int id{};
    std::string ipAddress{};

    while(configFile >> tipoSensor >> id >> ipAddress) {
        Sensor* sensor = nullptr;
        if (tipoSensor == 'A') {
            sensor = new SensorA(id, ipAddress);
        } else if (tipoSensor == 'B') {
            sensor = new SensorB(id, ipAddress);
        } else if (tipoSensor == 'C') {
            sensor = new SensorC(id, ipAddress);
        }
        if(sensor) {
            sensores.push_back(sensor);
        }
    }
    configFile.close();
    m_logger->logMessage("Sensores cargados");
    return true;
}

bool ControladorSensores::recolectarMedidas() {
    if (sensores.empty()) {
        m_logger->logMessage("Error: no hay sensores cargados");
        return false;
    }
    for(auto *sensor : sensores) {
        Medicion m{sensor->medir()};
        mediciones.push_back(m);
    }
    m_logger->logMessage("Mediciones recolectadas");
    return true;
}


void ControladorSensores::mostrarMediciones() const {
    //const std::vector<Medicion> ultimasMediciones {obtenerUltimasMediciones()};

    m_logger->logMediciones(mediciones);

}
ControladorSensores::~ControladorSensores() {
    for (auto *sensor : sensores) {
        delete sensor;
    }
}