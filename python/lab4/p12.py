import os
import functools

def get_dirs_info(p):
	if not os.path.isdir(p):
		return None

	total_size = 0
	fs = {}
	ds = {}

	for root, dirs, files in os.walk(p):
		for fl in files:
			with open(os.path.join(root, fl)) as f:
				total_size += len(f.read())
			path = root.split('/')
			
			if '..' in path:
				path.remove('..')
			
			if '.' in path:
				path.remove('.')
			
			depth = len(path)
			if depth not in fs.keys():
				fs[depth] = []
			fs[depth].append(fl)
						
		for d in dirs:
			ds[os.path.join(root, d)] = get_dirs_info(os.path.join(root, d))	
			

	return {
		"full_path": os.path.abspath(p),
		"total_size": total_size,
		"files": fs,
		"dirs": ds
	}


def cmp1(x, y):
	if 2 not in dirs[x]["files"].keys():
		x = 0
	else:
		x = len(dirs[x]["files"][2]) 

	if 2 not in dirs[y]["files"].keys():
		y = 0
	else:
		y = len(dirs[y]["files"][2]) 

	return y - x

def cmp2(x, y):
	return dirs[y]["total_size"] - dirs[x]["total_size"]

def cmp3(x, y):
	return max([len(s) for s in dirs[y]["files"].values()]) - max([len(s) for s in dirs[x]["files"].values()])

if __name__ == "__main__":
	from pprint import pprint
	retval = get_dirs_info('..')
	dirs = retval["dirs"]
	dirst = sorted(dirs.keys(), key=functools.cmp_to_key(cmp1))
	dirss = sorted(dirs.keys(), key=functools.cmp_to_key(cmp2))
	dirsm = sorted(dirs.keys(), key=functools.cmp_to_key(cmp3))

	with open("output.txt", "w") as f:
		f.write(str(dirst))	

	with open("size.txt", "w") as f:
		f.write(str(dirss))

	with open("lungime.txt", "w") as f:
		f.write(str(dirsm))



	

