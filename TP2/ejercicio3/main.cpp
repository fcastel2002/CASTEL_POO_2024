//
// Created by Usuario on 16/09/2024.
//
#include "controladorSensores.h"
#include "consoleLogger.h"
#include <iostream>
#include <thread>

int main() {
    const std::shared_ptr<Logger> consoleLogger = std::make_shared<ConsoleLogger>();
    ControladorSensores controlador(consoleLogger);

    controlador.cargarSensores("sensores.cfg");
    for (int i = 0; i < 5; ++i) {
        controlador.recolectarMedidas();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    controlador.mostrarMediciones();

    return 0;
}
