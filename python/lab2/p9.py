import functools

def custom_comp(a, b):
	return ord(a[1][2]) - ord(b[1][2])

def sort_by_tuple_element(*args):
	args = list(*args)
	return sorted(args, key=functools.cmp_to_key(custom_comp))

if __name__ == "__main__":
	print(sort_by_tuple_element([('abc', 'bcd'), ('abc', 'zza')]))
