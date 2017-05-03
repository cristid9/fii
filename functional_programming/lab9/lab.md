Tipul unit
==========

* `()` - asta se numeste unit
* un tip de date cu o singura valoare


 ```haskell
 -- creaza
 f::Int -> ()
 f x = ()
 ```
* Daca `a` are valorile `v1, v2..vn`
  `Maybe a` are valorile: `Just v1, Just v2 .. Just vn, Nothing`

Tipul parametrizat `IO a`
=======================

* `IO a = actiuni care, dupa ce sunt executate, produc o valoare de tip a`
* `IO () = actiune care dupa ce este executat produce un unit`

Compilare
=========

* daca scriu `ghc nume fisier` mi se genereaza un executabil
* Exemplu de program in haskell:
  ```
  main :: IO ()
  main = putStrLn "Hello World!"
  ```
* `putStrLn`
* `(>>)` permite inlantuirea lui `putStrLn`, 
  ignora valoarea produsa de prima
* `getLine` citeste ceva de la tastatura
* `(>>=)` folosesti chestia asta ca sa nu pierzi valoarea din `getLine`
 ca la `(>>)`. Trebuie sa-i dai un lambda ca argument 2.

`do` notation
=============

* Syntactic sugar pentru versiunea 4 de `main`

Tema
====
* fa un executabil care citeste un numar `n` urmat de inca `n` umere 
 si sa afiseze suma lor. (hint: facut functie __recursiva__)

Cod discutat la laborator
=========================

```haskell
main :: IO ()
main = (putStrLn "ana") >> (putStrLn "maria")
```

```haskell
main :: IO ()
main = getLine >> putStrLn "ana"
```

```haskell
main :: IO ()
main = getLine >>= (\s -> (putStrLn ("Hello, " ++ s)))
```

```haskell
-- gen pt secventializare
main :: IO ()
main = (putStrLn "Name") >>= 
    (\_ -> 
        (getLine >>= 
            (\name -> putStrLn "Prenume" >>= 
                (\_ -> 
                    (getLine >>= 
                        (\pren -> putStrLn ("H" ++ pren ++ name ))
                    )
                )
            )
        )
    )
```


```haskell
main :: IO ()
main = do
    x <- putStrLn "Nume"
    nume <- getLine
    y <- putStrLn "Prenume"
    pren <- getLine
    z <- putStrLn ("H " ++ nume ++ " " ++ pren)
    return z
```

```haskell
main :: IO ()
main = (readFile "input.txt") >>= print

 ```
