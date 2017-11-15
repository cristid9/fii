import os.path

def probl_2(path):
	if os.path.isfile(path):
		print open(path, 'r').read(4096)
	elif os.path.isdir(path):
		print os.listdir(path)
	else:
		print  "Cale inv"

if __name__ == "__main__":
	probl_2('.')
