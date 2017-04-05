{-

Pana in acest moment, am realizat un evaluator pentru expresii
aritmetice care contin numere si diverse operatii (adunare, impartire,
etc.).

Urmatorul pas este sa permitem ca expresiile sa contina si variabile.

Tipul de date Exp definit mai jos contine expresii care sunt alcatuite
din numere intregi pe 32 de biti (EInt Int), variabile (EVar String),
sume si produse.

-}

import Data.Maybe

data Exp = Var String
         | Numar Int
         | Suma Exp Exp
         | Produs Exp Exp deriving Show

{-

De exemplu, expresia aritmetica "(x + 10) * 2" este reprezentata de
urmatoarea valoare Haskell:

-- > Produs (Suma (Var "x") (Numar 10)) (Numar 2)
-- Produs (Suma (Var "x") (Numar 10)) (Numar 2)

-}

{-

Exercitiul 1

Scrieti o valoare Haskell care sa reprezinte expresia aritmetica "x *
(2 + y)". Verificati in ghci ca nu aveti vreo eroare de sintaxa.


-}

-- Produs (Var "x") (Suma (Numar 10) (Var "y"))


{-

Ce valoare are expresia aritmetica "x + 4"?

Depinde de valoarea lui "x".

Valoarea unei expresii aritmetice care contine variabile depind de
valorile variabilelor respective. De exemplu, pentru x = 0, expresia
aritmetica (x + 10) * 2 are valoarea 20, dar pentru x = 1, are
valoarea 22.

O valuatie este o functie definita pe multimea variabilelor cu valori
in multimea numerelor intregi. O valuatie "tine minte" ce valoare are
fiecare variabila. 

-}

type Valuatie = String -> Int


{-

Cuvantul cheie "type" introduce un *sinonim de tip*. Cu alte cuvinte,
tipul Valuatie este unul si acelasi cu tipul String -> Int, adica
tipul functiilor care primesc la intrare un String si produc la iesire
un Int. Este similar constructiei typedef din limbajul C. Dupa aceasta
definitie, nu exista nicio diferenta intre tipul "Valuatie" si tipul
"String -> Int".

De exemplu, valuatia "val1" de mai jos asociaza variabilei "x" numarul
10, variabilei "y" numarul 20, variabilei "z" numarul 25, si oricarei
alte variabile numarul 0.

-}

val1 :: Valuatie -- echivalent cu val1 :: String -> Int
val1 "x" = 10
val1 "y" = 20
val1 "z" = 25
val1 _ = 0

{-

Exercitiul 2

Scrieti o valuatie val2 care asociaza variabilei "x1" valoarea 100,
variabilei "x2" valoarea 10 si oricarei alte variabile valoarea 999.

-}

val2 :: Valuatie
val2 "x" = 100
val2 "x2" = 10
val2 _ = 999

{-

In continuare vom scrie o functie pentru evaluarea unei expresii
aritmetice care contine potential variabile. Deoarece valoarea
expresiei aritmetice depinde de valorile asociate variabilelor,
functia de evaluare primeste doi parametri:

1) expresia aritmetica care trebuie evaluata;

2) valuatia care asociaza fiecarei variabile un numar intreg.

-}

eval :: Exp -> Valuatie -> Int
eval (Numar x) _ = x               
eval (Var v) val = val v
eval (Produs e1 e2) val = (eval e1 val) * (eval e2 val)
eval (Suma e1 e2) val = (eval e1 val) + (eval e2 val)

{-

Iata cum putem calcula valoarea expresiei "(x + 10) * 2" in valuatia val1:

-- > eval (Produs (Suma (Var "x") (Numar 10)) (Numar 2)) val1
-- 40

-}

{-

Exercitiul 3

Evaluati in ghci expresiile aritmetice "x * (2 + y)", "(x + 10) * 2" si "(x1 + x2) * x" in 
valuatiile val1 si val2.

-- eval (Produs (Var "x") (Suma (Numar 2) (Var "y"))) val2
-- eval (Produs (Suma(Var "x") (Numar 10)) (Numar 2)) val2
-- eval (Produs (Suma (Var "x1") (Var "x2")) (Var "x")) val2
-}

{-

O valuatie *partiala* este o functie care asociaza unei submultimi de
variabile un numar intreg. Reprezentam o valuatie partiala printr-o
functie :: String -> Maybe Int.  De exemplu, valuatia partiala care
asociaza variabilei "x" numarul 10 si variabilei "y" numarul 20 este
reprezentata de urmatoarea functie:

-}

type ValuationPar = String -> Maybe Int

val1p :: ValuationPar
val1p "x" = Just 10
val1p "y" = Just 20
val1p _ = Nothing

{-

Exercitiul 4

Definiti o valuatie partiala care asociaza variabilelor "x", "y" si "z" numerele 10, 20 si respectiv 30.

-}

val2p :: ValuationPar
val2p "x" = Just 10
val2p "y" = Just 20
val2p "z" = Just 30

{-

Exercitiul 5

Completati functia evalp de mai jos.

Exemple:
-- > evalp (Produs (Suma (Var "x") (Numar 10)) (Numar 2)) val1p
-- Just 40
-- > evalp (Produs (Suma (Var "z") (Numar 10)) (Numar 2)) val1p
-- Nothing
-- > evalp (Produs (Suma (Var "z") (Numar 10)) (Numar 2)) val2p
-- Just 80

Hint: veti avea nevoie de functiile sumaMaybe si produsMaybe din laboratoarele anterioare.

-}

sumaMaybe :: Maybe Int -> Maybe Int -> Maybe Int
sumaMaybe (Just n1) (Just n2) = Just (n1 + n2)
sumaMaybe _ Nothing = Nothing
sumaMaybe Nothing _ = Nothing

evalp :: Exp -> ValuationPar -> Maybe Int
evalp (Numar x) _ = Just x
evalp (Var v) pval = pval v
evalp (Produs e1 e2) pval = sumaMaybe (evalp e1 pval) (evalp e2 pval)
--evalp (Suma e1 e2) pval = Just ((evalp e1 pval) + (evalp e2 pval))


