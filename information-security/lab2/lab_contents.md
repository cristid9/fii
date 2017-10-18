Lab2
====

Problema 1
----------

Given the diagram

```
                             # y
                            / \  
                             |
                             |
                             | {w, g}
                             |
#--------------------------->@----------------# w
x        {r, t}              z      {a, w}    |
                                              | {d}
                                              |
                                              \/
                                              () u
```
Answer the following:
---------------------
  * `can_share(r, x, w, G)`
  * `can_share(g, x, y, G)`
  * `can_share(d, z, u, G)`


Problema 2
----------

Homework (week 2-5) Implement a `can_share` predicate. Simulate it 
on a model with initial state, established subject which shouldn't 
posses certain rights and verify the safety of the system.

Having as input: n - number of vertices, e - number of edges

```
n e
a b {r, t}
C D {r, g}
```
