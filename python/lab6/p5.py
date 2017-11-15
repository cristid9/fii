import re

def find_match(path, attrs):
	content = open(path, 'r').read()
	r = re.findall("<[a-zA-Z = \./_\-]+>", content)
	print(r)
