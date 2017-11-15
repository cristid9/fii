import re

def extract(text):
	return re.findall("[a-z0-9A-Z]+", text)

if __name__ == "__main__":
	print extract("Foo Bar")
