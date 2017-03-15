data Zi = Luni | Marti | Miercuri | Joi deriving Show


instance Eq Zi where
--   (==) Luni Luni = True
--   (==) Luni _ = False
   (/=) Luni Luni = False
   (/=) Luni _ = True

dublu x = x + x
triplu x = x + x + x
laPatrat x = x ** 2

dublu' (x, y) = (dublu x, dublu y)
triplu' (x, y) = (triplu x, triplu y)
laPatrat' (x, y) = (laPatrat x, laPatrat y)

aplicaTuplu f (x, y) = (f x, f y)

twice f v = (f v) + (f v)

par = even
impar = odd

map' f [] = []
map' f (x:xs) = [f x] ++ (map f xs)

filter' f [] = []
filter f (x:xs) | (f x) == True = [x] ++ (filter' f xs)
                | otherwise  =  (filter' f  xs)

foldl' f el [] = el
foldl' f el (x:xs) =  (foldl' f (f el x)  xs)

-- gresit
foldl'' f el [] = el
foldl'' f el (x:xs) = f(x)(foldl'' f el xs)

f True = dublu
f False = laPatrat

suma x y = x + y
f1 = map dublu

comp f1 f2 x = f1 (f2 x)

(\x -> x + x) 2 

