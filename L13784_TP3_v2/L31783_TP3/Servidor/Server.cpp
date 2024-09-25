#include "Server.h"

using namespace XmlRpc;

XmlRpcServer MyServer;

void Numbers::execute(XmlRpcValue& params, XmlRpcValue& result) {
	NumberMethods numbers(params[0], params[1]);
	result = numbers.generate();
} Numbers(&MyServer);


int main(int argc, char* argv[1])
{
	if (argc != 2) {
		std::cerr << "Uso: Servidor N_PORT\n";
		return -1;
	}
	int port = atoi(argv[1]);
	XmlRpc::setVerbosity(5);
	MyServer.bindAndListen(port);
	MyServer.enableIntrospection(true);
	MyServer.work(-1.0);
	
	return 0;
}
