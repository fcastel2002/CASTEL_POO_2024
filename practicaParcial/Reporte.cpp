//
// Created by Usuario on 24/09/2024.
//

#include "Reporte.h"

#include "Dron.h"

void Reporte::listar(const std::vector<Registro> &registro) const {
    std::cout << m_encabezado << std::endl;
    std::cout << "No.\tAltura\tVelocidad\tTiempo\tDireccion" << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    int num = 1;
    for (const auto &r : registro) {
        std::cout << num++ << "\t" << r.getAltura() << "\t" << r.getVelocidad() << "\t\t" << r.getTiempo() << "\t" << r.getDireccion() << std::endl;
    }
}
