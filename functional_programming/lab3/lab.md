Lab 3
=====

User-defined data types
=======================

Tipuri enumerative
------------------
```
data Zi = Luni | Marti | Miercuri | ... | Dumminica
-- si numele is valorile cu litera mare
```

```
urm::Zi -> Zi
urm Luni = Marti
.
.
.
```

* fii atent ca trebuie sa derivezi show ca sa poti apela (vezi in cod)
* tipuri de data parametrizabile (linina 58 in cod)

Tema
----
* functiile pe liste pentru listele parametrizabile

Tipuri Algebrice
================

Tema
----
* baza2::Int -> ListaInt
* inversa ^
* conv::Nat -> Int
* uncov::Int -> Nat
* exp x y = x^y
* definit un tip de date pentru arbori binari de cautare
  ABC ( insert
        search
        delete
* AVL sau RedBlack- de facut tip de date
