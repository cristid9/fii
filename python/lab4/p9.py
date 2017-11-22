import sys, os
import inspect
import platform
import multiprocessing

if sys.version_info.major > 2:
	print "Python 3"
else:
	print "Python 3"

print os.getlogin()
print os.path.abspath(sys.argv[0])
print os.path.dirname(os.path.abspath(sys.argv[0]))
print os.path.dirname(os.path.abspath(sys.argv[0])).split(os.sep)
print platform.system()
print multiprocessing.cpu_count()

