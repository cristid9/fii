#! /bin/bash

def switch_case(s):
	result = ""
	
	for c in s:
		if c == c.upper():
			result += "_"
		result += c.lower()
	return result[1:]

if __name__ == "__main__":
	print switch_case("UpperCamelCase")
