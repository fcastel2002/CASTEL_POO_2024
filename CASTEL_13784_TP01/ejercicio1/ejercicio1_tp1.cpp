/*
 Created by Francisco Castel on 11/08/2024.
@author
Francisco Castel
@version
1.0 11/08/2024
1.1 29/08/2024 (Latest version)
*/

#include <iostream>
#include <windows.h>

using namespace std;
class Matriz {

    int cantFilas;
    int cantColumnas;
    char** matrix;

public:
    void llenar() { //genera la matriz de caracteres aleatorios
        for(int i = 0; i<this->cantFilas;i++) {
            for(int j = 0; j<this->cantColumnas;j++) {
                this->matrix[i][j] = rand()%96+32;
            }
        }
    }
    void mostrar() { //muestra en consola la matriz
        for(int i = 0;i<this->cantFilas;i++) {
            for(int j = 0; j<this->cantColumnas;j++) {
                cout<<this->matrix[i][j]<<" ";

            }
            cout<<endl;
        }
    }
    void borrar() { // Destructor
        for(int i = 0; i<this->cantFilas; i++) {
            delete[] this->matrix[i];
        }
        delete[] this->matrix;
    }
    Matriz(int n, int m) {  // Constructor
        this->cantFilas = n;
        this->cantColumnas = m;
        this->matrix = new char*[cantFilas];
        for(int i =0; i<cantFilas;i++) {
            this->matrix[i] = new char[cantColumnas];
        }
    }
    ~Matriz() {
        cout << "Matriz borrada con éxito\n"<<endl;
    }
};
int main() {
    SetConsoleOutputCP(CP_UTF8); // Para que se muestren los caracteres especiales
    cout<<"Ingrese tamaño de matriz... \n";
    int n,m;

    cout<<"Cantidad de filas: ";
    cin >> n;
        if (n<=0) {
            cout<<"Cantidad de filas no puede menor o igual a 0\n";
            return 0;
        }
    cout<<"Cantidad de columnas: ";
    cin >> m;
        if (m<=0) {
            cout<<"Cantidad de columnas no puede menor o igual a 0\n";
            return 0;
        }
    Matriz matriz1(n,m);
    matriz1.llenar();
    matriz1.mostrar();
    matriz1.borrar();
    return 0;

}

