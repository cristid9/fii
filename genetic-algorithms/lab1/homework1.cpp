
#include "stdafx.h"
#include <vector>
#include <climits>
#include <cmath>
#include <algorithm>
#include <iostream>

#define M_PI 3.14159265358979323846
#define MAX_TEMPERATURE 0.99
#define TEMP_STEP 0.00001
#define MAX_ITERATIONS 100

using std::vector;
using std::pow;
using std::round;

/**
* @brief Class used to represend the domain of a function.
*/
class Domain
{
private:
	double lower_bound;
	double upper_bound;
public:
	Domain(double lb, double ub)
		:lower_bound(lb), upper_bound(ub)
	{}

	double get_lower_bound() const
	{
		return lower_bound;
	}

	double get_upper_bound() const
	{
		return upper_bound;
	}
};

class RawPoint
{
private:
	vector<double> vals;
public:
	RawPoint(vector<double> v)
	{
		vals = v;
	}

	vector<double> get_vals() const
	{
		return vals;
	}
};

class CandidateSolution
{
private:
	vector<vector<bool>> solution_value;
	Domain solution_domain;
	unsigned int precission;
	unsigned int solution_args;
	unsigned int solution_size;

	vector<unsigned int> decimal_value()
	{
		vector<unsigned int> dec_val;
		for (int i = 0; i < solution_value.size(); ++i)
		{
			dec_val.push_back(0);
			for (int j = 0; j < solution_size; ++j)
			{
				dec_val[i] += pow(2, j) * solution_value[i][j];
			}
		}
		return dec_val;
	}

	void init_zero()
	{
		solution_size = round(log2((solution_domain.get_upper_bound()
			- solution_domain.get_lower_bound()) * pow(10, precission)));

		for (int i = 0; i < solution_args; ++i)
		{
			solution_value.push_back(vector<bool>());
			for (int j = 0; j < solution_size; ++j)
			{
				solution_value[i].push_back(0);
			}
		}
	}
public:
	CandidateSolution(Domain d, unsigned int sol_args, unsigned int p)
		: solution_domain(d), precission(p), solution_args(sol_args)
	{
		init_zero();
	}

	vector<double> to_real()
	{
		vector<unsigned int> dec_vals = decimal_value();
		vector<double> real_solution;
		for (int i = 0; i < dec_vals.size(); ++i)
		{
			real_solution.push_back(solution_domain.get_lower_bound() + dec_vals[i]
				* ((solution_domain.get_upper_bound() - solution_domain.get_lower_bound())
					/ (pow(2, solution_size) - 1)));
		}
		return real_solution;
	}

	void flip(unsigned int n)
	{

		for (int i = 0; i < solution_value.size(); ++i)
		{
			solution_value[i][n] = !solution_value[i][n];
		}
		/*
		int index = rand() % solution_value.size();
		solution_value[index][n] = !solution_value[index][n];
		*/
	}

