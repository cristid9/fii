def f(a, b):
	intersection = [x for x in a + b if x in a and x in b]
	reunion = list(set(a + b))
	a_minus_b = [x for x in a if x not in b]
	b_minus_a = [x for x in b if x not in a]

	return (intersection, reunion, a_minus_b, b_minus_a)
	

if __name__ == "__main__":
	print(f([1, 2, 3], [3, 4, 5]))
