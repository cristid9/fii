def build_dict(string):
	return {c : string.count(c) for c in string}

if __name__ == "__main__":
	print(build_dict("Ana are mere"))
