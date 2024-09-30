#pragma once
#include <string>
#include <vector>
#include <iostream>


class AdminInterface
{
public:

	static void showMessage(const std::string& message);
	static void showNumbers(const std::vector<double>& numbers);
};

