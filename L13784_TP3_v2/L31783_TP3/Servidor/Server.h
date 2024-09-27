#pragma once
#include <WinSock2.h>
#include <Windows.h>

#pragma comment(lib, "Ws2_32.lib")

#include <iostream>
#include "NumberGenerator.h"
#include "User.h"
#include <sstream>
#include "AdminInterface.h"
#include <string>

#include "../XMLRPC++/XmlRpc.h"

#pragma comment(lib, "../x64/Debug/XMLRPC++.lib")
#pragma comment(lib, "Ws2_32.lib")

using namespace XmlRpc;

class Numbers : public XmlRpcServerMethod , public NumberMethods
{
private:
	UserManager&  m_userManager;

public:
	Numbers(XmlRpcServer* S, UserManager& userManager) : XmlRpcServerMethod("GenerateNumber", S), m_userManager{ userManager }, NumberMethods(0, 0) {}
	void execute(XmlRpcValue& params, XmlRpcValue& result) override ;
	std::string help() { return std::string("Uso: GenerateNumber limite_inferior limite_superior"); }
};

class Users : public XmlRpcServerMethod, public UserManager
{

public:
	Users(XmlRpcServer* S) : XmlRpcServerMethod("RegisterUser", S) {}
	void execute(XmlRpcValue& params, XmlRpcValue& result);

};