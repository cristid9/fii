import zipfile
import pickle
import os
import datetime
import time

LIMIT = 100000 # 100kb

def to_minute(second):
	return second / 60

if __name__ == "__main__":

	indexed_files = []

	z = zipfile.ZipFile("foo.zip", mode='w')
	while True:
		current_files = None

		with open("srz.srz") as f:
			current_files = pickle.load(f)

		for f in current_files:
			if f in indexed_files:
				continue

			st = os.stat(f)
			a = datetime.datetime.now()
			b = datetime.datetime.fromtimestamp(st.st_mtime)

			if st.st_size < LIMIT and to_minute((a - b).total_seconds()) <= 5:
				z.write(f)
				indexed_files.append(f)
				print "[DUMP INFO]" + f + " dumped params: " + str(st.st_size) + ", " + str(to_minute((a - b).total_seconds()))

		# update the configuration after a break of 5 minutes
		time.sleep(300)

