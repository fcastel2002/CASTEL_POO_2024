#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>  // Para controlar la salida formateada

using namespace std;

/**
 * @class Archivo
 * @brief Clase para manejar la lectura de archivos.
 */
class Archivo {
private:
    ifstream archivo; ///< Stream de entrada para el archivo.
public:
    /**
     * @brief Constructor que abre un archivo.
     * @param nombreArchivo Nombre del archivo a abrir.
     */
    Archivo(const string& nombreArchivo) {
        archivo.open(nombreArchivo);
        if (!archivo.is_open()) {
            cerr << "Error al abrir el archivo: " << nombreArchivo << endl;
            exit(1);
        }
    }

    /**
     * @brief Destructor que cierra el archivo si está abierto.
     */
    ~Archivo() {
        if (archivo.is_open()) {
            archivo.close();
        }
    }

    /**
     * @brief Lee una línea del archivo.
     * @return La línea leída del archivo.
     */
    string leerLinea() {
        string linea;
        if (getline(archivo, linea)) {
            return linea;
        }
        else {
            return "";
        }
    }
};

/**
 * @class SistemaLuminoso
 * @brief Clase que representa un sistema luminoso.
 */
class SistemaLuminoso {
private:
    string estado; ///< Estado del sistema luminoso.
    float frecuencia; ///< Frecuencia del sistema luminoso.
    string color; ///< Color del sistema luminoso.
public:
    /**
     * @brief Constructor de la clase SistemaLuminoso.
     * @param estado Estado del sistema luminoso.
     * @param frecuencia Frecuencia del sistema luminoso.
     * @param color Color del sistema luminoso.
     */
    SistemaLuminoso(const string& estado, float frecuencia, const string& color)
        : estado(estado), frecuencia(frecuencia), color(color) {}

    /**
     * @brief Obtiene el estado del sistema luminoso.
     * @return Estado del sistema luminoso.
     */
    string getEstado() const { return estado; }

    /**
     * @brief Obtiene la frecuencia del sistema luminoso.
     * @return Frecuencia del sistema luminoso.
     */
    float getFrecuencia() const { return frecuencia; }

    /**
     * @brief Obtiene el color del sistema luminoso.
     * @return Color del sistema luminoso.
     */
    string getColor() const { return color; }
};

/**
 * @class Posicion
 * @brief Clase que representa una posición en el espacio.
 */
class Posicion {
private:
    float x, y, z; ///< Coordenadas X, Y, Z de la posición.
    int tiempoPermanencia; ///< Tiempo de permanencia en la posición.
public:
    /**
     * @brief Constructor de la clase Posicion.
     * @param x Coordenada X.
     * @param y Coordenada Y.
     * @param z Coordenada Z.
     * @param tiempo Tiempo de permanencia en la posición.
     */
    Posicion(float x, float y, float z, int tiempo)
        : x(x), y(y), z(z), tiempoPermanencia(tiempo) {}

    /**
     * @brief Obtiene la coordenada X.
     * @return Coordenada X.
     */
    float getX() const { return x; }

    /**
     * @brief Obtiene la coordenada Y.
     * @return Coordenada Y.
     */
    float getY() const { return y; }

    /**
     * @brief Obtiene la coordenada Z.
     * @return Coordenada Z.
     */
    float getZ() const { return z; }

    /**
     * @brief Obtiene el tiempo de permanencia en la posición.
     * @return Tiempo de permanencia en la posición.
     */
    int getTiempoPermanencia() const { return tiempoPermanencia; }
};

/**
 * @class Vuelo
 * @brief Clase que representa un vuelo, contiene posiciones y sistemas luminosos.
 */
class Vuelo {
private:
    vector<Posicion> posiciones; ///< Vector de posiciones del vuelo.
    vector<SistemaLuminoso> sistemasLuminosos; ///< Vector de sistemas luminosos del vuelo.
public:
    /**
     * @brief Agrega una posición al vuelo.
     * @param posicion La posición a agregar.
     */
    void agregarPosicion(const Posicion& posicion) {
        posiciones.push_back(posicion);
    }

    /**
     * @brief Agrega un sistema luminoso al vuelo.
     * @param sistema El sistema luminoso a agregar.
     */
    void agregarSistemaLuminoso(const SistemaLuminoso& sistema) {
        sistemasLuminosos.push_back(sistema);
    }

