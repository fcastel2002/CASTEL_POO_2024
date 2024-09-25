#include <iostream>
#include "Dron.h"
#include "Reporte.h"
int main(void) {

    Dron dron1(59);
    Reporte reporte1("No.\tAltura\tVelocidad\tTiempo\tDireccion");


    for (int i = 0; i < 10; i++) {
        dron1.addRegistro(Registro());
    }
    reporte1.listar(dron1.getRegistros());

}