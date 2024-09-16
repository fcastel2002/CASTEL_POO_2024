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

std::string ControladorSensores::cargarSensores(const std::string &cfgNombreArchivo) {
    std::ifstream configFile{cfgNombreArchivo};
    if(!configFile.is_open()) {
        return "Error al abrir el archivo de configuración";
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
    return "SENSORES CARGADOS";
}

std::string ControladorSensores::recolectarMedidas() {
    if (sensores.empty()) {
        return "ERROR: NO HAY SENSORES CARGADOS";
    }
    for(auto *sensor : sensores) {
        Medicion m{sensor->medir()};
        mediciones.push_back(m);
    }
    return "MEDICIONES RECOLECTADAS";
}
std::vector<Medicion> ControladorSensores::obtenerMediciones() const {
    std::vector <Medicion> ultimasMediciones;
    const auto now {std::chrono::system_clock::now()};
    for (const auto& m : mediciones) {
        auto diff{std::chrono::duration_cast<std::chrono::seconds>(now - m.getTime())};
        if (diff.count() <= 5) {
            ultimasMediciones.push_back(m);
        }
    }
    return ultimasMediciones;
}

void ControladorSensores::mostrarMediciones() const {
    //const std::vector<Medicion> ultimasMediciones {obtenerUltimasMediciones()};
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
ControladorSensores::~ControladorSensores() {
    for (auto *sensor : sensores) {
        delete sensor;
    }
}