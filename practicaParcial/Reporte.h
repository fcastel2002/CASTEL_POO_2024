//
// Created by Usuario on 24/09/2024.
//

#ifndef REPORTE_H
#define REPORTE_H

#include "Dron.h"
#include <vector>
#include <iostream>
class Reporte {
private:
    std::string m_encabezado {};
public:

    explicit Reporte(const std::string encabezado) : m_encabezado(encabezado) {}

    void listar(const std::vector<Registro> &registro) const;
};



#endif //REPORTE_H
