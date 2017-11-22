import re
import os

def print_matching_files(d, exp):
	for root, dirs, files in os.walk(d):
		for f in files:
			to_print = False
			prefix = False
			if re.match(exp, f) is not None:
				to_print = True
			else:
				with open(os.path.join(root, f)) as f:
					if re.match(exp, f.read()):
						prefix = True
			
			if to_print and prefix:
				print '>> %s' % f
			
			if to_print:
				print f


if __name__ == "__main__":
	print_matching_files('.', '[0-8]')
