//
// Created by Usuario on 11/09/2024.
//

#ifndef CSVPARSER_H
#define CSVPARSER_H
#include <string>
#include <vector>

class CSVParser{
private:
  std::vector<std::vector<std::string>> data;
public:
  void leerArchivo(const std::string &nombreArchivo);
  const std::vector<std::vector<std::string>> &obtenerDatos() const; //const al inicio porque lo que devuelve no puede ser modificado

};
#endif //CSVPARSER_H
