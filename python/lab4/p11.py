import os

def get_file_info(f):
	size = None
	with open(f) as fl:
		size = len(fl.read())

	return {
		"full_path": os.path.abspath(f),
		"file_size":  size,
		"file_extension": os.path.splitext(f),
		"can_read": os.access(f, os.R_OK),
		"can_write": os.access(f, os.W_OK)
	}

if __name__ == "__main__":
	print get_file_info("p10.py")
