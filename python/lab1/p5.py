#! /bin/bash

def has_special_chars(s):
	count = 0
	for c in s:
		if c in "\r\t\n\a\b\f\v":
			return True
	return False
	
if __name__ == "__main__":
	print has_special_chars("\foo\bar")
