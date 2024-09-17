//
// Created by Usuario on 11/09/2024.
//

#ifndef CSVPARSER_H
#define CSVPARSER_H
#include <string>
#include <vector>

/**
 * @class CSVParser
 * @brief Clase para leer y almacenar datos de archivos CSV.
 */
class CSVParser{
private:
  std::vector<std::vector<std::string>> data; ///< Estructura de datos para almacenar el contenido del archivo CSV.
public:
  /**
   * @brief Lee un archivo CSV y almacena su contenido en la estructura de datos interna.
   *
   * @param nombreArchivo El nombre del archivo CSV a leer.
   * @throws std::runtime_error Si no se puede abrir el archivo.
   */
  void leerArchivo(const std::string &nombreArchivo);

  /**
   * @brief Obtiene los datos leídos del archivo CSV.
   *
   * @return Una referencia constante a un vector de vectores de cadenas que contiene los datos del archivo CSV.
   */
  const std::vector<std::vector<std::string>> &obtenerDatos() const; //const al inicio porque lo que devuelve no puede ser modificado
};

#endif //CSVPARSER_H