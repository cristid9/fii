def f(*args):
	max_index = max([len(e) for e in args])

	result = []
	for i in range(0, max_index):
		result.append(tuple(None for i in range(0, max_index)))
	
	for i in range(0, max_index):
		for j, e in enumerate(args):
			if i >= len(e):
				tmp = list(result[i])
				tmp[j] = None
				result[i] = tmp
			else:
				tmp = list(result[i])
				tmp[j] = e[i]
				result[i] = tmp

	return result

if __name__ == "__main__":
	print(f([1,2,3,4], [5,6,7], ["a", "b", "c" ]))
