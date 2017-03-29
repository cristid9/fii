{-

Mai jos avem un tip de date pentru expresii aritmetice cu numere
(intregi pe 32 de biti), + si *.

De exemplu, expresia matematica (3 + 4) * 5 este reprezentata de
valoarea Haskell:

-- > Produs (Suma (Numar 3) (Numar 4)) (Numar 5)
-- Produs (Suma (Numar 3) (Numar 4)) (Numar 5)

-}

data Exp = Numar Int
         | MinusUnar Exp
         | MinusBinar Exp Exp
         | Suma Exp Exp
         | Produs Exp Exp
         | Div Exp Exp
         deriving Show

{-

Exercitiul 1

Cum reprezentam expresia aritmetica 4 * (3 + 2) * 2?

-}


-- (Produs (Produs (Numar 4) (Suma (Numar 3) (Numar 2))) (Numar 2))


{-

Dandu-se o expresie aritmetica, putem calcula valoarea acesteia
folosind functia "eval":

-}

eval :: Exp -> Int

eval (MinusUnar e) = -eval(e)
eval (MinusBinar e e2) = eval(e) - eval(e2)
eval (Numar n) = n
eval (Suma e1 e2) = (eval e1) + (eval e2)
eval (Produs e1 e2) = (eval e1) * (eval e2)
eval (Div e1 e2) = (eval e1) `div` (eval e2)


{-

Exercitiul 2

Extindeti tipul Exp cu constructori pentru:

1) minus unar (e.g. MinusUnar (Numar 5) reprezinta expresia "-5")
2) minus binar (e.g. MinusBinar (Numar 3) (Numar 3) reprezinta expresia "3-3")

Adaptati functia eval astfel incat sa trateze si cazul noilor
constructori.

Evaluati folosind functia voastra expresiile -(3 + 4) si ((-3) * 4) +
(10 * 2).

-}


{-

Exercitiul 3

Extindeti expresiile cu operatia de impartire.

Ce se intampla in cazul unei impartiri prin 0?

-}
--  *** Exception: divide by zero

