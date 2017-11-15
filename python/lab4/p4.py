import os.path

def function(path):
	if os.path.isdir(path):
		for k in os.listdir(path):
			function(os.path.join(path, k))
	print path


if __name__ == "__main__":
	function(".")
	

