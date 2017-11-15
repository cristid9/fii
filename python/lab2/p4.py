#! /bin/bash

def operate_list(a, b):
	"""
	* sets union
	* sets intersection
    * set a minus set b
	* set b minus set a
	"""
	a_b_union = list(set([n for n in a + b]))
	a_b_intersection = list(set([n for n in a + b if n in a and n in b]))
	a_b_minus = [n for n in a if n not in b]
	b_a_minus = [n for n in b if n not in a]

	return (a_b_union, a_b_intersection, a_b_minus, b_a_minus)

if __name__ == "__main__":
	for operation in operate_list([1, 2, 3], [3, 4, 5]):
		print operation
