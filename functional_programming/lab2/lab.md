Tupluri
=======

```
> (True, 'a')
> (1, False)
> ('a', 'a')
> ()
```

Functii tupluri
---------------

* fst - primul element din tuplu
* snd - al doilea element din tuplu

Liste
=====

Definitie
---------
O lista de tip lista de `[a]` este :
- sau lista vida notata cu `[]`
- sau lista care incepe cu un element `x` de tip `a` (`x::a`) si continua
  cu o lista `l::[a]` notata `x:l`

Misc
----
- `:` si `[]` se numesc constructori


Sintaxa
-------
```
> [1, 2, 3, 4]
> [] -- lista vida
> [1, 2, 3] --> 1:(2:(3:([]))) -- asa e reprezentata o lista

```

if-then/else
============
Structura:

```
if exp then
    exp_1
else
    exp_2
```

`if-then/else` este o expresie:
```
(if False then 1 else 2) * 2
```

Garzi (mai idiomatic decat `if-then/else`)
==========================================

Vezi exemplul 5.


Tema 2
======
* Faceti o functie `pune_la_sfarsit` si care primeste `a -> [a] -> [a]`
  ```
  pls 7 [1, 2, 3] ====> [1, 2, 3, 7]
  ```
* Faceti o functie `contine` care primeste `[a] -> a -> Bool`
* Concatenare `[a] -> [a] -> [a]`
* Invers `[a] -> [a]`
* Pos `[a] -> Int ->a` nr de la pozitia aia
* elem impar `[Integer] -> [Integer]` elementele de pe pozziti impare
