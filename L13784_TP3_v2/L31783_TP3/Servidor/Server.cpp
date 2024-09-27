#include "Server.h"
#include <chrono>
#include <thread>
#include <conio.h>


using namespace XmlRpc;

 

XmlRpcServer MyServer;

void Numbers::execute(XmlRpcValue& params, XmlRpcValue& result) {
    std::string alias = params[0];

    // Verificar si el segundo parámetro es "NS" o parte de las cotas
    bool newSequence = false;
    double ci, cs;

    if (params.size() > 2 && params[1] == "NS") {
        newSequence = true;  // Nueva secuencia
        ci = params[2];  // Cota inferior
        cs = params[3];  // Cota superior
    }
    else {
        ci = params[1];  // Cota inferior (cuando no hay "NS")
        cs = params[2];  // Cota superior
    }

    // Obtener usuario
    User* user = m_userManager.getUser(alias);
    if (!user) {
        m_userManager.addUser(alias, "127.0.0.1");
        user = m_userManager.getUser(alias);
    }

    // Si es una nueva secuencia, limpiar la secuencia anterior
    if (newSequence) {
        user->clearSequence();
    }

    // Actualizar los límites de ci y cs
    this->updateDistribution(ci, cs);
    double generatedNumber = this->generate();

    // Agregar el número generado a la secuencia
    user->addNumberToSequence(generatedNumber);

    // Formar el mensaje de respuesta en un string
    std::ostringstream response;

    response << "Numero generado: " << generatedNumber << "\n";
    AdminInterface::showMessage(response.str()); 

    response << "Suma acumulada: " << user->getSum() << "\n";
    AdminInterface::showMessage(response.str()); 

    response << "Promedio: " << user->getAverage() << "\n";
    AdminInterface::showMessage(response.str()); 

    response << "Numeros en la secuencia: ";

    std::vector<double> sequence = user->getSequence();

    std::sort(sequence.begin(), sequence.end());

    for (double num : sequence) {
        response << num << " ";
    }
    response << "\n";
    AdminInterface::showMessage(response.str()); 

    // Asignar el string resultante a `result`
    result = response.str();
}

int main(int argc, char* argv[1])
{
    if (argc != 2) {
        std::cerr << "Uso: Servidor N_PORT\n";
        return -1;
    }
    int port = atoi(argv[1]);
    XmlRpc::setVerbosity(5);

    UserManager userManager;

    MyServer.bindAndListen(port);

    Numbers generateNumber(&MyServer, userManager);

    MyServer.enableIntrospection(true);

    std::string command;

    AdminInterface::showMessage("Servidor iniciado en el puerto " + std::to_string(port) + ". Escriba 'help' para ver comandos.\n");

    while (true) {
        MyServer.work(0.4);

        if (_kbhit()) {
            std::getline(std::cin, command);

            if (command == "exit") {

                userManager.saveUsers();
                AdminInterface::showMessage("saliendo...\n");
                break;
            }
            else if (command == "save") {
                userManager.saveUsers();
                AdminInterface::showMessage("Usuarios guardados.\n");
            }
            else if (command == "load") {
                userManager.loadUsers();
                AdminInterface::showMessage("Usuarios cargados.\n");
            }
            else if (command == "stats") {
                auto users = userManager.getUsers();
                for (const auto& pair : users) {
                    const User& user = pair.second;
                    AdminInterface::showMessage("Alias: " + user.getAlias() + "\n");
                    AdminInterface::showMessage("IP: " + user.getIpAddress() + "\n"); 
                    AdminInterface::showMessage("Numeros generados: " + std::to_string(user.getNumbersGenerated()) + "\n");  
                    AdminInterface::showMessage("Secuencias iniciadas: " + std::to_string(user.getSequencesStarted()) + "\n"); 
                }
            }
            else if (command == "help") {
                AdminInterface::showMessage("Comandos disponibles:\n"
                    "exit: salir del servidor\n"
                    "save: guardar los usuarios en un archivo\n"
                    "load: cargar los usuarios de un archivo\n"
                    "stats: mostrar estadísticas de los usuarios\n");
            }
            else {
                AdminInterface::showMessage("Comando no reconocido. Escriba 'help' para ver comandos.\n"); 
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
    return 0;
}
