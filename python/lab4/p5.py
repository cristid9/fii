import os

def traverse(path):

	for root, dirs, files in os.walk(path):
		for f in files + dirs:
			full_path = os.path.join(root, f)
			f_type = "dir" if os.path.isdir(full_path) else \
				"file" if os.path.isfile(full_path) else "unknown"
			print ("[%s]" + full_path) % f_type

if __name__ == "__main__":
	traverse(".")

