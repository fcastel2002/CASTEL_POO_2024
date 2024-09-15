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
    Medicion(std::string type, int sensorId);
    void addData(const std::string &key, double data);
    double getData(const std::string &key) const;
    std::chrono::system_clock::time_point getTime() const;
    std::string_view getType() const;
    int getSensorId() const;
private:
    std::map<std::string, double> m_data;  //asociamos string (key) a valores de tipo double
    std::chrono::system_clock::time_point m_time; //tiempo en que se realizo la medicion
    std::string m_type; //tipo de medicion
    int m_sensorId;

};
#endif //MEDICION_H
