data Zi = Luni | Marti | Miercuri | Duminica deriving Show

urm::Zi -> Zi
urm Luni = Marti
urm Marti = Miercuri

data Valadev = Fals | Adevarat deriving Show

neg::Valadev -> Valadev
neg Fals = Adevarat
neg Adevarat = Fals

conj::Valadev -> Valadev -> Valadev
conj Adevarat Adevarat = Adevarat
conj _ _ = Fals

convert::Bool -> Valadev
convert True = Adevarat
convert False = Fals

convert2::Valadev -> Bool
convert2 Adevarat = True
convert2 Fals = False

-- astia doi se numesc constructori, Intul ala este parametrul constructorului
data OInt = UnIntreg Int | NiciunIntreg deriving Show

imp::Int -> Int -> OInt
imp _ 0 = NiciunIntreg
imp x y = UnIntreg (div x y)

imp'::OInt -> OInt -> OInt
imp' NiciunIntreg NiciunIntreg = NiciunIntreg
imp' _ NiciunIntreg = NiciunIntreg
imp' NiciunIntreg _ = NiciunIntreg
imp' (UnIntreg x) (UnIntreg 0) = NiciunIntreg
imp' (UnIntreg x) (UnIntreg y) = UnIntreg (div x y)

data Lista = Vida | Cons Int Lista deriving Show

numElem::Lista -> Int
numElem Vida = 0
numElem (Cons i t) = 1 + (numElem t)


customS::Lista -> Int
customS Vida = 0
customS (Cons i t) = i + (customS t)

add'::Lista -> Int -> Lista
add' Vida el = (Cons el Vida)
add' (Cons x l) el = (Cons x (add' l el))

unconvert::[Int] -> Lista
unconvert [] =  Vida
unconvert (x:l) = (Cons x (unconvert l))

data Lista2 a = Vida2 | Cons2 a (Lista2 a) deriving Show

-- cica e la fel cu cea de la punctul precedent
-- convert2::(Lista2 a)-> [a]
-- convert2 (Cons2 a l) = 

data Nat = Zero | Succ Nat deriving Show


add::Nat -> Nat -> Nat
add Zero x = x
add (Succ y) x = (Succ (add x y))

imul::Nat -> Nat -> Nat
imul Zero x = Zero
imul (Succ y) x = add (Succ y) x

