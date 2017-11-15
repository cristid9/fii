from os import mkdir
from os.path import join

def kill_disk(cale, nr_dir, nr_files, size):
	if depth > 0:
		for i in range(nr_dir):
			mkdir(join('dir' + str(i)))
			kill_disk(join(cale, 'dir' + str(i)), depth - 1, nr_dir, nr_files, size)
		for i in range(nr_files):
			open(join(cale, 'file' + str(i)), 'w').write('a' * size)


if __name__ == "__main__":
	kill_disk('dummy', 3, 3, 3, 1024 * 1024 * 3)
