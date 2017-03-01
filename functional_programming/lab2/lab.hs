import Data.List

fst3 (x, y, z) = x

count [] = 0
count (x:l) = 1 + count l

-- merge inversata ordinea
sum_ [] = 0
sum_ (x:l) = x + sum l

sum_odd [] = 0
sum_odd (x:l) = if x `mod` 2 == 1 then x + sum_odd l else sum_odd l

-- garzi
sum_odd2 [] = 0
sum_odd2 (x:l) | x `mod` 2 == 1 = x + sum_odd l
               | otherwise = sum_odd l

sum_odd_pos [] = 0
sum_odd_pos [x] = x
sum_odd_pos (x:y:xs) = x + sum_odd_pos xs 

-- primeste un nr si intoare lista cu reprezentarea in baza 2
get_base2_repr 0 = [0]
get_base2_repr 1 = [1]
get_base2_repr a = ((a `mod` 2):(get_base2_repr (a `div` 2)))

-- inversa
get_dec_repr [] = 0
get_dec_repr (x:l) = x * (2 ^ count(x:l)) + get_dec_repr l


g (x:y) = x
