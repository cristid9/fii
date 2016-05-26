p0 = 0.1
n = 150
succese = 20
\alpha = .05

! invata formulele astea pentru examen

1) H_0 : p = p_0
2) H_a : p > p_0(as di)
3) \alpha = 0.05
4) scorul testului
   z = (p' - p_0) / \sqrt(p_0(1 - p_0))

    p' = succese / n = 20 / 150 = 0.13
    z = (0.13 -0.10) / \sqrt(0.1 * 0.9) / 150 1.36
    z* = qnorm(1 - \alpha) = 1.64
    Decizia
      z = 1.36 < z* = 1.64 => se acceepta ipoteaza nula la \alpha=0.05



Interpretare:
-------------

Cu o incredere de 95% se poate afrima ca procentul rebuturilor este aproximativ 
egal 10%, deci nu a crescut.


II.3
---

p0 = 0.1
n = 110
succese = 15

1) H0: p = p0
2) Ha: p < p0 (as stg)
3) alpha = {0.01, 0.05}
4) z = 1.27

p' = (15/110) = .13

5) z* = gnorm(\alpha, 0.1) = -1.64;

6) Decizia z = 1.27 > z* = -1.64 => se acc H0 la \alpha = 0.05


Cu o incredere de 95% se poate afirma ca procentul clientilror neultimiti eeste
aproximativ egal cu 10%, deci nu a scazut a.i. schimbarea a ffost inutila.


II.4
----
 p0 = 0.025
   n = 128
   succese = 10

1) H0: p = p0
2) Ha: p > p0 (as dr)
3) \alpha = {0.05, 0.01}
4) z = 3.84
5) z* = 1.64
6) Decizia

z = 3.84 > z* = 1.64 => se resp H0 la \alpha=0.05


Cu o incredere de 95% se poate afirma ca procentul a crescut in timp


II.5
----
    p0 = 0.25 (morti)
    n = 42
    succese = 17 (morti)
    \alpha = 0.01

Procentul de purici morti trebuie sa creasca
1) H_0: p = p_0
2) H_a : p > p_0 ()
3) \alpha = 0.01
4) z = 2.31
5) z* = 2.32
6) Decizia
z = 2.31 < z* = 2.32 => se accepta H_0 la \alpha 0.01


pt. \alpha = 0.05 => z* = 1.64
 z = 2.31 > z* = 1.64 => se resp H_0 la \alpha = 0.05morti


