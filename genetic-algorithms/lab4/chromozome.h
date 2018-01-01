#ifndef CHROMOZOME_H__
#define CHROMOZOME_H__

#include <vector>
#include <random>
#include <iostream>
#include "domain.h"

using std::uniform_int_distribution;
using std::default_random_engine;
using std::vector;
using std::cout;

class Chromozome
{
private:
	vector<vector<bool>> solution_value;
	Domain solution_domain;
	unsigned int precission;
	unsigned int solution_args;
	unsigned int solution_size;
	default_random_engine debug_engine;
	uniform_int_distribution<int> debug_distribution;

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

		debug_distribution = uniform_int_distribution<int>(0, 1);
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
	Chromozome(Domain d, unsigned int sol_args, unsigned int p)
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

		for (int i = 0; i < solution_value.size(); ++i)
		{
			for (int j = 0; j < solution_value[i].size(); ++j)
			{
				int v = debug_distribution(debug_engine);
				solution_value[i][j] = rand() % 2;
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


#endif // CHROMOZOME_H__