//
// Created by Usuario on 11/09/2024.
//

#include "controlador.h"
#include "csvParser.h"
#include "xmlWriter.h"
#include <iostream>
#include <stdexcept>

void Controlador::ejecutar(const std::vector<std::string>& archivosCSV){
  for(const std::string &archivo : archivosCSV){
    try{
      CSVParser parser;
      parser.leerArchivo(archivo);
      XMLWriter::escribirXML(archivo + ".xml", parser.obtenerDatos());
    }catch(const std::runtime_error &e){
      std::cerr << "Error: " << e.what() << std::endl;
    }
  }
}