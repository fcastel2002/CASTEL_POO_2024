//
// Created by Usuario on 11/09/2024.
//

#ifndef XMLWRITER_H
#define XMLWRITER_H
#include <string>
#include <vector>

/**
 * @class XMLWriter
 * @brief Clase para escribir datos en archivos XML.
 */
class XMLWriter {
public:
    /**
     * @brief Escribe datos en un archivo XML.
     *
     * Esta función toma un nombre de archivo y una estructura de datos, abre el archivo para escritura,
     * y escribe los datos en formato XML. Si no se puede abrir el archivo, lanza una excepción.
     *
     * @param nombreArchivo El nombre del archivo XML a escribir.
     * @param data Un vector de vectores de cadenas que contiene los datos a escribir en el archivo XML.
     * @throws std::runtime_error Si no se puede abrir el archivo.
     */
    static void escribirXML(const std::string &nombreArchivo, const std::vector<std::vector<std::string>> &data);
};

#endif //XMLWRITER_H