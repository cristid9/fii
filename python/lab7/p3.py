import sys
import os
import hashlib
import datetime

def find_duplicates(root_file, output_file):
	found_files = {}
	out = open(output_file, 'w')

	for (root, directories, files) in os.walk(root_file):
		for fileName in files:
			full_fileName = os.path.join(root, fileName)
			hf = hashlib.sha256(open(full_fileName).read()).hexdigest()
			
			for k in found_files:
				if found_files[k] == hf:
					out.write(k + " <===> " + full_fileName)		

			found_files[full_fileName] = hf
		
	out.close()


if __name__ == "__main__":
	root_file = sys.argv[1]

	time1 = datetime.datetime.now()
	find_duplicates(root_file, "out.txt")
	time2 = datetime.datetime.now()

	print time2 - time1
