#include "stdafx.h"
#include <vector>
#include <random>
#include <iostream>


#define M_PI 3.14159265358979323846

using std::cout;
using std::vector;
using std::uniform_int_distribution;
using std::uniform_real_distribution;
using std::default_random_engine;

#define POP_SIZE 100
#define ITERATIONS 100

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

	void set_vals(vector<vector<bool>> v)
	{
		solution_value = v;
	}

	void flip(unsigned int n)
	{

		for (int i = 0; i < solution_value.size(); ++i)
		{
			solution_value[i][n] = !solution_value[i][n];
		}
	}

	void make_random()
	{
		default_random_engine engine;
		uniform_int_distribution<int> distribution(0, 1);

		for (int i = 0; i < solution_value.size(); ++i)
		{
			for (int j = 0; j < solution_value[i].size(); ++j)
			{
				solution_value[i][j] = distribution(engine);
			}
		}
	}

	void mutate()
	{
		default_random_engine engine;
		uniform_int_distribution<int> distribution(0, solution_value.size() - 1);
		int pos = distribution(engine);

		uniform_int_distribution<int> distribution2(0, solution_value[pos].size() - 1);
		int pos_in = distribution2(engine);

		solution_value[pos][pos_in] = !solution_value[pos][pos_in];
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

	vector<vector<bool>> get_raw_val() const
	{
		return solution_value;
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
};

class Population
{
private:
	vector<CandidateSolution> vals;
	size_t pop_size;
	size_t tournament_size;
	Function func;
public:
	Population(size_t p_size, size_t t, Function f) 
		: func(f), pop_size(p_size), tournament_size(t)
	{
		for (int i = 0; i < pop_size; ++i)
		{
			CandidateSolution s(f.get_domain(), f.get_args_number(), f.get_precission());
			s.make_random();
			vals.push_back(s);
		}
	}

	void select()
	{
		int i = 0;

		default_random_engine engine;
		uniform_int_distribution<int> distribution(0, pop_size - 1);

		while (i < tournament_size)
		{
			int index1 = distribution(engine);
			int index2 = distribution(engine);

			while (index1 == index2)
			{
				index2 = distribution(engine);
			}

			double fitness1 = func.eval(vals[index1]);
			double fitness2 = func.eval(vals[index2]);

			if (fitness1 > fitness2)
			{
				vals[index2] = vals[index1];
			}
			else
			{
				vals[index1] = vals[index2];
			}

			i++;
		}
	}

	void crossover()
	{
		default_random_engine engine;
		uniform_int_distribution<int> distribution(0, pop_size);
		uniform_int_distribution<int> distribution2(0,
			vals[0].get_sollution_size() * vals[0].get_raw_val()[0].size() - 1);

		for (int i = 0; i < pop_size; i++)
		{
			//while (!func.in_domain(chromozome1) && !func.in_domain(chromozome2))
			//{
			int index1 = distribution(engine);
			int index2 = distribution(engine);

			while (index1 == index2)
			{
				index2 = distribution(engine);
			}

			if (index1 > index2)
			{
				int tmp = index1;
				index1 = index2;
				index2 = tmp;
			}

			int point1 = distribution2(engine);
			int point2 = distribution2(engine);

			while (point1 == point2)
			{
				point2 = distribution2(engine);
			}

			if (point1 > point2)
			{
				int tmp = point1;
				point1 = point2;
				point2 = tmp;
			}


			vector<vector<bool>> tmp = vals[index1].get_raw_val();
			vector<vector<bool>> chromozome2 = vals[index2].get_raw_val();
			vector<vector<bool>> chromozome1 = vals[index1].get_raw_val();

			int counter = 0;
			for (int i = 0; i < chromozome1.size(); ++i)
			{
				for (int j = 0; j < chromozome1[i].size(); ++j)
				{
					if (counter > point1)
					{
						chromozome1[i][j] = chromozome2[i][j];
					}

					counter++;
				}
			}

			counter = 0;

			for (int i = 0; i < chromozome2.size(); ++i)
			{
				for (int j = 0; j < chromozome2[i].size(); ++j)
				{
					if (counter < point2)
					{
						chromozome2[i][j] = tmp[i][j];
					}
					counter++;
				}
			}

			vals[index1].set_vals(chromozome1);
			vals[index2].set_vals(chromozome2);
		}

		// }
		//vals[index1].set_vals(chromozome1);
		//vals[index2].set_vals(chromozome2);
	}

	void mutate()
	{
		default_random_engine engine;
		uniform_int_distribution<int> distribution(0, 1);
		for (int i = 0; i < pop_size; ++i)
		{
			int r = distribution(engine);

			if (r)
			{
				vals[i].mutate();
			}
		}
	}

	CandidateSolution get_fittest() 
	{
		double fittest = func.eval(vals[0]);
		CandidateSolution s = vals[0];

		for (int i = 1; i < pop_size; ++i)
		{
			if (func.eval(vals[i]) > fittest)
			{
				fittest = func.eval(vals[i]);
				s = vals[i];
			}
		}

		return s;
	}
};

class GeneticAlgorithm
{
	Population population;
	size_t iterations;

public:
	GeneticAlgorithm(Population p, int it)
		: population(p), iterations(it)
	{
	}
	
	RawPoint run()
	{
		int i = 0;
		while (i < iterations)
		{
			population.select();
			population.crossover();
			population.mutate();

			++i;
		}

		return population.get_fittest().to_real();
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
		100;
}

int main()
{

	Domain to_optimize_domain(0, 31);
	Function func(to_optimize, to_optimize_domain, 2, 1);

	Population p(1000, 1000, func);
	GeneticAlgorithm g(p, 1000);

	RawPoint point = g.run();

	for (int i = 0; i < point.get_vals().size(); ++i)
	{
		std::cout << point.get_vals()[i] << " ";
	}
	
	std::cout << std::endl;
	
	return 0;
}

