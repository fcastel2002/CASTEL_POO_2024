#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class ElementoUnion {
protected:
    std::string sistema;
    std::string material;
    double pesoUnitario;

public:
    ElementoUnion(const std::string &sistema, const std::string &material, double pesoUnitario)
    : sistema{sistema}, material{material}, pesoUnitario{pesoUnitario} {}

    virtual ~ElementoUnion() = default;

    std::string getMaterial() const { return material; }
    std::string getSistema() const { return sistema; }
    double getPesoUnitario() const { return pesoUnitario; }
};

class Tornillo : public ElementoUnion {
private:
    std::string tipoCabeza;
    double diametro;
    double largo;
    std::string paso;

public:
    Tornillo(const std::string &sistema, const std::string &material, double pesoUnitario,
             const std::string &tipoCabeza, double diametro, double largo, const std::string &paso)
    : ElementoUnion(sistema, material, pesoUnitario),
      tipoCabeza{tipoCabeza}, diametro{diametro}, largo{largo}, paso{paso} {}

    std::string getTipoCabeza() const { return tipoCabeza; }
    double getDiametro() const { return diametro; }
    double getLargo() const { return largo; }
    std::string getPaso() const { return paso; }
};

class Tuerca : public ElementoUnion {
private:
    double diametro;
    std::string paso;
    bool autofrenante;
    std::string tipoApriete;

public:
    Tuerca(const std::string &sistema, const std::string &material, double pesoUnitario,
           double diametro, const std::string &paso, bool autofrenante, const std::string &tipoApriete)
    : ElementoUnion(sistema, material, pesoUnitario),
      diametro{diametro}, paso{paso}, autofrenante{autofrenante}, tipoApriete{tipoApriete} {}

    double getDiametro() const { return diametro; }
    std::string getPaso() const { return paso; }
    bool getAutofrenante() const { return autofrenante; }
    std::string getTipoApriete() const { return tipoApriete; }
};

class GestorMateriales {
private:
    std::vector<Tornillo> tornillos;
    std::vector<Tuerca> tuercas;

public:
    void asignarMateriales(const std::string &filename);
    void mostrarMateriales() const;
};

void GestorMateriales::asignarMateriales(const std::string &filename) {
    std::ifstream file(filename);

    // Comprobación de la apertura del archivo
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << filename << std::endl;
        std::cerr << "Verifique la ruta del archivo o si existe." << std::endl;
        return;
    }

    std::string linea;
    int contadorLineas = 0;

    // Saltar las primeras tres líneas
    while (contadorLineas < 3 && std::getline(file, linea)) {
        contadorLineas++;
    }

    // Procesar el resto de las líneas
    while (std::getline(file, linea)) {
        std::stringstream ss(linea);
        std::vector<std::string> fila;
        std::string palabra;

        // Dividir la línea por comas
        while (std::getline(ss, palabra, ',')) {
            fila.push_back(palabra);
        }

        // Verificar si es un tornillo o tuerca
        if (fila[0] == "Tornillo") {
            Tornillo tornillo(
                fila[1],    // Sistema
                fila[2],    // Material
                std::stod(fila[7]),  // Peso unitario
                fila[3],    // Tipo de cabeza
                std::stod(fila[5]),  // Diámetro
                std::stod(fila[6]),  // Largo
                fila[4]     // Paso
            );
            tornillos.push_back(tornillo);
        }
        else if (fila[0] == "Tuerca") {
            bool autofrenante = (fila[3] == "Si" || fila[3] == "1");
            Tuerca tuerca(
                fila[1],    // Sistema
                fila[2],    // Material
                std::stod(fila[7]),  // Peso unitario
                std::stod(fila[6]),  // Diámetro
                fila[5],    // Paso
                autofrenante,  // Autofrenante
                fila[4]     // Tipo de apriete
            );
            tuercas.push_back(tuerca);
        }
    }
}

class MostrarTabla {
public:
    static void mostrarTornillos(const std::vector<Tornillo> &tornillos) {
        std::cout << "Tabla de Tornillos:\n";
        std::cout << "Sistema\tMaterial\tTipoCabeza\tDiametro\tLargo\tPaso\tPeso\n";
        for (const auto &tornillo : tornillos) {
            std::cout << tornillo.getSistema() << "\t"
                      << tornillo.getMaterial() << "\t"
                      << tornillo.getTipoCabeza() << "\t"
                      << tornillo.getDiametro() << "\t"
                      << tornillo.getLargo() << "\t"
                      << tornillo.getPaso() << "\t"
                      << tornillo.getPesoUnitario() << "\n";
        }
    }

    static void mostrarTuercas(const std::vector<Tuerca> &tuercas) {
        std::cout << "\nTabla de Tuercas:\n";
        std::cout << "Sistema\tMaterial\tAutofrenante\tTipoApriete\tDiametro\tPaso\tPeso\n";
        for (const auto &tuerca : tuercas) {
            std::cout << tuerca.getSistema() << "\t"
                      << tuerca.getMaterial() << "\t"
                      << (tuerca.getAutofrenante() ? "Si" : "No") << "\t"
                      << tuerca.getTipoApriete() << "\t"
                      << tuerca.getDiametro() << "\t"
                      << tuerca.getPaso() << "\t"
                      << tuerca.getPesoUnitario() << "\n";
        }
    }
};

void GestorMateriales::mostrarMateriales() const {
    MostrarTabla::mostrarTornillos(tornillos);
    MostrarTabla::mostrarTuercas(tuercas);
}

int main() {
    GestorMateriales gestor;
    gestor.asignarMateriales("material.csv");  // Cambia por la ruta correcta
    gestor.mostrarMateriales();

    return 0;
}
