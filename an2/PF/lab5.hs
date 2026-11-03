-- ex 1
sumsqimp :: [Int] -> Int
sumsqimp l = foldr (+) 0 (map (\x -> x*x) (filter odd l))


-- ex 2
alltrue :: [Bool] -> Bool
alltrue l = foldr (&&) True l

-- ex 3
verify :: (Int -> Bool) -> [Int] -> Bool
verify cond l = foldr (&&) True (map cond l)
 
-- ex 4
anyverify :: (Int -> Bool) -> [Int] -> Bool
anyverify cond l = foldr (||) False (map cond l)


-- ex 5
mapfoldr :: (a -> b) -> [a] -> [b]
mapfoldr cond l = foldr (\x tail -> cond x : tail) [] l

filterfoldr :: (a -> Bool) -> [a] -> [a]
filterfoldr cond l = foldr (\x tail -> if cond x then x : tail else tail) [] l

-- ex 6
listToInt :: [Integer]-> Integer
listToInt l = foldl (\nr cif -> nr*10 + cif) 0 l

-- ex 7
rmChar :: Char -> String -> String
rmChar ch s = filter (\x -> (x /= ch)) s

rmCharsRec :: String -> String -> String
rmCharsRec [] s = s
rmCharsRec (h:t) s = rmCharsRec t (rmChar h s)

rmCharsFold :: String -> String -> String
rmCharsFold l s = foldr rmChar s l


-- ex 8
myReverse :: [a] -> [a] 
myReverse l = foldl (\tail x -> x : tail) [] l

-- ex 9
myElem :: Int -> [Int] -> Bool
myElem x l = foldr (\y tail -> y == x || tail) False l

-- ex 10    
myUnzip :: [(a, b)] -> ([a], [b])
myUnzip l = foldr (\(x, y) (xs, ys) -> (x : xs, y : ys)) ([], []) l


-- ex 11
union :: [Int] -> [Int] -> [Int]
union l1 l2 = foldr (\x un -> if elem x un then un else x : un) [] (l1 ++ l2)



-- ex 12
intersect :: [Int] -> [Int] -> [Int]
intersect l1 l2 = foldr (\x ins -> if not (elem x ins) && elem x l1 && elem x l2 then x : ins else ins) [] (l1 ++ l2)

-- ex 13
permutations :: [Int] -> [[Int]]
permutations l = foldr (\_ permutari -> [x : ll | ll <- permutari, x <- l, not (elem x ll)]) [[]] l

-- ex 14
prim :: [[Int]] -> [[Int]]
prim [[]] = []