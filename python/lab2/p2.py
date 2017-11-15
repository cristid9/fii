#! /bin/bash

def is_prime(n):
	for i in range(2, n):
		if n % i == 0:
			return False
	return True

def filter_primes(numbers):
	primes = []
	for n in numbers:
		if is_prime(n):
			primes.append(n)

	return primes


if __name__ == "__main__":
	print filter_primes([i for i in range(1, 100)])
