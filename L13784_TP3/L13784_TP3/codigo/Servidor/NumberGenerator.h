#pragma once

#include <random>
#include <vector>
#include "User.h"
class NumberMethods
{
protected: //protegemos para poder heredar
	double m_ci {};
	double m_cs {};

	std::default_random_engine generator; //mersenne_twister_engine (pseudorandom number generator)
	std::uniform_real_distribution<double> distribution; //uniform_real_distribution (continuous distribution)

public:
	NumberMethods(double ci, double cs);

	void updateDistribution(double ci, double cs);
	double generate();
	double sum(std::vector<double> currentNumbers);
	double average(std::vector<double> currentNumbers);
	
};	
