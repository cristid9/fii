#! /bin/bash


def count_words(s):
	'''
	s as in sentence
	'''

	for sign in [',', ';', '?', '!', '.']:
		s = s.replace(sign, '')

	return len(s.split())

if __name__ == "__main__":
	print count_words("  foo, bar;")
	
