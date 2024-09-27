/* holaServer.cpp : ejemplo sencillo de servidor XMLRPC. 
   Uso: holaServer Port
*/
#define WIN32_LEAN_AND_MEAN

// Incluir winsock2.h antes de windows.h
#include <winsock2.h>
#include <windows.h>

#include <iostream>
#include <stdlib.h>
using namespace std;
#include "../XMLRPC++/XmlRpc.h"
using namespace XmlRpc;

#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "../x64/Debug/XMLRPC++.lib")
// S es el servidor
XmlRpcServer S;

// Sin argumentos, el resultado es "Hola".
class Saludo : public XmlRpcServerMethod
{
public:
  Saludo(XmlRpcServer* S) : XmlRpcServerMethod("Saludo", S) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result)
  {
    result = "Hola";
  }

  std::string help() { return std::string("Diga Hola"); }

} saludo(&S);    // Este constructor registra el método en el servidor


// Con un argumento, el resultado es "Hola, " + argumento
class SaludoNombre : public XmlRpcServerMethod
{
public:
  SaludoNombre(XmlRpcServer* S) : XmlRpcServerMethod("SaludoNombre", S) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result)
  {
    std::string resultString = "Hola, ";
    resultString += std::string(params[0]);
    result = resultString;
  }
} saludoNombre(&S);


// Con un numero variable de argumento, todos dobles, el resultado es la suma
class Sumar : public XmlRpcServerMethod
{
public:
  Sumar(XmlRpcServer* S) : XmlRpcServerMethod("Sumar", S) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result)
  {
    int nArgs = params.size();
    double sum = 0.0;
    for (int i=0; i<nArgs; ++i)
      sum += double(params[i]);
    result = sum;
  }
} sumar(&S);

int main(int argc, char* argv[])
{
  if (argc != 2) {
    std::cerr << "Uso: hola_server N_Port\n";
    return -1;
  }
  int port = atoi(argv[1]);

  XmlRpc::setVerbosity(5);

  // Se crea un socket de servidor sobre el puerto indicado
  S.bindAndListen(port);

  // Enable introspection
  S.enableIntrospection(true);

  // A la escucha de requerimientos
  S.work(-1.0);

  return 0;
}
 
