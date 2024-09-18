//
// Created by Usuario on 15/09/2024.
//

#include "medicion.h"

#include <utility>

/**
 * @brief Constructor de la clase Medicion.
 *
 * @param type Tipo de la medición.
 * @param sensorId ID del sensor.
 * @param ipAddress Dirección IP del sensor.
 */
Medicion::Medicion(std::string type, const int sensorId, std::string ipAddress)
    : m_time{std::chrono::system_clock::now()}, m_type{std::move(type)}, m_sensorId{sensorId}, m_ipAddress{std::move(ipAddress)} {}

/**
 * @brief Añade un dato a la medición.
 *
 * @param key Clave del dato.
 * @param data Valor del dato.
 */
void Medicion::addData(const std::string &key, const double data) {
    m_data[key] = data;
}

/**
 * @brief Obtiene un dato de la medición.
 *
 * @param key Clave del dato.
 * @return Valor del dato asociado a la clave, o 0.0 si no se encuentra.
 */
double Medicion::getData(const std::string &key) const {
    if (const auto it = m_data.find(key); it != m_data.end()) {
        return it->second;
    }
    return 0.0;
}

/**
 * @brief Obtiene el tiempo de la medición.
 *
 * @return Punto en el tiempo en que se realizó la medición.
 */
std::chrono::system_clock::time_point Medicion::getTime() const {
    return m_time;
}

/**
 * @brief Obtiene el tipo de la medición.
 *
 * @return Tipo de la medición.
 */
std::string_view Medicion::getType() const {
    return m_type;
}

/**
 * @brief Obtiene el ID del sensor.
 *
 * @return ID del sensor.
 */
int Medicion::getSensorId() const {
    return m_sensorId;
}

/**
 * @brief Obtiene la dirección IP del sensor.
 *
 * @return Dirección IP del sensor.
 */
std::string_view Medicion::getIpAddress() const {
    return m_ipAddress;
}