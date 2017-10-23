#! /bin/bash

def count_vowels(s):
	count = 0
	for c in s:
		if c.lower() in "aeiou":
			count += 1
	return count

if __name__ == "__main__":
	print count_vowels("Foo Bar")
