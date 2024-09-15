//
// Created by Usuario on 11/09/2024.
//
#include "controlador.h"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]){
  if(argc < 2){
    std::cerr << "Error: Debe ingresar al menos un archivo CSV" << std::endl;
    return 1;
  }
  std::vector<std::string> archivosCSV;
  for(int i = 1; i < argc; i++){
    archivosCSV.emplace_back(argv[i]);
  }
  Controlador controlador;
  controlador.ejecutar(archivosCSV);
  return 0;
}