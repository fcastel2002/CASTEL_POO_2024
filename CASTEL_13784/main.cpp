#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

class ElementoUnion;
class Tornillo;
class Tuerca;
class GestorMateriales;
class MostrarTabla;

class ElementoUnion {
protected:
    std::string sistema {};
    std::string material {};
    double pesoUnitario {};

public:
    ElementoUnion(const std::string &sistema, const std::string &material, double pesoUnitario)
    : sistema{sistema}
    , material{material}
    , pesoUnitario{pesoUnitario} {}
    virtual ~ElementoUnion() = default;

    std::string getMaterial() const {
        return material;
    }
    std::string getSistema() const {
        return sistema;
    }
    double getPesoUnitario() const {
        return pesoUnitario;
    }
};

class Tornillo : public ElementoUnion {
private:

    std::string tipoCabeza {};
    double diametro {};
    double largo {};
    std::string paso {};

public:
    Tornillo(std::string &sistema, std::string &material, double pesoUnitario, std::string &tipoCabeza, double diametro, double largo, std::string &paso)
    : ElementoUnion(sistema, material, pesoUnitario)
    , tipoCabeza{tipoCabeza}
    , diametro{diametro}
    , largo{largo}
    , paso{paso} {}

    std::string getTipoCabeza() const {
        return tipoCabeza;
    }
    double getDiametro() const {
        return diametro;
    }
    double getLargo() const {
        return largo;
    }
    std::string getPaso() const {
        return paso;
    }

};

class Tuerca : public ElementoUnion {
private:
    double diametro {};
    std::string paso {};
    bool autofrenante {};
    std::string tipoApriete {};

public:
    Tuerca(std::string &sistema, std::string &material, double pesoUnitario, double diametro, std::string &paso, bool autofrenante, std::string &tipoApriete)
        : ElementoUnion(sistema, material, pesoUnitario)
        , diametro{diametro}
        , paso{paso}
        , autofrenante{autofrenante}
        , tipoApriete{tipoApriete} {}

    double getDiametro() const {
        return diametro;
    }
    std::string getPaso() const {
        return paso;
    }
    bool getAutofrenante() const {
        return autofrenante;
    }
    std::string getTipoApriete() const {
        return tipoApriete;
    }


};



class GestorMateriales {
private:
    std::vector <ElementoUnion*> elementos;
    std::vector<Tornillo> tornillos;
    std::vector<Tuerca> tuercas;
public:
    void asignarMateriales( const std::string &filename);
    void mostrarMateriales() const;
    double calcularPesoTornillosInoxidables() const;
    int contarTuercasInoxidables() const;
    ~GestorMateriales() {
        for (auto& elemento : elementos) {
            delete elemento;
        }
    }
};

void GestorMateriales::asignarMateriales(const std::string &filename) {
    std::ifstream file(filename);
    std::string linea, palabra;
    int contadorLineas = 0;
    if (!file.is_open()) {
        std::cerr << "Error al abrir el archivo" << std::endl;
    }

    while(std::getline(file,palabra)) {
        std::stringstream ss(linea);
        std::vector <std::string> fila;
        contadorLineas++;
        if (contadorLineas == 1) {
            continue;
        }
        while(std::getline(ss, palabra, ',')) {
            fila.push_back(palabra);
        }
        if (fila[0] == "Tornillo") {
            Tornillo* tornillo = new Tornillo(
                fila[1], // Sistema
                fila[2], //Material
                std::stod(fila[7]), // Peso unitario
                fila[3], //Tipo cabeza
                std::stod(fila[4]), //Diametro
                std::stod(fila[5]), //Largo
                fila[6]
                );
            elementos.push_back(tornillo);// Paso
        }
        else if (fila[0] == "Tuerca") {

            Tuerca* tuerca = new Tuerca(
                fila[1], // Sistema
                fila[2], //Material
                std::stod(fila[7]), // Peso unitario
                std::stod(fila[6]),
                fila[6],
                (fila[5] == "1") ? true : false,
                fila[4]
            );
            elementos.push_back(tuerca);
        }

    }

}

double GestorMateriales::calcularPesoTornillosInoxidables() const {
    double pesoTotal = 0;
    for (const auto& tornillo : tornillos) {
        if (tornillo.getMaterial() == "Inoxidable") {
            pesoTotal += tornillo.getPesoUnitario();
        }
    }
    return pesoTotal;
}

// Función que cuenta la cantidad de tuercas inoxidables
int GestorMateriales::contarTuercasInoxidables() const {
    int cantidadInoxidables = 0;
    for (const auto& tuerca : tuercas) {
        if (tuerca.getMaterial() == "Inoxidable") {
            cantidadInoxidables++;
        }
    }
    return cantidadInoxidables;
}

class MostrarTabla {
public:
     static void mostrarTornillos(const std::vector<Tornillo> &tornillos);
     static void mostrarTuercas( const std::vector<Tuerca> &tuercas);
};

void MostrarTabla::mostrarTornillos(const std::vector<Tornillo> &tornillos) {
    std::cout << "Tabla de tornillos" << std::endl;
    std::cout << "Sistema\tMaterial\tPeso unitario\tTipo cabeza\tDiametro\tLargo\tPaso" << std::endl;
    for (const auto &tornillo : tornillos) {
        std::cout << tornillo.getSistema()
        << "\t" << tornillo.getMaterial()
        << "\t" << tornillo.getPesoUnitario()
        << "\t" << tornillo.getTipoCabeza()
        << "\t" << tornillo.getDiametro()
        << "\t" << tornillo.getLargo()
        << "\t" << tornillo.getPaso() << std::endl;
    }
}

     void MostrarTabla::mostrarTuercas( const std::vector<Tuerca> &tuercas) {
        std::cout << "Tabla de tuercas" << std::endl;
        std::cout << "Sistema\tMaterial\tPeso unitario\tDiametro\tPaso\tAutofrenante\tTipo apriete" << std::endl;
        for (const auto &tuerca : tuercas) {
            std::cout << tuerca.getSistema()
            << "\t" << tuerca.getMaterial()
            << "\t" << tuerca.getPesoUnitario()
            << "\t" << tuerca.getDiametro()
            << "\t" << tuerca.getPaso()
            << "\t" << tuerca.getAutofrenante()
            << "\t" << tuerca.getTipoApriete() << std::endl;
        }
    }


void GestorMateriales::mostrarMateriales() const {
    MostrarTabla::mostrarTornillos(tornillos);
    MostrarTabla::mostrarTuercas(tuercas);
}


int main() {
    GestorMateriales gestor;
    gestor.asignarMateriales("material.csv");
    gestor.mostrarMateriales();
    std::cout << "Peso total de tornillos inoxidables: " << gestor.calcularPesoTornillosInoxidables() << std::endl;
    std::cout << "Cantidad de tuercas inoxidables: " << gestor.contarTuercasInoxidables() << std::endl;
    return 0;
}
