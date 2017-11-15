#! /bin/bash
from pprint import pprint


def generic_combinations(i, n, depth, stop):
	master_collections = []
	collections = [-1 for i in range(0, 9)]

	def f(i, n, depth, stop):
		"""
		Useful for avoiding module-level variables.
		"""
		if depth == n:
			master_collections.append(list([n for n in collections if n != -1]))
			return
	
		for i in range(0, stop):
			collections[n] = i
			f(i + 1, n + 1, depth, stop)

	f(i, n, depth, stop)
	return master_collections


def len_x_chose_k(x, k):
	x_combinations = []
	master_collections = generic_combinations(0, 1, k, len(x))
	for configuration in master_collections:
		combination = set([x[i] for i in configuration])

		if combination not in x_combinations:
			x_combinations.append(combination)

	return x_combinations


if __name__ == "__main__":
	pprint(len(len_x_chose_k([1, 2, 3, 4], 4)))
	# print collections
	# pass:q

