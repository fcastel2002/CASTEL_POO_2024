//
// Created by Usuario on 16/09/2024.
//

#ifndef CONTROLADORSENSORES_H
#define CONTROLADORSENSORES_H
#include <vector>
#include <string>
#include <string_view>
#include "sensor.h"
#include "medicion.h"

class ControladorSensores {

public:

    std::string cargarSensores (const std::string &cfgNombreArchivo);
    std::string recolectarMedidas();
    std::vector<Medicion> obtenerMediciones() const;
    void mostrarMediciones() const;

    ~ControladorSensores();

private:
    std::vector<Sensor*> sensores; //collecion de sensores
    std::vector<Medicion> mediciones; //colección de mediciones

};
#endif //CONTROLADORSENSORES_H
