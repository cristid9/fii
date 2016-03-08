# This is just a quick poc that I wrote in order to understand the
# algorithm better.

from __future__ import print_function

def karatsuba(num1, num2):
    if len(num1) == 1 or len(num2) == 1:
        return str(int(num1) * int(num2))

    m = max(len(num1), len(num2))
    m2 = int(m / 2)

    high1, low1  = num1[:m2:], num1[m2::]
    high2, low2  = num2[:m2:], num2[m2::]

    z0 = int(karatsuba(low1, low2))
    z1 = int(karatsuba((str(int(low1) + int(high1))),
        (str(int(low2) + int(high2)))))
    z2 = int(karatsuba(high1, high2))

    return str(z2 * (10 ** (2 * m2)) + ((z1 - z2 - z0) * (10 ** (m2))) + (z0))

print(karatsuba("11", "12"))
