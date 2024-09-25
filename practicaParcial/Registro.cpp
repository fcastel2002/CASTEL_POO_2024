//
// Created by Usuario on 24/09/2024.
//

#include "Registro.h"

Registro::Registro() {
    m_altura = static_cast<float> (rand() % 300 + 100);
    m_velocidad = static_cast<float> (rand() % 50 + 100);
    m_tiempo = static_cast<float> (rand() % 60 );
    m_direccion = generarDireccion();
}

std::string Registro::generarDireccion() const {
    std::string direcciones[] = {"Norte", "Sur", "Este", "Oeste"};
    return direcciones[rand() % 4];
}