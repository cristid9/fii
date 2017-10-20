from matrices_provider import get_matrices

def compute_determinant(m):
    return (m[0][0] * m[1][1] * m[2][2] +\
            m[0][2] * m[1][0] * m[2][1] +\
            m[0][1] * m[1][2] * m[2][0]) -\
           (m[0][2] * m[1][1] * m[2][0] +\
            m[0][1] * m[1][0] * m[2][2] +\
            m[0][0] * m[1][2] * m[2][1])

def get_transpose(m):
    return [
        [m[0][0], m[1][0], m[2][0]],
        [m[0][1], m[1][1], m[2][1]],
        [m[0][2], m[1][2], m[2][2]]
    ]

def get_adjugate(t):
    mi_1 = t[1][1] * t[2][2] - t[2][1] * t[1][2]
    mi_2 = -(t[1][0] * t[2][2] - t[2][0] * t[1][2])
    mi_3 = t[1][0] * t[2][1] - t[2][0] * t[1][1]
    mi_4 = -(t[0][1] * t[2][2] - t[2][1] * t[0][2])
    mi_5 = t[0][0] * t[2][2] - t[2][0] * t[0][2]
    mi_6 = -(t[0][0] * t[2][1] - t[2][0] * t[0][1])
    mi_7 = t[0][1] * t[1][2] - t[1][1] * t[0][2]
    mi_8 = -(t[0][0] * t[1][2] - t[1][0] * t[0][2])
    mi_9 = t[0][0] * t[1][1] - t[1][0] * t[0][1]

    return [
        [mi_1, mi_2, mi_3],
        [mi_4, mi_5, mi_6],
        [mi_7, mi_8, mi_9]
    ]

def get_inverse(m_star, det):
    return [
        [m_star[0][0] * (1.0 / det), m_star[0][1] * (1.0 / det), m_star[0][2] * (1.0 / det)],
        [m_star[1][0] * (1.0 / det), m_star[1][1] * (1.0 / det), m_star[1][2] * (1.0 / det)],
        [m_star[2][0] * (1.0 / det), m_star[2][1] * (1.0 / det), m_star[2][2] * (1.0 / det)]
    ]

def get_answer(iv, r):
    return [
        iv[0][0] * r[0] + iv[0][1] * r[1] + iv[0][2] * r[2],
        iv[1][0] * r[0] + iv[1][1] * r[1] + iv[1][2] * r[2],
        iv[2][0] * r[0] + iv[2][1] * r[1] + iv[2][2] * r[2]
    ]

if __name__ == "__main__":
    m, r = get_matrices()
    det = compute_determinant(m)
    if det == 0:
        print 'Determinant 0'
        exit(1)
    t = get_transpose(m)
    a_s = get_adjugate(t)
    iv = get_inverse(a_s, det)
    result = get_answer(iv, r)

    print result

