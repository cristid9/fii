def unice_duplicate(s):
	unice = [e for e in s if s.colunt(e)==1]
	duplicate = [e for e in s if s.count(e) > 1]
	return (unice, duplicate)

print unice_duplicate([1, 2, 3, 4])
