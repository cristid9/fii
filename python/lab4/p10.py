import os

def search_by_content(target, to_search):
	result = []
	if os.path.isfile(target):
		with open(target) as f:
			if to_search in f.read():
				result.append(target)

	elif os.path.isdir(target):
		for root, dirs, files in os.walk(target):
			for f in files:
				with open(os.path.join(root, f)) as fl:
					x = fl.read()
					if to_search in x:
						result.append(f)


	else:
		raise ValueError()
	
	return result

if __name__ == "__main__":
	print search_by_content('.', "if")
