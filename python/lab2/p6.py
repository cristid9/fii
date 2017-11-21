def f(*args):
	l = []
	x = args[-1]
	lists = args[:-1]
	for li in lists:
		l += li
	result = []
	for e in l:
		if l.count(e) == x:
			result.append(e)
	return set(result)

if __name__ == "__main__":
	print f([1, 2, 3], [2, 3, 4], [4, 5, 6], [4, 1, "test"], 2)
