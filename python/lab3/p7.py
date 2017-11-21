fs = {
    "print_all": lambda *a, **k: print(a, k),
    "print_args_commas": lambda *a, **k: print(a, k, sep=", "),
    "print_only_args": lambda *a, **k: print(a),
    "print_only_kwargs": lambda *a, **k: print(k)
}

def apply_function(name, *a, **kw):
	return fs[name](*a, **kw)

if __name__ == "__main__":
	print(apply_function("print_all", 1, a=1))
