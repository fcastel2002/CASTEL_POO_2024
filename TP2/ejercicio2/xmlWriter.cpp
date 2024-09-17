//
// Created by Usuario on 11/09/2024.
//

#include "xmlWriter.h"
#include <fstream>
#include <stdexcept>

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
void XMLWriter::escribirXML(const std::string &nombreArchivo, const std::vector<std::vector<std::string> > &data) {
    std::ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo");
    }
    archivo <<"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    archivo << "<root>\n";

    for (const auto &fila : data) {
        archivo << "  <registro>\n";
        if (fila.size() > 0) archivo << "    <dispID>" << fila[0] << "</dispID>\n";
        if (fila.size() > 1) archivo << "    <apertura>" << fila[1] << "</apertura>\n";
        if (fila.size() > 2) archivo << "    <nivel>" << fila[2] << "</nivel>\n";
        if (fila.size() > 3) archivo << "    <caudal>" << fila[3] << "</caudal>\n";
        archivo << "  </registro>\n"; //se cierra el elemento registro
    }
    archivo << "</root>\n"; //se cierra el elemento root
    archivo.close();
}