//
// Created by Usuario on 11/09/2024.
//

#include "csvParser.h"
#include <fstream>
#include <sstream>
#include <stdexcept>


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

const std::vector<std::vector<std::string>> &CSVParser::obtenerDatos() const{
  return data;
}