    //
// Created by Usuario on 15/09/2024.
//

#ifndef MEDICION_H
#define MEDICION_H
#include <string>
#include <string_view>
#include <map>
#include <chrono>

class Medicion {
public:
    Medicion(std::string type, int sensorId, std::string ipAddress);
    void addData(const std::string &key, double data);
    [[nodiscard]] double getData(const std::string &key) const;
    [[nodiscard]] std::chrono::system_clock::time_point getTime() const;
    [[nodiscard]] std::string_view getType() const;
    [[nodiscard]] std::string_view getIpAddress() const;
    [[nodiscard]] int getSensorId() const;
private:
    std::map<std::string, double> m_data;  //asociamos string (key) a valores de tipo double
    std::chrono::system_clock::time_point m_time; //tiempo en que se realizo la medicion
    std::string m_type{}; //tipo de medicion
    int m_sensorId{};
    std::string m_ipAddress{};

};
#endif //MEDICION_H
