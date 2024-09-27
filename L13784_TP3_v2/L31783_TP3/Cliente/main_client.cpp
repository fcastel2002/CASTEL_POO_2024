#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "../XMLRPC++/XmlRpc.h"

#include "RequestHandler.h"
#include "ClientInterface.h"

#pragma comment(lib, "../x64/Debug/XMLRPC++.lib")
#pragma comment(lib, "Ws2_32.lib")
using namespace XmlRpc;

int main(int argc, char* argv[])
{
    if (argc != 3) {
        std::cerr << "Uso: cliente IP_HOST N_PORT\n";
        return -1;
    }

    int port = std::atoi(argv[2]);

    // Conexión al servidor XML-RPC
    XmlRpcClient client(argv[1], port);
	XmlRpcValue request, result, noArgs; 
	if (client.execute("system.listMethods", noArgs, result))
	{
		ClientInterface::showMessage("Metodos:\n " + result.toXml() + "\n");
	}
    else {
		std::cerr << "Error en la llamada a 'listMethods'\n";
    }

    while (true) {

        std::string command;
        ClientInterface::showMessage("Introduzca peticion (alias param1 param2 param3 param4)\n");
        std::getline(std::cin, command);
        std::istringstream iss(command);
        std::vector<std::string> params;
        std::string token;

        while (iss >> token)
        {
            params.push_back(token);
        }

        if (params.empty())
        {
            std::cerr << "Error: se esperaba al menos un parámetro.\n";
            continue;
        }

        try
        {
            std::string alias = params[0];
            std::vector<std::string> requestParams(params.begin() + 1, params.end()); // Se toman los parametros de la peticion
            RequestHandler requestHandler(alias, requestParams);
            request = requestHandler.getRequest();
			


            // Enviar la petición al método "GenerateNumber" del servidor

            if (client.execute("GenerateNumber", request, result)) {
				ClientInterface::showResults(result); 
            }
            else {
                std::cerr << "Error al ejecutar la petición." << std::endl;
            }
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
		}


    }
    return 0;
}
