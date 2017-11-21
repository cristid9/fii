def f(*args, flag=True, x=1):
	result = []
	for string in args:
		result.append([])
		for ch in string:
			if flag and ord(ch) % x == 0:
				result[-1].append(ch)
			if not flag and not ord(ch) % x == 0:
				result[-1].append(ch)
	return result

if __name__ == "__main__":
	print(f("test", "hello", "lab002", flag=False, x=2))
