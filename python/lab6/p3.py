def f(text, lista):
	li = []

	for x in lista:
		li += re.findall(x, text)
	
	return li
	
if __name__ == "__main__":
	print f("Foo bar", ["[a-z]+"])
