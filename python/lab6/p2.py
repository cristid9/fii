import re

def f(text, x, regex):
	[y for y in re.findall(regex, text) if len(y) <= x]

if __name__ == "__main__":
	f("Foo Bar", 3, "[a-z0-9A-Z]+")
