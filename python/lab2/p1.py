#! /bin/bash

def nth_fibonacci(n):
	if n == 1 or n == 2:
		return 1
	return nth_fibonacci(n - 1) + nth_fibonacci(n - 2)

def get_fibonacci_list(amount):
	numbers = []

	for i in range(1, amount + 1):
		numbers.append(nth_fibonacci(i))	

	return numbers

if __name__ == "__main__":
	print get_fibonacci_list(8)
