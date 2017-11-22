import os
import shutil

KB = 1000
MB = 1000000

def get_files_by_ext(d, ext):
	fs = []
	for root, dirs, files in os.walk(d):
		for fl in files:
			if os.path.splitext(fl)[1] == ext:
				fs.append(os.path.join(root, fl))

	return fs

def classify(files):
	# criteria 1
	if not os.path.isdir('c1_10kb'):
		os.mkdir('c1_10kb')
	if not os.path.isdir('c1_1mb'):
		os.mkdir('c1_1mb')
	
	if not os.path.isdir('c1_2mb'):
		os.mkdir('c1_2mb')
	
	if not os.path.isdir('c1_5mb'):
		os.mkdir('c1_5mb')
	
	if not os.path.isdir('c1_'):
		os.mkdir('c1_')

	for letter in list(map(chr, range(97, 123))):
		if not os.path.isdir('c2_' + letter):
			os.mkdir('c2_' + letter)

	if not os.path.isdir('c3_alnum'):
		os.mkdir('c3_alnum')

	if not os.path.isdir('c3_not_alnum'):
		os.mkdir('c3_not_alnum')

	for f in files:
		size = os.stat(f).st_size
		basename = f.split('/')[-1]
		print os.path.join('c1_10kb', basename)
		if size < 10 * KB:
			shutil.copyfile(f, os.path.join('c1_10kb', basename))
		elif size < MB: 
			shutil.copyfile(f, os.path.join('c1_1mb', basename))
		elif size < 2 * MB:
			shutil.copyfile(f, os.path.join('c1_2mb', basename))
		elif size < 5 * MB:
			shutil.copyfile(f, os.path.join('c1_5mb', basename))
		else:
			shutil.copyfile(f, os.path.join('c1_', basename))

		if basename[0].isalpha():
			shutil.copyfile(f, os.path.join('c2_' + basename[0], basename))

		if all(letter.isalpha() for letter in basename):
			shutil.copyfile(f, os.path.join('c3_alnum', basename))
		else:
			shutil.copyfile(f, os.path.join('c3_not_alnum', basename))

def clean():
	if os.path.isdir('c1_10kb'):
		shutil.rmtree('c1_10kb')
	
	if os.path.isdir('c1_1mb'):
		shutil.rmtree('c1_1mb')
	
	if os.path.isdir('c1_2mb'):
		shutil.rmtree('c1_2mb')
	
	if os.path.isdir('c1_5mb'):
		shutil.rmtree('c1_5mb')
	
	if os.path.isdir('c1_'):
		shutil.rmtree('c1_')

	if os.path.isdir('c3_alnum'):
		shutil.rmtree('c3_alnum')
	
	if os.path.isdir('c3_not_alnum'):
		shutil.rmtree('c3_not_alnum')

	for letter in list(map(chr, range(97, 123))):
		if os.path.isdir('c2_' + letter):
			shutil.rmtree('c2_' + letter)


if __name__ == "__main__":
	fs = get_files_by_ext('.', '.py')
	classify(fs)
#	clean()
	print fs


