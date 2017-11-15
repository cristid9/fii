import os.path

def function(src, dest, buffer):
	if not os.path.isfile(src) or not os.path.isfile(dest):
		return
	
	bsn = os.path.basename(src)
	while os.path.exists(os.path.join(bsn, dst)):
		name, ext = os.path.splitext(bsn)
		name = name + '_c'
		bsn = name + ext

	f = open(os.path.join(bsn, dst), 'w')
	s = open(src, 'r')
	wrt = s.read(buffer)
	while len(wrt) > 0:
		f.write(wrt)
		wrt = s.read(buffer)

	f.close()
	s.close()

function('p5.py', 'foo', 10)
