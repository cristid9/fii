#! /bin/bash

def check_line_coefficients(point, a, b, c):
	if a * point[0] + b * point[1] + c == 0:
		return True
	return False

def get_lines(points):
	search_interval = range(-100, 100)	
	lines = []

	for point in points:
		for a in search_interval:
			for b in search_interval:
				for c in search_interval:
					if check_line_coefficients(point, a, b, c) and (a, b, c) not in lines:
						lines.append((a, b, c))			
	return lines

if __name__ == "__main__":
	"""
	Not sure if this is the right solution indeed
	"""
	print len(get_lines([(1, 2)]))
