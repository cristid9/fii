data Nat = Zero | Succ Nat deriving Show

convert::Nat -> Int
convert Zero = 0
convert (Succ n) = 1 + (convert n)

unconvert::Int -> Nat
unconvert 0 = Zero
unconvert n = (Succ (unconvert (n - 1)))

add Zero x = x
add (Succ y) x = (Succ (add x y))
 
imul::Nat -> Nat -> Nat
imul Zero x = Zero
imul (Succ Zero) n = n
imul n (Succ Zero) = n
imul x (Succ y) = imul (add x x) y
  
expNat::Nat -> Nat -> Nat
expNat n Zero = Succ Zero
expNat n1 (Succ n2) = imul (expNat n1 n2) n1 

