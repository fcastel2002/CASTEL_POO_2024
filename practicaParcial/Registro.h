//
// Created by Usuario on 24/09/2024.
//

#ifndef REGISTRO_H
#define REGISTRO_H
#include <string>
#include <cstdlib>
#include <ctime>

class Registro {
private:
    float m_altura {};
    float m_velocidad {};
    float m_tiempo {};
    std::string  m_direccion {};

    std::string generarDireccion() const;

public:



    float getAltura() const {
        return m_altura;
    }

    float getVelocidad() const {
        return m_velocidad;
    }

    float getTiempo() const {
        return m_tiempo;
    }

    std::string getDireccion() const {
        return m_direccion;
    }


    Registro();
};


#endif //REGISTRO_H
