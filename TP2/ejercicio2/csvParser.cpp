//
// Created by Usuario on 11/09/2024.
//

#include "csvParser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

/**
 * @brief Lee un archivo CSV y almacena su contenido en la estructura de datos interna.
 *
 * Esta función abre un archivo CSV especificado por su nombre, lee cada línea del archivo,
 * y divide cada línea en valores separados por punto y coma (';'). Los valores se almacenan
 * en un vector de vectores de cadenas.
 *
 * @param nombreArchivo El nombre del archivo CSV a leer.
 * @throws std::runtime_error Si no se puede abrir el archivo.
 */
void CSVParser::leerArchivo(const std::string &nombreArchivo){
  std::ifstream archivo(nombreArchivo);
  if(!archivo.is_open()){
    throw std::runtime_error("No se pudo abrir el archivo");
  }
  std::string linea;
  while(std::getline(archivo, linea)){
    std::vector<std::string> fila;
    std::stringstream ss(linea);
    std::string valor;
    while(std::getline(ss, valor, ';')){
      fila.push_back(valor);
    }
    data.push_back(fila);
  }
  archivo.close();
}

/**
 * @brief Obtiene los datos leídos del archivo CSV.
 *
 * Esta función devuelve una referencia constante a la estructura de datos interna que contiene
 * los valores leídos del archivo CSV.
 *
 * @return Una referencia constante a un vector de vectores de cadenas que contiene los datos del archivo CSV.
 */
const std::vector<std::vector<std::string>> &CSVParser::obtenerDatos() const{
  return data;
}