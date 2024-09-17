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

/**
 * @brief Clase ControladorSensores.
 *
 * Esta clase se encarga de gestionar los sensores y sus mediciones.
 */
class ControladorSensores {

public:
    /**
     * @brief Carga los sensores desde un archivo de configuración.
     *
     * @param cfgNombreArchivo El nombre del archivo de configuración.
     * @return true si los sensores se cargaron correctamente, false en caso contrario.
     */
    bool cargarSensores(const std::string &cfgNombreArchivo);

    /**
     * @brief Recolecta las mediciones de todos los sensores cargados.
     *
     * @return true si las mediciones se recolectaron correctamente, false en caso contrario.
     */
    bool recolectarMedidas();

    /**
     * @brief Obtiene las mediciones recolectadas.
     *
     * @return Un vector de objetos Medicion que contiene las mediciones recolectadas.
     */
    std::vector<Medicion> obtenerMediciones() const;

    /**
     * @brief Muestra las mediciones recolectadas.
     */
    void mostrarMediciones() const;

    /**
     * @brief Constructor de la clase ControladorSensores.
     *
     * @param logger Puntero compartido a una instancia de Logger.
     */
    explicit ControladorSensores(std::shared_ptr<Logger> logger);

    /**
     * @brief Destructor de la clase ControladorSensores.
     *
     * Elimina todos los sensores asignados dinámicamente.
     */
    ~ControladorSensores();

private:
    std::vector<Sensor*> sensores; ///< Colección de sensores
    std::vector<Medicion> mediciones; ///< Colección de mediciones
    std::shared_ptr<Logger> m_logger; ///< Puntero compartido a una instancia de Logger
};

#endif //CONTROLADORSENSORES_H