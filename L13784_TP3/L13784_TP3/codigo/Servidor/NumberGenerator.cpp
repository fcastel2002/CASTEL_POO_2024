#include "NumberGenerator.h"
#include <ctime>
#include <vector>
NumberMethods::NumberMethods(double ci, double cs) : m_ci{ ci }, m_cs{ cs }, distribution( m_ci, m_cs )
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
	double sum = 0;
	for (auto& number : currentNumbers) {
		sum += number;
	}
	return sum;
}

double NumberMethods::average(std::vector <double> currentNumbers)
{
	double sum = 0;
	for (auto& number : currentNumbers) {
		sum += number;
	}
	return sum / currentNumbers.size();
}

void NumberMethods::updateDistribution(double ci, double cs)
{
	m_ci = ci;
	m_cs = cs;
	distribution = std::uniform_real_distribution<double>(ci, cs);
}