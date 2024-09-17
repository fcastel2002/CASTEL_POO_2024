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
#include "logger.h"

class ControladorSensores {

public:

    bool cargarSensores(const std::string &cfgNombreArchivo);
    bool recolectarMedidas();
    std::vector<Medicion> obtenerMediciones() const;
    void mostrarMediciones() const;

    explicit ControladorSensores(std::shared_ptr<Logger> logger);

    ~ControladorSensores();

private:
    std::vector<Sensor*> sensores; //collecion de sensores
    std::vector<Medicion> mediciones; //colección de mediciones
    std::shared_ptr<Logger> m_logger;
};
#endif //CONTROLADORSENSORES_H
