#include "AdminInterface.h"

void AdminInterface::showMessage(const std::string& message)
{
	std::cout << message;
}

void AdminInterface::showNumbers(const std::vector<double>& numbers)
{
	for (const auto& number : numbers)
	{
		std::cout << number << " ";
	}
	std::cout << std::endl;
}