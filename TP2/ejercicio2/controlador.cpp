//
// Created by Usuario on 11/09/2024.
//

#include "controlador.h"
#include "csvParser.h"
#include "xmlWriter.h"
#include <iostream>
#include <stdexcept>

/**
 * @brief Ejecuta el proceso de lectura de archivos CSV y escritura de su contenido en archivos XML.
 *
 * Esta función itera sobre una lista de rutas de archivos CSV, lee cada archivo usando CSVParser,
 * y escribe los datos analizados en un archivo XML usando XMLWriter. Si ocurre un error durante
 * el proceso, captura la excepción e imprime un mensaje de error.
 *
 * @param archivosCSV Un vector de cadenas que contiene las rutas de los archivos CSV a procesar.
 */
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