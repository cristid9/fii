def is_prime(n):
	
	for i in range(2, n):
		if n % i == 0:
			return False
	
	return True

def extract_biggest_prime(s):
	import re
	numbers = [int(n) for n in re.findall("\d+", s)]

	max_prime = -1
	for number in numbers:
		if is_prime(number) and number > max_prime:
			max_prime = number

	return max_prime


if __name__ == "__main__":
	print extract_biggest_prime('ahsfaisd35biaishai23isisvdshcbsi271cidsbfsd97sidsda')
