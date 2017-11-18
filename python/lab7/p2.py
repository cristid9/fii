import datetime
 
def is_prime_2(number):
	cond = True
	for i in range(2, number):
		if number % i == 0:
			cond = False

	return cond

def is_prime_1(number):
	for i in range(2, number):
		if number % i == 0:
			return False
	return True

if __name__ == "__main__":
	timep11 = datetime.datetime.now()
	is_prime_1(1000000)
	timep12 = datetime.datetime.now()
	print timep11, timep12


	timep21 = datetime.datetime.now()
	is_prime_2(1000000)
	timep22 = datetime.datetime.now()
	print timep21, timep22

	print str(timep12 - timep12) + " <=> " + str(timep22 - timep21)
