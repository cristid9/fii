{-

Pana acum am vazut cum se poate crea un tip de date algebric pentru
expresii aritmetice si cum se pot evalua astfel de expresii.

Dar este incomod sa le scriem de mana.

Am avea nevoie de un parser, adica de un program care sa transforme
un sir de caractere reprezentand o expresie aritmetica intr-o valoare
Haskell de tip Exp.

De exemplu, rezultatul parsarii sirului de caractere "(3 + 4) * 5" ar
trebui sa fie "Produs (Suma (Numar 3) (Numar 4))".

Vom implementa parsarea in doua etape:

1) etapa de tokenizare
2) etapa de parsare propriu-zisa

In acest fisier vom implementa prima etapa.

Tokenizarea, sau analiza lexicala, transforma un sir de caractere
intr-un sir de tokenuri. De exemplu, "(33 + 424) * 5" va fi transformat
in:

1) paranteza deschisa
2) numarul 33
3) caracterul '+'
4) numarul 424
5) paranteza inchisa
6) caracterul '*'
7) numarul 5

-}

-- vom avea nevoie de modulul Data.Char petru diverse functii utile
import Data.Char
import Data.Maybe

-- valorile de tip Token corespund tuturor tokenurile de care avem nevoie
-- pentru inceput, vom trata doar '+', '*' si numerele intregi
data Token = TInt String
           | TSuma
           | TProdus
             deriving Show

{-

Exercitiul 1

Definiti functia skipWhiteSpace, care primeste la intrare un sir de
caractere si intoarce sirul de caractere fara spatiile de la inceput.

Exemple:
-- > skipWhiteSpace "  3 +  5 "
-- "3 +  5 "
-- > skipWhiteSpace "2 + 4 "
-- "2 + 4 "

In rezolvare, tineti cont ca String nu este altceva decat un sinonim
pentru [Char] (un String este o lista de Char).

-}
skipWhiteSpace :: String -> String
skipWhiteSpace [] = [] 
skipWhiteSpace (x:xs) = if x == ' ' then skipWhiteSpace(xs) else x:xs

{-

Exercitiul 2

Definiti functia getInteger, care primeste la intrare un sir de caractere si
intoarce o pereche de siruri de caractere:

- prima componenta a perechii contine cifrele cu care incepe sirul
primit ca argument;
- a doua componenta, restul sirului.

Exemple:
-- > getInteger "123  + 23"
-- ("123", "  + 23")
-- > getInteger " 123 + 23 * 3"
-- ("", " 123 + 23 * 3")
-- > getInteger "123123123123 "
-- ("123123123123", " ")

Hint:
Ce face functia isDigit, care face parte din modulul Data.Char, pe care l-ati
importat la inceputul fisierului?
-- > isDigit '3'
-- > isDigit 'a'
-- > isDigit ' '
-}

getInteger :: String -> (String, String)
getInteger [] = ([], [])
getInteger (x:xs) = 
    if (isDigit x) then 
        (x:(fst (getInteger xs)), (snd (getInteger xs))) 
    else
        ("", x:xs)

{-

Exercitiul 3

Definiti functia tokenNext, care primeste la intrare un sir de caractere si
intoarce o valoare de tip Maybe (Token, String):

- valoarea intoarsa este Nothing daca sirul primul ca argument nu
incepe cu unul din tokenurile valide
- valoare intoarsa este Just (x, y) daca sirul primul ca argument incepe
cu tokenul x :: Token si restul sirului este y

Exemple:

-- > tokenNext "+ * 123"
-- Just (TSuma, " * 123")
-- > tokenNext "123123 12 +"
-- Just (TInt "123123", " 12 +")
-- > tokenNext "* 1 + 2"
-- Just (TProdus, " 1 + 2")
-- > tokenNext "a + 1"
-- Nothing
-- > tokenNext " 1 + 2"
-- Nothing
-}

tokenNext :: String -> Maybe (Token, String)
tokenNext [] = Nothing
tokenNext (x:xs) | x == '+' = Just (TSuma, xs)
                 | x == '*' = Just (TProdus, xs)
                 | isDigit x = Just (TInt (fst (getInteger (x:xs))), snd (getInteger (x:xs)))
                 | otherwise = Nothing

{-
Exercitiul 4

Definiti functia tokenize, care primeste la intrare un sir de
caractere si intoarce o valoare de tip Maybe [Token]:

- Nothing daca sirul dat ca parametru nu contine tokenuri valide; 

- Just l daca l :: [Token] este chiar lista de tokenuri din sirul dat
la intrare.

Exemple:

-- > tokenize "1+2"
-- Just [TInt "1", TSuma, TInt "2"]
-- > tokenize "1+2*3"
-- Just [TInt "1", TSuma, TInt "2", TProdus, TInt "3"]
-- > tokenize "12+23*34"
-- Just [TInt "12", TSuma, TInt "23", TProdus, TInt "34"]
-- > tokenize "12 + 23 * 34"
-- Just [TInt "12", TSuma, TInt "23", TProdus, TInt "34"]
-- > tokenize " 12 + 23 * 34"
-- Just [TInt "12", TSuma, TInt "23", TProdus, TInt "34"]
-- > tokenize "     12 + 23 * 34"
-- Just [TInt "12", TSuma, TInt "23", TProdus, TInt "34"]
-- > tokenize "     12 +   23      *   34    "
-- Just [TInt "12", TSuma, TInt "23", TProdus, TInt "34"]
-- > tokenize "12+2 3*34"
-- Just [TInt "12", TSuma, TInt "2", TInt "3", TProdus, TInt "34"]
-- > tokenize "1 2 3 +"
-- Just [TInt "1", TInt "2", TInt "3", TSuma]
-- > tokenize "a1 2 3 +"
-- Nothing
-- > tokenize "1 _ 2 3 +"
-- Nothing
-- > tokenize "1 / 2"
-- Nothing

Incercati si alte exemple.

Hint: daca v este o valoare de tip Maybe a, puteti face o analiza de cazuri folosind
constructia "case" in felul urmator:

case v of
  Just x  -> 1
  Nothing -> 2

Expresia de mai sus se evalueaza la 1 daca v este de forma Just x si
la 2 daca v este Nothing.

-}

-- nu merge la operatorii invalizi

tokenize :: String -> Maybe [Token]
--tokenize [] = Nothing
--tokenize (x:xs) =  
--    if x /= '*' && x /= '+' && not(isDigit x) && x /= ' ' then
--        Nothing
--    else
--        Just ((fst (fromJust ((tokenNext (x:xs))))) : (fromMaybe [] (tokenize (snd (fromJust (tokenNext (x:xs)))))))

tokenize l = if (skipWhiteSpace l) == [] then Just []
    else case  (tokenNext (skipWhiteSpace l)) of
       Nothing -> Nothing
       Just (f, s) -> case (tokenize s) of
           Nothing -> Nothing
           Just lista -> Just (f:lista)

