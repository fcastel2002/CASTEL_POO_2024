#pragma once

#include <vector>
#include <string>
#include <iostream>
#include "../XMLRPC++/XmlRpc.h"
using namespace XmlRpc;
class ClientInterface
{
public:
	static void showMessage(const std::string& message);
	static void showNumbers(const std::vector<double>& numbers);
	static void showResults(XmlRpcValue result);
};

