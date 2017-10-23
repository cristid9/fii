def comp_val(a, b):
	types = [dict, set, list, tuple]
	indici = [list, tuple]
	if type(a) == type(b):
		if type(a) not in types:
			return a == b
		if len(a) != len(b):
			return False
		if type(a) in indici:
			for i in range(0, len(a)):
				if comp_val(a[i], b[i]) == False:
					print a, b
					return False
			return True
		else:
			a, b, c = comp_dict(a, b)
			if len(a) + len(b) + len(c) == 0:
				return False
			return True
	else:
		return False

def comp_dict(a, b):
	doar_a = []
	doar_b = []
	valori_diferite = []
	for k in a:
		if k not in b:
			doar_a.append(k)

	for k in b:
		if k not in a:
			doar_b.append(k)
		else:
			r = comp_val(a[k], b[k])
			if r == False:
				valori_diferite.append(k)

	return (valori_diferite, doar_a, doar_b)

if __name__ == "__main__":
	print comp_dict({'a': 1, 'b': 1}, {'a': 1, 'b': [1, 2], 'c': 3})
