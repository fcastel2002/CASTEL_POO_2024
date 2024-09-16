//
// Created by Usuario on 15/09/2024.
//

#include "medicion.h"

#include <utility>

Medicion::Medicion(std::string type, const int sensorId, std::string ipAddress) : m_time{std::chrono::system_clock::now()}, m_type{std::move(type)},m_sensorId{sensorId}, m_ipAddress{std::move(ipAddress)} {}

void Medicion::addData(const std::string &key, const double data) {
    m_data[key] = data;
}
double Medicion::getData(const std::string &key) const {
    if (const auto it = m_data.find(key); it != m_data.end()) {
        return it->second;
    }
    return 0.0;
}
std::chrono::system_clock::time_point Medicion::getTime() const {
    return m_time;
}
std::string_view Medicion::getType() const {
    return m_type;
}
int Medicion::getSensorId() const {
    return m_sensorId;
}
std::string_view Medicion::getIpAddress() const {
    return m_ipAddress;
}