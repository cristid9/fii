#! /bin/bash

def count_occurences(haystack, needle):
	count = 0
	while True:
		idx = haystack.find(needle)
		if idx == -1:
			break
		count += 1
		print count
		haystack = haystack[idx + 1:]
	return count

if __name__ == "__main__":
	print count_occurences("ana anana ana", "ana") # expected = 4
