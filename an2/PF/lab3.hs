import Data.Char

--- ex 1
-- a
verifL :: [Int] -> Bool
verifL l =  length(l) `mod` 2 == 0

-- b
takefinal :: [Int] -> Int -> [Int]
takefinal l n = if length(l) >= n then drop (length l - n) l 
                else l

-- c
remove :: [Int] -> Int -> [Int]
remove l n = if length(l) < n then l
             else take n l ++ drop (n + 1) l


--- ex 2
-- semiPareRec [0,2,1,7,8,56,17,18] == [0,1,4,28,9]
semiPareRec :: [Int] -> [Int]
semiPareRec [] = []
semiPareRec (h:t)
 | even h    = h `div` 2 : t'
 | otherwise = t'
 where t' = semiPareRec t

-- a
myreplicate :: Int -> a -> [a]
myreplicate n v = if n<=0 
                    then []
                  else
                    v : myreplicate (n-1) v

-- b
sumimp :: [Int] -> Int
sumimp l = if length(l)==0
                then 0
            else if head(l) `mod` 2 == 1
                then head(l) + sumimp (tail(l))
            else 
                sumimp (tail(l))

-- c
totalLen :: [String] -> Int
totalLen [] = 0
totalLen l = if take 1 (head l) == "A"
                then length(head(l)) + totalLen(tail(l))
            else totalLen(tail(l))


--- ex 3

nrvocaux :: String -> Int
nrvocaux [] = 0
nrvocaux cuv = if (head(cuv) `elem` "aeiou")
                    then 1 + nrvocaux(tail(cuv))
                else nrvocaux(tail(cuv))

nrVocale :: [String] -> Int
nrVocale [] = 0
nrVocale l = if reverse(head(l)) /= head(l)
                then nrVocale (tail l)
            else 
                nrvocaux(head(l)) + nrVocale (tail(l))


--- ex 4
f :: Int -> [Int] -> [Int]
f _ [] = []
f x (h:t) = if h `mod` 2 == 1
            then h : f x t
        else 
            h : x : f x t


-------

semiPareComp :: [Int] -> [Int]
semiPareComp l = [ x `div` 2 | x <- l, even x ]

--- ex 5
divizori :: Int -> [Int]
divizori n = [d | d <- [1..n], n `mod` d == 0]

--- ex 6
listadiv :: [Int] -> [[Int]]
listadiv l = [divizori e | e <- l]

--- ex 7
inIntervalComp :: Int -> Int -> [Int] -> [Int]
inIntervalComp a b l = [e | e <- l, a <= e && e <= b]

inIntervalRec :: Int -> Int -> [Int] -> [Int]
inIntervalRec _ _ [] = []
inIntervalRec a b (h:t) = if (a <= h && h <= b)
                            then h : inIntervalRec a b t
                          else inIntervalRec a b t

--- ex 8
pozitiveRec :: [Int] -> Int
pozitiveRec [] = 0
pozitiveRec (h:t) = if h > 0
                    then 1 + pozitiveRec t
                  else 
                    pozitiveRec t

pozitiveComp :: [Int] -> Int
pozitiveComp l = length [e | e <- l, e > 0]


--- ex 9
auxpozrec :: [Int] -> Int -> [Int]
auxpozrec [] _ = []
auxpozrec (h:t) idx = if h `mod` 2 == 1
                            then idx : auxpozrec t (idx+1) 
                       else auxpozrec t (idx+1)
pozitiiImpareRec :: [Int] -> [Int]
pozitiiImpareRec l = auxpozrec l 0

pozitiiImpareComp :: [Int] -> [Int]
pozitiiImpareComp l = [idx | (e, idx) <- zip l [0..], odd e]


--- ex 10
multDigitsRec :: String -> Int
multDigitsRec[] = 1
multDigitsRec (h:t) = if isDigit h 
                         then digitToInt h * multDigitsRec t
                      else multDigitsRec t

multDigitsComp :: String -> Int
multDigitsComp s = product [digitToInt c | c <- s, isDigit c]