	/**
	* @brief Made for debug purposes.
	*/
	void print() const
	{
		for (int i = 0; i < solution_value.size(); ++i)
		{
			for (int j = 0; j < solution_value[i].size(); ++j)
			{
				std::cout << solution_value[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	/**
	* @brief getter.
	*/
	unsigned int get_sollution_size() const
	{
		return solution_size;
	}
};

class Function
{
private:
	double(*func)(RawPoint point);
	Domain domain;
	unsigned int precission;
	unsigned int args_number;
public:
	Function(double(*f)(RawPoint point), Domain d, unsigned int p, unsigned int num)
		: func(f), domain(d), precission(p), args_number(num)
	{
	}

	double eval(CandidateSolution sol)
	{
		vector<double> double_sol = sol.to_real();
		RawPoint p(double_sol);

		return func(p);
	}

	unsigned int get_precission() const
	{
		return precission;
	}

	unsigned int get_args_number() const
	{
		return args_number;
	}

	Domain get_domain() const
	{
		return domain;
	}

	// TODO: overwrite the function call operator.
};

CandidateSolution random_candidate_sollution(Function func)
{
	CandidateSolution rand_sol(func.get_domain(), func.get_args_number(), func.get_precission());
	for (int i = 0; i < rand_sol.get_sollution_size(); ++i)
	{
		if (rand() % 2)
		{
			rand_sol.flip(i);
		}
	}

	// rand_sol.print();
	return rand_sol;
}

double fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

RawPoint simmulated_annealing(Function func, int max_iterations, double temp_step)
{
	double temperature = MAX_TEMPERATURE;
	CandidateSolution max_hilltop = random_candidate_sollution(func);
	double max_hilltop_fitness = func.eval(max_hilltop);

	while (temperature > 0)
	{
		// for debug purposes
		//	std::cout << max_hilltop.to_real()[0] << std::endl;

		for (int i = 0; i < max_iterations; ++i)
		{
			unsigned int bit_pos = rand() % max_hilltop.get_sollution_size();
			CandidateSolution hilltop = max_hilltop;
			hilltop.flip(bit_pos);
			double fitness = func.eval(hilltop);

			if (fitness < max_hilltop_fitness)
			{
				max_hilltop = hilltop;
				max_hilltop_fitness = fitness;
			}
			else
			{
				double probability = fRand(0.0, 0.99);
				double acceptance_probability = exp(-1 * fabs(max_hilltop_fitness - fitness) / temperature);

				if (probability < acceptance_probability)
				{
					max_hilltop = hilltop;
					max_hilltop_fitness = fitness;
				}
			}
		}
		temperature *= temp_step;
	}

	return RawPoint(max_hilltop.to_real());
}

RawPoint hil_climbing(Function func, int max_number_of_iterations)
{
	CandidateSolution max_hilltop = random_candidate_sollution(func);
	double max_fitness = func.eval(max_hilltop);

	for (int i = 0; i < max_number_of_iterations; ++i)
	{
		unsigned int bit_position = rand() % max_hilltop.get_sollution_size();
		CandidateSolution hilltop = max_hilltop;
		hilltop.flip(bit_position);
		double fitness = func.eval(hilltop);

		if (fitness <= max_fitness)
		{
			max_fitness = fitness;
			max_hilltop = hilltop;
		}
	}

	return RawPoint(max_hilltop.to_real());
}

RawPoint sa_hill_climbing(Function func, int max_number_of_iterations)
{
	vector<CandidateSolution> max_hilltops;

	for (int i = 0; i < max_number_of_iterations; ++i)
	{
		CandidateSolution max_hilltop = random_candidate_sollution(func);
		double max_fitness = func.eval(max_hilltop);
		bool increase_found = true;

		while (increase_found)
		{
			increase_found = false;
			for (int bit_position = 1; bit_position < max_hilltop.get_sollution_size(); ++bit_position)
			{
				CandidateSolution hilltop = max_hilltop;
				hilltop.flip(bit_position);
				double fitness = func.eval(hilltop);

				if (fitness < max_fitness)
				{
					max_fitness = fitness;
					max_hilltop = hilltop;
				}
			}
		}
		
		max_hilltops.push_back(max_hilltop);
	}

	CandidateSolution result = max_hilltops[0];
	double result_fitness = func.eval(result);
	
	for (auto it = max_hilltops.begin(); it != max_hilltops.end(); ++it)
	{
		if (func.eval(*it) < result_fitness)
		{
			result_fitness = func.eval(*it);
			result = *it;
		}
	}

	return RawPoint(result.to_real());
}

RawPoint na_hill_climbing(Function func, int max_number_of_iterations)
{
	vector<CandidateSolution> max_hilltops;

	for (int i = 0; i < max_number_of_iterations; ++i)
	{
		CandidateSolution max_hilltop = random_candidate_sollution(func);
		double max_fitness = func.eval(max_hilltop);

		for (int bit_position = 0; bit_position < max_hilltop.get_sollution_size(); ++bit_position)
		{
			CandidateSolution hilltop = max_hilltop;
			hilltop.flip(bit_position);
			double fitness = func.eval(hilltop);
			
			if (fitness < max_fitness)
			{
				max_fitness = fitness;
				max_hilltop = hilltop;
			}
		}
		max_hilltops.push_back(max_hilltop);
	}

	CandidateSolution result = max_hilltops[0];
	double result_fitness = func.eval(result);

	for (auto it = max_hilltops.begin(); it != max_hilltops.end(); ++it)
	{
		if (func.eval(*it) < result_fitness)
		{
			result_fitness = func.eval(*it);
			result = *it;
		}
	}

	return RawPoint(result.to_real());
}

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



int main()
{
	Domain ackley_domain(-32.768, 32.768);
	Function func(ackley_function, ackley_domain, 3, 30);
// = simmulated_annealing(func, MAX_ITERATIONS, TEMP_STEP);
	
	double minimum = DBL_MAX;
	double mean = 0;
	double maximum = DBL_MIN;

	for (int i = 0; i < 30; ++i)
	{
		RawPoint computed_sol = na_hill_climbing(func, MAX_ITERATIONS);
		minimum = std::min(minimum, ackley_function(computed_sol));
		mean += ackley_function(computed_sol);
		maximum = std::max(maximum, ackley_function(computed_sol));
	}

	mean /= 30;

	std::cout << "For ackley" << std::endl;
	std::cout << minimum << std::endl;
	std::cout << mean << std::endl;
	std::cout << maximum << std::endl;

	/*
	std::cout << "Now for De Jong's function " << std::endl;
	Domain de_jong_domain(-5.12, 5.12);
	Function de_jong(de_jong_function, de_jong_domain, 3, 5);
	//computed_sol = simmulated_annealing(de_jong, MAX_ITERATIONS, TEMP_STEP);
	computed_sol = sa_hill_climbing(de_jong, MAX_ITERATIONS);

	std::cout << de_jong_function(computed_sol) << std::endl;

	Domain schwefel_domain(-500, 500);
	Function schewefel(schwefel_function, schwefel_domain, 3, 7);
	// computed_sol = simmulated_annealing(schewefel, MAX_ITERATIONS, TEMP_STEP);
	computed_sol = sa_hill_climbing(schewefel, MAX_ITERATIONS);

	std::cout << schwefel_function(computed_sol) << std::endl;

	Domain six_hump_domain(-3, 3);
	Function six_hump(six_hump_function, six_hump_domain, 2, 2);
	// computed_sol = simmulated_annealing(six_hump, MAX_ITERATIONS, TEMP_STEP);
	computed_sol = sa_hill_climbing(six_hump, MAX_ITERATIONS);

	std::cout << "====>" << six_hump_function(computed_sol) << std::endl;
	std::cout << computed_sol.get_vals()[0] << " " << computed_sol.get_vals()[1] << std::endl;
	*/
	return 0;
}
