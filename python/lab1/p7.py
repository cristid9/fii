#! /bin/bash

def fazan(char_len, *s):
	i = 1
	while i < len(s):
		if s[i - 1][0:char_len] != s[i][:char_len-1:-1]:
			return False
		i += 1
	return True

if __name__ == "__main__":
	print fazan(2, 'ana', 'cana')
