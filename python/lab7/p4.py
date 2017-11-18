import sys
import os
import hashlib
import json

OUT_FILE = "out.txt"

if __name__ == "__main__":
	target_dir = sys.argv[1]

	files = []

	for f in os.listdir(target_dir):
		cmap = {}
		cmap["name"] = f
		cmap["md5"] = hashlib.md5(open(f).read()).hexdigest()
		cmap["sha256"] = hashlib.sha256(open(f).read()).hexdigest()
		cmap["size"] = os.stat(f).st_size
		cmap["ctime"] = os.stat(f).st_ctime
		cmap["abs_path"] = os.path.join(target_dir, f)
		files.append(cmap)

	with open("out.txt", "w") as f:
		f.write(json.dumps(files))
