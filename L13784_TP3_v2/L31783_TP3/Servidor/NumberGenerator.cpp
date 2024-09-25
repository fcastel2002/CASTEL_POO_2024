#include "NumberGenerator.h"
#include <ctime>
#include <vector>
NumberMethods::NumberMethods(double ci, double cs) : m_ci{ ci }, m_cs{ cs }, distribution{ ci, cs }
{
	std::random_device rd;
	generator.seed(rd());

}

double NumberMethods::generate()
{
	return std::round(distribution(generator) * 100.0) / 100; //round to 2 precision digits
}

double NumberMethods::sum( std::vector<double> currentNumbers )
{
	
}

double NumberMethods::average(int a, int b)
{
	return (a + b) / 2;
}