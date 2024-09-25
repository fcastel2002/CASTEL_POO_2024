//
// Created by Usuario on 24/09/2024.
//

#ifndef DRON_H
#define DRON_H

#include "Registro.h"
#include <vector>
class Dron {
private:
    int m_id {};
    std::vector<Registro> m_registros;
public:
    explicit Dron(int id) : m_id {id} {}
    void addRegistro(const Registro& registro);

    const std::vector<Registro> &getRegistros() const;
    int getId() const;
};



#endif //DRON_H
