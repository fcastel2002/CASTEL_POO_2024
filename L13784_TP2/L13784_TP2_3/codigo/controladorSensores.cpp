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

/**
 * @brief Constructor for ControladorSensores.
 *
 * @param logger Shared pointer to a Logger instance.
 */
ControladorSensores::ControladorSensores(std::shared_ptr<Logger> logger) : m_logger{logger}{}

/**
 * @brief Loads sensors from a configuration file.
 *
 * @param cfgNombreArchivo The name of the configuration file.
 * @return true if the sensors were loaded successfully, false otherwise.
 */
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
        switch (tipoSensor) {
            case 'A': sensor = new SensorA(id, ipAddress); break;
            case 'B': sensor = new SensorB(id, ipAddress); break;
            case 'C': sensor = new SensorC(id, ipAddress); break;
            default: m_logger->logMessage("Error: tipo de sensor desconocido"); break;
        }
        if(sensor) {
            sensores.push_back(sensor);
        }
    }
    configFile.close();
    m_logger->logMessage("Sensores cargados");
    return true;
}

/**
 * @brief Collects measurements from all loaded sensors.
 *
 * @return true if measurements were collected successfully, false otherwise.
 */
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

/**
 * @brief Displays the collected measurements.
 */
void ControladorSensores::mostrarMediciones() const {
    //const std::vector<Medicion> ultimasMediciones {obtenerUltimasMediciones()};
    m_logger->logMediciones(mediciones);
}

/**
 * @brief Destructor for ControladorSensores.
 *
 * Deletes all dynamically allocated sensors.
 */
ControladorSensores::~ControladorSensores() {
    for (auto *sensor : sensores) {
        delete sensor;
    }
}