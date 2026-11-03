{-
[x^2 |x <- [1..10], x `rem` 3 == 2]
[(x,y) | x <- [1..5], y <- [x..(x+2)]]
[(x,y) | x <- [1..3], let k = x^2, y <- [1..k]]
[x | x <- "Facultatea de Matematica si Informatica", elem x ['A'..'Z']]
[[x..y] | x <- [1..5], y <- [1..5], x < y]
-}

-- 2.
factori :: Int -> [Int]
factori n = [d | d <- [1..n], n `rem` d == 0]

-- 3.
prim :: Int -> Bool
prim n = if length(factori n) == 2
            then True
        else False

-- 4.
numerePrime :: Int -> [Int]
numerePrime n = [x | x <- [2..n], prim x]

-- 5.
myzip3 :: [a] -> [b] -> [c] -> [(a,b,c)]
myzip3 l1 l2 l3 = [(x, y, z) | ((x, y), z) <- zip (zip l1 l2) l3]

-- extra idk?? 
ordonataNat :: [Int] -> Bool
ordonataNat [] = True
ordonataNat [x] = True
ordonataNat (x:xs) = undefined
ordonata :: [a] -> (a -> a -> Bool) -> Bool
ordonata = undefined

-- 6.
firstEl :: [(a, b)] -> [a]
firstEl l = map (\(x, _) -> x) l

-- 7.
sumList :: [[Int]] -> [Int]
sumList l = map (\lista -> sum lista) l

-- 8.
prel2 :: [Int] -> [Int]
prel2 l = map (\x -> if even x then x `div` 2 else x * 2) l

-- 9.
arechar :: Char -> [String] -> [String]
arechar c l = filter (elem c) l

-- 10.
impsq :: [Int] -> [Int]
impsq l = map (\x -> x * x) (filter odd l)

-- 11.
pozimpsq :: [Int] -> [Int]
pozimpsq l = map (\(idx, x) -> x * x) (filter (\(idx, x) -> odd idx) (zip [0..] l))

-- 12.
numaiVocale :: [[Char]] -> [[Char]]
numaiVocale l = map (\cuv -> filter (\c -> elem c "aeiouAEIOU") cuv) l

-- 13.
mymap :: (a -> b) -> [a] -> [b]
mymap _ [] = []
mymap f (h:t) = f h : mymap f t

myfilter :: (a -> Bool) -> [a] -> [a]
myfilter _ [] = []
myfilter f (h:t) = if f h 
                    then f h : myfilter f t
                else 
                    myfilter f t

-- bonus
step :: Char -> [Char] -> [[Char]]
step p c = [newc | zip [0..] map (\c -> filter (\cell -> elem cell "_") c) l]

