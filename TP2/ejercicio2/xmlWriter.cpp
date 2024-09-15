//
// Created by Usuario on 11/09/2024.
//

#include "xmlWriter.h"
#include <fstream>
#include <stdexcept>

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
