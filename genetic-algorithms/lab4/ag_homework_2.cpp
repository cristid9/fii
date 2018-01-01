#include "stdafx.h"
#include <windows.h>
#include <vector>
#include <random>
#include <iostream>

using std::cout;

#include "raw_point.h"
#include "function.h"
#include "population.h"

#define M_PI 3.14159265358979323846

using std::cout;
using std::vector;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::default_random_engine;

#define POP_SIZE 100
#define ITERATIONS 100

class GeneticAlgorithm
{
	Population population;
	size_t iterations;

public:
	GeneticAlgorithm(Population p, int it)
		: population(p), iterations(it)
	{
	}
	
	Chromozome run()
	{
		population.evaluate();
		
		int i = 0;
		while (i < iterations)
		{
			population.evolve();
			++i;
		}

		return population.get_fittest();
	}

};

class SupervisoryGeneticAlgorithm
{
private:
	Function function_to_optimize__;
public:
	SupervisoryGeneticAlgorithm(Function to_optimize)
		: function_to_optimize__(to_optimize)
	{
	}

	Chromozome supervise()
	{
		Population pop(100, 10, function_to_optimize__, 0.65, 0.50);
		GeneticAlgorithm ga(pop, 1000);

		Chromozome ch = ga.run();
		vector<double> values = ch.to_real();
		return ch;
	}
};

/**
* Raw hard-coded expression of the ackley function.
*/
double ackley_function(RawPoint p)
{
	double a = 20;;
	double b = 0.2;
	double c = 2 * M_PI;

	vector<double> vals = p.get_vals();

	double sum_pows = 0.0;
	double sum_cos = 0.0;
	for (auto it = vals.begin(); it != vals.end(); ++it)
	{
		sum_pows += pow(*it, 2.0);
		sum_cos += cos(c * (*it));
	}

	return -a * exp(-b * sqrt((1.0 / vals.size()) * sum_pows))
		- exp((1.0 / vals.size()) * sum_cos) + a + exp(1);
}

/**
* Raw hard-coded expression of the de jong's function.
*/
double de_jong_function(RawPoint p)
{
	double sum = 0.0;

	for (int i = 0; i < p.get_vals().size(); ++i)
	{
		sum += pow(p.get_vals()[i], 2.0);
	}

	return sum;
}

double de_jong_modified(RawPoint p)
{
	return -1 * de_jong_function(p) + 5000;
}


/**
* Raw hard-coded expression of the Schwefel's function.
*/
double schwefel_function(RawPoint p)
{
	double sum = 0.0;
	for (int i = 0; i < p.get_vals().size(); ++i)
	{
		sum += p.get_vals()[i] * sin(sqrt(fabs(p.get_vals()[i])));
	}

	return sum;
}

double schwefel_function_pos(RawPoint p)
{
	return -1 * schwefel_function(p) + 5000;
}

/**
* @brief hard-coded expression for the six hump...
*/
double six_hump_function(RawPoint p)
{
	double x1 = p.get_vals()[0];
	double x2 = p.get_vals()[1];

	return (4 - 2.1 * pow(x1, 2.0) + pow(x1, 4.0 / 3.0)) * pow(x1, 2.0) +
		x1 * x2 + (-4 + 4 * pow(x2, 2.0)) * pow(x2, 2.0);
}

double to_optimize(RawPoint p)
{

	double x = p.get_vals()[0];

	return pow(x, 3.0) -
		60 * pow(x, 2.0) +
		900 * x +
		100 - 18;
}

Domain to_optimize_domain(0, 31);
Function func_to_optimize(to_optimize, to_optimize_domain, 2, 1);

double supervisory_algorithm_function(RawPoint p)
{
	vector<double> vals     = p.get_vals();
	double crossover_rate__ = vals[0] / 100;
	double mutation_rate__  = vals[1] / 100;
	size_t pop_size__       = vals[2];
	size_t iterations__     = vals[3];

	Population pop(pop_size__, 10, func_to_optimize, crossover_rate__, mutation_rate__);
	GeneticAlgorithm ga(pop, iterations__);
	
	return func_to_optimize.eval(ga.run());
}

int main()
{

	Domain supervisory_domain(0, 100);
	Function func(supervisory_algorithm_function, supervisory_domain, 2, 4);

	SupervisoryGeneticAlgorithm sga(func);
	
	vector<double> results = sga.supervise().to_real();
	
	for (int i = 0; i < results.size(); ++i)
	{
		std::cout << "=============================" << std::endl;
		std::cout << results[i] << std::endl;
		std::cout << "=============================" << std::endl;
	}
	
	return 0;
}

