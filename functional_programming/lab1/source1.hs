-- cauta HOOGLE pe net
-- f :: Int -> Int <- nu mai face type inference 

f :: Num a => a -> a
f x = x + 2
g x y = x * y
perimeter r = 2 * pi * r

ff :: Int -> Float
ff x = fromIntegral x

-- daca pui fact de 0 dupa fact n ruleaza la infinit
fact 0 = 1
fact n = n * (fact (n - 1))
-- ^^^^ partea asta e se cheama pattern

sum__ 0 = 0
sum__ n = n + (sum__ (n - 1))

functie = 1 + 2

-- :t posibil utila, calculeza tipul expresiei
-- *Main> :t 42
-- 42 :: Num a => a 42 are tipul a daca a face parte in casa Num

h x = not x

