import sys
import os
import time
import random
import datetime
import hashlib

if __name__ == "__main__":
	a, b = int(sys.argv[1]), int(sys.argv[2])

	prog_time = datetime.datetime.now().minute
	while True:
		x = random.randint(a, b)
		time.sleep(x)
		current_time = datetime.datetime.now().minute
		print current_time - prog_time

