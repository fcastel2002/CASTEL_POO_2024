#pragma once
#include <WinSock2.h>
#include <Windows.h>

#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include "NumberGenerator.h"
#include "UserManager.h"
#include "Statistics.h"

#include "../XMLRPC++/XmlRpc.h"

#pragma comment(lib, "../x64/Debug/XMLRPC++.lib")



class Numbers : public XmlRpcServerMethod , public NumberMethods
{
public:
	Numbers(XmlRpcServer* S) : XmlRpcServerMethod("GenerateNumber", S) {}
	void execute(XmlRpcValue& params, XmlRpcValue& result);
	std::string help() { return std::string("Uso: GenerateNumber limite_inferior limite_superior"); }
};

class Users : public XmlRpcServerMethod, public UserManager
{

public:
	Users(XmlRpcServer* S) : XmlRpcServerMethod("RegisterUser", S) {}
	void execute(XmlRpcValue& params, XmlRpcValue& result);

};