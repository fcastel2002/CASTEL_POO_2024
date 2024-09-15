//
// Created by Usuario on 15/09/2024.
//

#ifndef SENSOR_H
#define SENSOR_H
#include <string>
#include <string_view>
class Medicion; //declaracion adelantada porque medir() retorna un objeto de tipo Medicion

class Sensor { //clase abstracta

public:

    Sensor(int id, std::string  ipAddres) : m_id{id}, m_ipAddress{std::move(ipAddres)} {};
    virtual ~Sensor() = default;

    virtual Medicion medir() = 0; //metodo virtual para realizar una medicion
    int getId() const { return m_id; }
    std::string_view getIpAddress() const { return m_ipAddress; }

protected:
    int m_id{};
    std::string m_ipAddress{};

};
#endif //SENSOR_H
