import re

def cen(s):
	if len(s) == 1:
		if lower(s[0]) in 'aeiou':
			return '*'
	if len(s) == 0:
		return ''
	
	if s[0] in 'aeiou' and s[-1] in 'aeiou':
		return re.sub('(.).', r'\1*', s)
	return s

if __name__ == "__main__":
	print cen("ana")
