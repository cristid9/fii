import re

INPUT_FILE = "system.txt"
VARIABLES = ["x", "y", "z", "x", "y", "z"]

def get_matrices():
    matrix_1 = [
        [0, 0, 0],
        [0, 0, 0],
        [0, 0, 0]
    ]

    matrix_result = [0, 0, 0]

    with open(INPUT_FILE) as f:
        content = f.readlines()
        i, k = 0, 0
        for line in content:
            line = line.replace(' ', '')
            x = re.findall(r'[-+]*[0-9]*x', line)
            y = re.findall(r'[-+]*[0-9]*y', line)
            z = re.findall(r'[-+]*[0-9]*z', line)
            r = re.findall(r'=[ ]*[-+]*[0-9]+', line)

            if len(x) == 0:
                x = 0
            elif x[0].strip() == 'x' or x[0].strip() == '+x':
                x = 1
            elif x[0].strip() == '-x':
                x = -1
            else:
                x = float(x[0][0:-1])

            if len(y) == 0:
                y = 0
            elif y[0] == 'y' or y[0] == '+y':
                y = 1
            elif y[0] == '-y':
                y = -1
            else:
                y = float(y[0][0:-1])

            if len(z) == 0:
                z = 0
            elif z[0].strip() == 'z' or z[0].strip() == '+z':
                z = 1
            elif z[0].strip() == '-z':
                z = -1
            else:
                z = float(z[0][0:-1])


            r = float(r[0][1:])

            matrix_1[i][0] = x
            matrix_1[i][1] = y
            matrix_1[i][2] = z

            matrix_result[k] = r

            i += 1
            k += 1

    return matrix_1, matrix_result

def main():
    print get_matrices()

