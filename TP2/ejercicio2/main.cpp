//
// Created by Usuario on 11/09/2024.
//
#include "controlador.h"
#include <iostream>
#include <vector>

/**
 * @brief Punto de entrada principal de la aplicación.
 *
 * Esta función principal verifica que se haya proporcionado al menos un archivo CSV como argumento,
 * crea una instancia de la clase Controlador y ejecuta el proceso de lectura de archivos CSV y escritura
 * de su contenido en archivos XML.
 *
 * @param argc El número de argumentos de la línea de comandos.
 * @param argv Un arreglo de cadenas que contiene los argumentos de la línea de comandos.
 * @return Un entero que indica el estado de salida del programa (0 si se ejecuta correctamente, 1 si hay un error).
 */
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