//
// Created by Usuario on 11/09/2024.
//

#ifndef CONTROLADOR_H
#define CONTROLADOR_H
#include <string>
#include <vector>

/**
 * @class Controlador
 * @brief Clase que maneja la ejecución del proceso de lectura de archivos CSV y escritura de su contenido en archivos XML.
 */
class Controlador {
public:
    /**
     * @brief Ejecuta el proceso de lectura de archivos CSV y escritura de su contenido en archivos XML.
     *
     * Esta función itera sobre una lista de rutas de archivos CSV, lee cada archivo usando CSVParser,
     * y escribe los datos analizados en un archivo XML usando XMLWriter. Si ocurre un error durante
     * el proceso, captura la excepción e imprime un mensaje de error.
     *
     * @param archivosCSV Un vector de cadenas que contiene las rutas de los archivos CSV a procesar.
     */
    void ejecutar(const std::vector<std::string>& archivosCSV);
};

#endif //CONTROLADOR_H