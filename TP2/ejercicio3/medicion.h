//
// Created by Usuario on 15/09/2024.
//

#ifndef MEDICION_H
#define MEDICION_H
#include <string>
#include <string_view>
#include <map>
#include <chrono>

/**
 * @brief Clase Medicion.
 *
 * Esta clase representa una medición realizada por un sensor.
 */
class Medicion {
public:
    /**
     * @brief Constructor de la clase Medicion.
     *
     * @param type Tipo de la medición.
     * @param sensorId ID del sensor.
     * @param ipAddress Dirección IP del sensor.
     */
    Medicion(std::string type, int sensorId, std::string ipAddress);

    /**
     * @brief Añade un dato a la medición.
     *
     * @param key Clave del dato.
     * @param data Valor del dato.
     */
    void addData(const std::string &key, double data);

    /**
     * @brief Obtiene un dato de la medición.
     *
     * @param key Clave del dato.
     * @return Valor del dato asociado a la clave, o 0.0 si no se encuentra.
     */
    [[nodiscard]] double getData(const std::string &key) const;

    /**
     * @brief Obtiene el tiempo de la medición.
     *
     * @return Punto en el tiempo en que se realizó la medición.
     */
    [[nodiscard]] std::chrono::system_clock::time_point getTime() const;

    /**
     * @brief Obtiene el tipo de la medición.
     *
     * @return Tipo de la medición.
     */
    [[nodiscard]] std::string_view getType() const;

    /**
     * @brief Obtiene la dirección IP del sensor.
     *
     * @return Dirección IP del sensor.
     */
    [[nodiscard]] std::string_view getIpAddress() const;

    /**
     * @brief Obtiene el ID del sensor.
     *
     * @return ID del sensor.
     */
    [[nodiscard]] int getSensorId() const;

private:
    std::map<std::string, double> m_data;  ///< Mapa que asocia claves (string) a valores de tipo double.
    std::chrono::system_clock::time_point m_time; ///< Tiempo en que se realizó la medición.
    std::string m_type{}; ///< Tipo de medición.
    int m_sensorId{}; ///< ID del sensor.
    std::string m_ipAddress{}; ///< Dirección IP del sensor.
};

#endif //MEDICION_H