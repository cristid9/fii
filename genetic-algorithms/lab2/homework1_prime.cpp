#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <set>
#include <map>
#include <bitset>
#include <climits>
#include <string>
#include <vector>

#define ITERATIONS 10000

using namespace std;

int f(int x)
{
	return pow(x, 3.0) -
		60 * pow(x, 2.0) +
		900 * x +
		100;
}

bitset<5> get_initial_solution()
{
	bitset<5> init_sol(string("00000"));

	for (int i = 0; i < 5; ++i)
	{
		if (rand() % 2)
		{ 
			init_sol.flip(i);  
		}
	}

	return init_sol;
}

int to_int(bitset<5> hilltop)
{
	int sol = 0;
	for (int i = 4; i >= 0; --i)
	{
		sol += hilltop[i] * pow(2, i);
	}

	return sol;
}

set<int> sa_hill_climbing(int iterations)
{
	vector<int> max_hilltops;
	map<int, set<int>> landscape;

	for (int i = 0; i < iterations; ++i)
	{
		bitset<5> max_hilltop = get_initial_solution();

		landscape[to_int(max_hilltop)] = set<int>();
		int max_fitness = f(to_int(max_hilltop));
		bool increase_found = true;

		while (increase_found)
		{
			increase_found = false;
			for (int bit_position = 0; bit_position < 5; bit_position++)
			{
				bitset<5> hilltop = max_hilltop;
				hilltop.flip(bit_position);
				int fitness = f(to_int(hilltop));
				
				if (fitness > max_fitness)
				{
					max_fitness = fitness;
					max_hilltop = hilltop;
					landscape[to_int(max_hilltop)] = set<int>();
					increase_found = true;
				}

				landscape[to_int(max_hilltop)].insert(to_int(hilltop));
			}
		}
		
		max_hilltops.push_back(to_int(max_hilltop));
	}


	int maxi = f(max_hilltops[0]);
	int choose = max_hilltops[0];
	for (int i = 1; i < max_hilltops.size(); ++i)
	{
		if (f(max_hilltops[i]) > maxi)
		{
			maxi = f(max_hilltops[i]);
			choose = max_hilltops[i];
		}
	}

	cout << choose << "<=asta e boss" << endl;
	return landscape[choose];
}

map<int, set<int>> na_hill_climbing(int iterations)
{
	vector<int> max_hilltops;
	map<int, set<int>> landscape;

	for (int i = 0; i < iterations; ++i)
	{
		bitset<5> max_hilltop = get_initial_solution();

		landscape[to_int(max_hilltop)] = set<int>();
		int max_fitness = f(to_int(max_hilltop));

		for (int bit_position = 0; bit_position < 5; bit_position++)
		{
			bitset<5> hilltop = max_hilltop;
			hilltop.flip(bit_position);
			int fitness = f(to_int(hilltop));

			if (fitness > max_fitness)
			{
				max_fitness = fitness;
				max_hilltop = hilltop;
				landscape[to_int(max_hilltop)] = set<int>();
			}

			landscape[to_int(max_hilltop)].insert(to_int(hilltop));
		}

		max_hilltops.push_back(to_int(max_hilltop));
	}


	int maxi = f(max_hilltops[0]);
	int choose = max_hilltops[0];
	for (int i = 1; i < max_hilltops.size(); ++i)
	{
		if (f(max_hilltops[i]) > maxi)
		{
			maxi = f(max_hilltops[i]);
			choose = max_hilltops[i];
		}
	}

	return landscape;
}


int main()
{
	map<int, set<int>> vc = na_hill_climbing(2);

	for (auto it = vc.begin(); it != vc.end(); ++it)
	{
		cout << it->first << ": " << endl;
		for (auto jt = it->second.begin(); jt != it->second.end(); ++jt)
		{
			cout << "\t" << (*jt) << endl;
		}
	}

    return 0;
}

