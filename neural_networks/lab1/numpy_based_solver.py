import numpy
from matrices_provider import get_matrices

if __name__ == "__main__":
    m, r = get_matrices()
    det = numpy.linalg.det(m)

    if int(det) == 0:
        print "Determinat 0 "
        exit(0)

    m = numpy.array(m)
    r = numpy.array(r)

    print numpy.linalg.lstsq(m, r)[0]
