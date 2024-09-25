//
// Created by Usuario on 24/09/2024.
//

#include "Dron.h"

void Dron::addRegistro(const Registro &registro) {
    m_registros.push_back(registro);
}

const std::vector<Registro> &Dron::getRegistros() const {
    return m_registros;
}

int Dron::getId() const {
    return m_id;
}