    /**
     * @brief Muestra los datos del vuelo en formato tabular.
     */
    void mostrarDatos() const {
        // Definir el ancho de cada columna
        const int anchoCoordenadas = 20;
        const int anchoTiempo = 12;
        const int anchoEstado = 10;
        const int anchoFrecuencia = 18;
        const int anchoColor = 10;

        // Imprimir la cabecera de la tabla
        cout << setw(anchoCoordenadas) << "Coordenadas (X,Y,Z)"
            << " | " << setw(anchoTiempo) << "Tiempo (s)"
            << " | " << setw(anchoEstado) << "Estado"
            << " | " << setw(anchoFrecuencia) << "Frecuencia (Hz)"
            << " | " << setw(anchoColor) << "Color" << endl;

        cout << string(anchoCoordenadas + anchoTiempo + anchoEstado + anchoFrecuencia + anchoColor + 14, '-') << endl;

        // Imprimir los datos del vuelo
        for (size_t i = 0; i < posiciones.size(); ++i) {
            const Posicion& pos = posiciones[i];
            const SistemaLuminoso& sistema = sistemasLuminosos[i];

            stringstream coordenadas;
            coordenadas << fixed << setprecision(2)
                << "(" << pos.getX() << ", " << pos.getY() << ", " << pos.getZ() << ")";

            cout << setw(anchoCoordenadas) << coordenadas.str()
                << " | " << setw(anchoTiempo) << pos.getTiempoPermanencia()
                << " | " << setw(anchoEstado) << sistema.getEstado()
                << " | " << setw(anchoFrecuencia) << fixed << setprecision(2) << sistema.getFrecuencia()
                << " | " << setw(anchoColor) << sistema.getColor() << endl;
        }
        printf("\n");
    }
};

/**
 * @class Dron
 * @brief Clase que representa un dron, maneja la carga y muestra de datos de vuelo.
 */
class Dron {
private:
    Vuelo vuelo; ///< Vuelo asociado al dron.
    Archivo archivo; ///< Archivo de donde se cargan los datos del vuelo.

    /**
     * @brief Reemplaza comas por puntos en una cadena.
     * @param s La cadena original.
     * @return La cadena con comas reemplazadas por puntos.
     */
    string comaPorPunto(const string& s) {
        string res = s;
        for (size_t i = 0; i < res.size(); ++i) {
            if (res[i] == ',') {
                res[i] = '.';
            }
        }
        return res;
    }
public:
    /**
     * @brief Constructor de la clase Dron.
     * @param nombreArchivo Nombre del archivo de donde se cargarán los datos.
     */
    Dron(const string& nombreArchivo)
        : archivo(nombreArchivo) {}

    /**
     * @brief Carga los datos del archivo al vuelo.
     */
    void cargarDatos() {
        string linea;
        while ((linea = archivo.leerLinea()) != "") {
            stringstream ss(linea);
            string token;
            float x, y, z, frecuencia;
            int tiempo;
            string estado, color;

            // Parsear las coordenadas X, Y, Z y tiempo de permanencia
            getline(ss, token, ';'); x = stof(comaPorPunto(token));
            getline(ss, token, ';'); y = stof(comaPorPunto(token));
            getline(ss, token, ';'); z = stof(comaPorPunto(token));
            getline(ss, token, ';'); tiempo = stoi(comaPorPunto(token));

            // Parsear el sistema luminoso
            getline(ss, token, ';'); estado = token;
            getline(ss, token, ';'); frecuencia = stof(comaPorPunto(token));
            getline(ss, token, ';'); color = token;

            // Crear la posición y el sistema luminoso
            Posicion posicion(x, y, z, tiempo);
            SistemaLuminoso sistema(estado, frecuencia, color);

            // Agregar la posición y el sistema luminoso al vuelo
            vuelo.agregarPosicion(posicion);
            vuelo.agregarSistemaLuminoso(sistema);
        }
    }

    /**
     * @brief Muestra los datos del vuelo.
     */
    void mostrarDatos() const {
        vuelo.mostrarDatos();
    }
};

/**
 * @brief Función principal.
 * @param argc Número de argumentos.
 * @param argv Array de argumentos.
 * @return Código de salida.
 */
int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Uso: " << argv[0] << " <nombreArchivo>" << endl;
        return 1;
    }
    cout << "Nombre del archivo proporcionado: " << argv[1] << endl; // Mensaje de depuración
    Dron dron(argv[1]);

    dron.cargarDatos();
    dron.mostrarDatos();

    return 0;
}