import sys

if __name__ == "__main__":
	try:
		a, b = int(sys.argv[1]), int(sys.argv[2])
	except IndexError:
		print "nu sunt doua numere"
		sys.exit()
	except ValueError:
		print "nu sunt numere"
		sys.exit()

print (a+b)
print (a-b)
print (a*b)

try:
	print a / b
except ZeroDivisionError:
	print "infinit"
		
