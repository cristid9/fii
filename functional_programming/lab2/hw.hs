import Data.List

-- problem 1
pune_la_sfarsit [] el = el:[]
pune_la_sfarsit (x:l) el = x:(pune_la_sfarsit l el)

-- problem 2
contine [] a = False
contine (x:l) a | x == a = True
                | x /= a = (contine l a)

-- problem 3
concatenare (x:l) [] = x:l
concatenare (x:l) (x2:l2) = x:(concatenare l l2):x2


-- problem 4
inversare [] = [] 
inversare (x:l) = pune_la_sfarsit (inversare l) x

--problem 5
pos (x:l) index | index > 0 = (pos l (index - 1)) 
                | index == 0 = x

-- problem 6


