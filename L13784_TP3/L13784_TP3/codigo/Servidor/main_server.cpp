

#include "Server.h"
XmlRpcServer MyServer;

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
    userManager.loadUsers();

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
                    "stats: mostrar estadisticas de los usuarios\n"
                    "clear: borrar contenido de archivo users.bin\n");
            }
            else if (command == "clear") {
				AdminInterface::showMessage("Esta seguro de que desea borrar los usuarios? (s/n)\n");
				std::string response;
				std::getline(std::cin, response);
                if (response == "s") {
                    userManager.clearUsersFile();
                    AdminInterface::showMessage("Usuarios borrados.\n");
                }
				else 
                {
					AdminInterface::showMessage("Operacion cancelada.\n");
                    continue;
                }
               
            }
            else {
                AdminInterface::showMessage("Comando no reconocido. Escriba 'help' para ver comandos.\n");
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
    return 0;
}
