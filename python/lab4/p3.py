from os import environ

def functie(nume):
	f = open(nume, 'w')

	for k in environ:
		f.write(k + '\t' + environ[k])
	f.close()

if __name__ == "__main__":
	functie("text.txt")
