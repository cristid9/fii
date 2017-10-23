ops = {    
    "+": lambda a, b: a + b,     
    "*": lambda a, b: a * b,
    "/": lambda a, b: a / b,
    "%": lambda a, b: a % b,
	'^': lambda a, b: a ** b
}

def a(operator, *a, **k):
	return ops[operator](a, k)

def apply_op(operator, a, b):
	return ops[operator](a, b)

if __name__ == "__main__":
	print apply_op('/', 1, 1)
