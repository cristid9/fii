#! /bin/bash

def gcd(a, b):
	while b:
		a, b = b, a % b
	return a


def solve(*nums):
	solution = nums[0]

	for num in nums[1:]:
		solution = gcd(solution, num)

	return solution

if __name__ == "__main__":
	print solve(10, 20, 30)
