//
// Created by Usuario on 16/09/2024.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

struct SensorCfg {
    char sensorType {};
    int id {};
    std::string ipAddress {};
};

std::string generarArchivoCfg(const std::string &cfgNombreArchivo, const std::vector <SensorCfg> &sensores) {
    std::ofstream archivo(cfgNombreArchivo);
    if (!archivo) {
        return "ERROR: No se pudo abrir el archivo.";
    }

    for (const auto&[sensorType, id, ipAddress] : sensores) {
        archivo << sensorType << " " << id << " " << ipAddress << std::endl;
    }
    archivo.close();
    return "ARCHIVO GENERADO CON ÉXITO";
}

int main() {
    std::vector <SensorCfg> sensores = {
            {'A', 1, "192.168.1.10"},
            {'B', 2, "192.168.1.11"},
            {'C', 3, "192.168.1.12"},
            {'A', 4, "192.168.1.13"},
            {'B', 5, "192.168.1.14"},
            {'C', 6, "192.168.1.16"}
            };
    generarArchivoCfg("sensores.cfg", sensores);
    return 0;
}