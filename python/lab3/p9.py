import itertools

def operatii(*a):
	rez = {}
	for i in range(len(a)):
		for j in range(i + 1, len(a)):
			rez[str(a[i]) + '|' + str(a[j])] = list(a[i] | a[j])
			rez[str(a[i]) + '&' + str(a[j])] = list(a[i] & a[j])
			rez[str(a[i]) + '-' + str(a[j])] = list(a[i] - a[j])
			rez[str(a[i]) + '-' + str(a[j])] = list(a[i] - a[j])
	return rez

from pprint import pprint

pprint(operatii({1, 2}, {2, 1}))
