-- tipul pentru expresii aritmetice definit in laboratoarele
-- precedente

data Exp = Var String
         | Numar Int
         | Suma Exp Exp
         | Produs Exp Exp deriving Show

-- tipul pentru o valuatie partiala

type ValuationPar = String -> Maybe Int

-- functii ajutatoare din laboratorul precedent

lift2 :: (a -> b -> c) -> Maybe a -> Maybe b -> Maybe c
lift2 f Nothing _ = Nothing
lift2 f _ Nothing = Nothing
lift2 f (Just x) (Just y) = Just (f x y)

sumaMaybe :: Maybe Int -> Maybe Int -> Maybe Int
sumaMaybe = lift2 (+)

produsMaybe :: Maybe Int -> Maybe Int -> Maybe Int
produsMaybe = lift2 (*)

-- functia de evaluare care asociaza unei expresii si unei valuatii
-- partiale o valoare de tip Maybe Int reprezentand fie rezultatul
-- evaluarii (sub forma Just x), fie faptul ca in timpul evaluarii a
-- avut loc o eroare (Nothing).

evalp :: Exp -> ValuationPar -> Maybe Int
evalp (Numar x) _ = Just x
evalp (Var y) valp = valp y
evalp (Suma e1 e2) valp = sumaMaybe (evalp e1 valp) (evalp e2 valp)
evalp (Produs e1 e2) valp = produsMaybe (evalp e1 valp) (evalp e2 valp)

{-

Exercitiul 1

Scrieti o functie empty :: ValuationPar care asociaza Nothing oricarei
variabile.

Exemple:

-- > empty "x"
-- Nothing
-- > empty "y"
-- Nothing
-- > empty "x1"
-- Nothing
-- > empty "result"
-- Nothing

-}

empty :: ValuationPar
empty _ = Nothing

{-

Exercitiul 2

Scrieti o functie update :: ValuationPar -> String -> Maybe Int ->
ValuationPar care primeste trei argumente: o valuatie partiala, o
variabila, o noua valoare :: Maybe Int pentru variabila respectiva si
intoarce o noua valuatie partiala,

Exemple:

-- > (update empty "x" (Just 10)) "x"
-- Just 10
-- > (update empty "x" (Just 10)) "y"
-- Nothing
-- > (update (update empty "x" (Just 10)) "y" (Just 20)) "x"
-- Just 10
-- > (update (update empty "x" (Just 10)) "y" (Just 20)) "y"
-- Just 20
-- > (update (update empty "x" (Just 10)) "y" (Just 20)) "x1"
-- Nothing
-- > (update (update (update empty "x" (Just 10)) "y" (Just 20)) "x" (Just 30)) "x"
-- Just 30
-- > (update (update (update empty "x" (Just 10)) "y" (Just 20)) "x" (Just 30)) "y"
-- Just 20
-- > (update (update (update empty "x" (Just 10)) "y" (Just 20)) "x" (Just 30)) "x1"
-- Nothing

Hint: tineti cont ca update intoarce o *functie*.

-}

update :: ValuationPar -> String -> Maybe Int -> ValuationPar
update f variabila valoare = \x -> valoare

{-

Pana in acest moment, am realizat un evaluator pentru expresii
aritmetice care contin numere, diverse operatii (adunare, impartire,
etc.) si variabile.

Urmatorul pas este sa folosim expresiile aritmetice pe care le-am
definit pentru a construi programe.

Un program va fi alcatuit dintr-o secventa de instructiuni.

Pentru inceput, nu vom avea decat un singur tip de instructiune:
instructiunea de atribuire.  Instructiunea de atribuire este
reprezentata prin constructorul Atrib, care are doua argumente:
variabila (un String) care este atribuita si o expresie aritmetica a
carei valoare va fi memorata in variabila.

-}

data Instr = Atrib String Exp deriving Show

{-

Exercitiul 3

Folosind functia evalp de mai sus, scrieti o functie executaInstr ::
ValuationPar -> Instr -> ValuationPar care primeste la intrare o
valuatie partiala si o instructiune si intoarce o noua valuatie
partiala, obtinuta din valuatia initiala prin actualizarea variabilei
atribuita in instructiune.

Exemple:

-- > (executaInstr empty (Atrib "x" (Suma (Numar 1) (Numar 2)))) "x"
-- Just 3
-- > (executaInstr empty (Atrib "x" (Suma (Numar 1) (Numar 2)))) "y"
-- Nothing
-- > (executaInstr (update empty "x" (Just 10)) (Atrib "x" (Suma (Numar 1) (Numar 2)))) "x"
-- Just 3
-- > (executaInstr (update empty "y" (Just 10)) (Atrib "x" (Suma (Numar 1) (Numar 2)))) "x"
-- Just 3
-- > (executaInstr (update empty "y" (Just 10)) (Atrib "x" (Suma (Numar 1) (Numar 2)))) "y"
-- Just 10
-- > (executaInstr (update empty "y" (Just 10)) (Atrib "x" (Suma (Numar 1) (Numar 2)))) "x1"
-- Nothing

-}

executaInstr :: ValuationPar -> Instr -> ValuationPar
executaInstr pval (Atrib str e) =  (\x -> (evalp e pval))

{-

Pentru inceput, un program va fi o lista de instructiuni.

-}

type Program = [Instr]

{-

Iata un exemplu de program cu trei instructiuni:

-}

prog1 :: Program
prog1 = [Atrib "x" (Suma (Numar 1) (Numar 2)),
         Atrib "y" (Suma (Var "x") (Var "x")),
         Atrib "result" (Produs (Var "x") (Var "y"))]

{- 

Prin conventie, vom folosi deocamdata variabila "result" pentru a
memora valoarea intoarsa de program.

-}

{-

Exercitiul 4

Scrieti o functie executaProgram :: ValuationPar -> Program ->
ValuationPar care primeste la intrare un program si o valuatie
partiala si intoarce valuatia partiala obtinuta dupa executia tuturor
instructiunilor din program.

Exemple:

-- > (executaProgram empty prog1) "x"
-- Just 3
-- > (executaProgram empty prog1) "y"
-- Just 6
-- > (executaProgram empty prog1) "result"
-- Just 18
-- > (executaProgram empty prog1) "x1"
-- Nothing

-}

executaProgram :: ValuationPar -> Program -> ValuationPar
executaProgram valuatie [] = valuatie
executaProgram valuatie (i:is) = executaInstr  (executaProgram valuatie is) i

{-

Exercitiul 5

Scrieti o functie evalProgram :: Program -> Maybe Int care calculeaza
rezultatul executiei unui program (continutul variabilei "result" la
sfarsit).

Exemple:

-- > evalProgram prog1
-- Just 18
-- > evalProgram [Atrib "result" (Suma (Numar 2) (Numar 2))]
-- Just 4
-- > evalProgram [Atrib "x" (Suma (Numar 2) (Numar 2))]
-- Nothing

-}

evalProgram :: Program -> Maybe Int
evalProgram prog = (executaProgram empty prog) "result"

-- plm, mai uita-te pe ele acasa
