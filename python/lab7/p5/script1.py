import os
import pickle
import time

if __name__ == "__main__":
	

	while True:
		fs = os.listdir('.')
		with open('srz.srz', 'wb') as f:
			pickle.dump(fs, f)	
			print "[INFO] Another dump created"			
			
	
		time.sleep(10)
