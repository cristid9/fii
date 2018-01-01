#ifndef POPULATION_H__
#define POPULATION_H__

#include <vector>
#include <random>
#include "function.h"
#include "chromozome.h"
#include <windows.h>

using std::uniform_real_distribution;
using std::uniform_int_distribution;
using std::default_random_engine;
using std::vector;

class Population
{
private:
	vector<Chromozome> vals;
	vector<double> eval_results;
	default_random_engine engine;
	uniform_real_distribution<double> select_distribution;
	size_t pop_size;
	size_t tournament_size;
	double crossover_rate;
	double mutation_rate;
	Function func;
public:
	Population(size_t p_size, size_t t, Function f, double xo_rate, double m_r)
		: func(f), pop_size(p_size), tournament_size(t), crossover_rate(xo_rate),
		mutation_rate(m_r)
	{
		select_distribution = uniform_real_distribution<double>(0, 1);
		for (int i = 0; i < pop_size; ++i)
		{
			Chromozome s(f.get_domain(), f.get_args_number(), f.get_precission());
			s.make_random();
			vals.push_back(s);
		}

	}

	void evaluate()
	{
		eval_results = vector<double>();
		for (int i = 0; i < pop_size; ++i)
		{
			double result = func.eval(vals[i]);

			eval_results.push_back(result);
		}
	
	}

	void select()
	{
		double total_fitness = 0;
		for (int i = 0; i < eval_results.size(); ++i)
		{
			total_fitness += eval_results[i];
		}

		vector<double> rel_fitness;
		for (int i = 0; i < eval_results.size(); ++i)
		{
			rel_fitness.push_back(eval_results[i] / total_fitness);
		}


		vector<double> probs;
		probs.push_back(rel_fitness[0]);
		for (int i = 1; i < rel_fitness.size(); ++i)
		{
			probs.push_back(probs[i - 1] + rel_fitness[i]);
		}

		vector<Chromozome> new_pop;
		while (new_pop.size() < pop_size)
		{
			double r = select_distribution(engine);
			for (int j = 0; j < probs.size() - 1; ++j)
			{
				if (r <= probs[j + 1] && r > probs[j])
				{
					new_pop.push_back(vals[j]);
					break;
				}
			}
		}

		vals = new_pop;
	}

	void crossover()
	{
		uniform_int_distribution<int> distribution(0, pop_size - 10);
		uniform_real_distribution<double> distribution_xo(0, 1);

		for (int i = 0; i < pop_size; ++i)
		{
			int k = distribution(engine);
			int j = distribution(engine);
			Chromozome c1 = vals[k];
			Chromozome c2 = vals[j];

			double r = distribution_xo(engine);
			if (r <= crossover_rate)
			{
				int limit = c1.get_raw_val().size() * c1.get_raw_val()[0].size();

				uniform_int_distribution<int> xo_point_distribution(0, limit - 1);
				int xo_point = xo_point_distribution(engine);

				vector<vector<bool>> c1_vals = c1.get_raw_val();
				vector<vector<bool>> c2_vals = c2.get_raw_val();
				vector<vector<bool>> c1_vals_tmp = c1.get_raw_val();

				int times = 0;
				for (int idx1 = 0; idx1 < c1_vals.size() && times < xo_point; idx1++)
				{
					for (int idx2 = 0; idx2 < c1_vals[0].size() && times < xo_point; ++idx2)
					{
						c1_vals[idx1][idx2] = c2_vals[idx1][idx2];
						times++;
					}
				}

				times = 0;
				for (int idx1 = 0; idx1 < c2_vals.size(); ++idx1)
				{
					for (int idx2 = 0; idx2 < c2_vals[0].size(); ++idx2)
					{
						if (times > xo_point)
						{
							c2_vals[idx1][idx2] = c1_vals_tmp[idx1][idx2];

						}
						times++;
					}
				}

				Chromozome c1_ = c1;
				Chromozome c2_ = c2;
				c1_.set_vals(c1_vals);
				c2_.set_vals(c2_vals);

				if (func.eval(c1_) > func.eval(c1))
				{
					vals[k] = c1_;
				}

				if (func.eval(c2_) > func.eval(c2))
				{
					vals[j] = c2_;
				}
			}
		}
	}

	void mutate()
	{
		uniform_real_distribution<double> distribution(0, 1);
		for (int i = 0; i < pop_size; ++i)
		{
			double r = distribution(engine);

			if (r <= mutation_rate)
			{
				vals[i].mutate();
			}
		}
	}

	Chromozome get_fittest()
	{
		double fittest = func.eval(vals[0]);
		Chromozome s = vals[0];

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

	void evolve()
	{
		select();
		crossover();
		mutate();
		evaluate();
	}
};


#endif