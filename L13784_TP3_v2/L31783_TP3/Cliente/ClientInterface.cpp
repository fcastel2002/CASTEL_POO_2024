#include "ClientInterface.h"

void ClientInterface::showMessage(const std::string& message)
{
	std::cout << message;
}

void ClientInterface::showNumbers(const std::vector<double>& numbers)
{
	for (const auto& number : numbers)
	{
		std::cout << number << " ";
	}
	std::cout << std::endl;
}

void ClientInterface::showResults(XmlRpcValue result)
{
	std::cout << "Results: " << std::endl;
	for (int i = 0; i < result.size(); i++)
	{
		std::cout << result[i] << " ";
	}
	std::cout << std::endl;
}