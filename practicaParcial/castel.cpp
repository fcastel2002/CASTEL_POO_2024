#include <iostream>
#include "Dron.h"
#include "Reporte.h"
int main(void) {

    Dron dron1(59);
    Reporte reporte1("Reporte numero 1 del dron 59");
    Registro reg1;
    Registro reg2;

    dron1.addRegistro(reg1);
    dron1.addRegistro(reg2);
    reporte1.listar(dron1.getRegistros());

}