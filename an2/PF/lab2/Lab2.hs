import Data.List

myInt = 31415926535897932384626433832795028841971693993751058209749445923

double :: Integer -> Integer
double x = x+x

--maxim :: Integer -> Integer -> Integer
maxim x y = if (x > y)
               then x
          else y

max3 x y z = let
             u = maxim x y
             in (maxim  u z)

fibonacciCazuri :: Integer -> Integer
fibonacciCazuri n
    | n < 2     = n
    | otherwise = fibonacciCazuri (n - 1) + fibonacciCazuri (n - 2)
    
fibonacciEcuational :: Integer -> Integer
fibonacciEcuational 0 = 0
fibonacciEcuational 1 = 1
fibonacciEcuational n =
    fibonacciEcuational (n - 1) + fibonacciEcuational (n - 2)
    

----- ex 6:
-- a
sumsq x y = x^2 + y^2

-- b
paritate x = if (x `mod` 2 == 0) 
                then "par"
                else "impar"

-- c
factorial :: Integer -> Integer
factorial 0 = 1
factorial n = n * factorial (n - 1)

-- d
verif :: Integer -> Integer -> Bool
verif x y = if (x > 2*y) 
                then True
                else False

-- e
maximlist :: [Integer] -> Integer
maximlist [] = 0
maximlist [x] = x
maximlist (x:xs) = maxim x (maximlist xs)


----- ex 7:
poly :: Double -> Double -> Double -> Double -> Double
poly a b c x = a*x^2 + b*x + c

----- ex 8:
-- var 1
fizzbuzz :: Integer -> String
fizzbuzz x = if (x `mod` 3 == 0 && x `mod` 5 == 0) 
              then "FizzBuzz"
              else if (x `mod` 3 == 0)
                    then "Fizz" 
               else if (x `mod` 5 == 0)
                    then "Buzz" 
                else ""

-- var 2
fizzbuzz2 :: Integer -> String
fizzbuzz2 x
    | x `mod` 3 == 0 && x `mod` 5 == 0 = "FizzBuzz"
    | x `mod` 3 == 0 = "Fizz"
    | x `mod` 5 == 0 = "Buzz"
    | otherwise = ""


----- ex 9:
-- var 1
tribonacci :: Integer -> Integer
tribonacci 1 = 1
tribonacci 2 = 1
tribonacci 3 = 2
tribonacci n = tribonacci (n-1) + tribonacci (n-2) + tribonacci (n-3)

-- var 2
tribonacci2 :: Integer -> Integer
tribonacci2 n
    | n == 1 = 1
    | n == 2 = 1
    | n == 3 = 2
    | otherwise = tribonacci2 (n-1) + tribonacci2 (n-2) + tribonacci2 (n-3)

----- ex 10:
binomial :: Integer -> Integer -> Integer
binomial n 0 = 1
binomial 0 k = 0
binomial n k = binomial (n-1) k + binomial (n-1) (k-1)


----- ex 11:
-- a
sumn :: Integer -> Integer
sumn 0 = 0
sumn n = n + sumn (n-1)

-- b 
putere :: Integer -> Integer -> Integer
putere x 0 = 1
putere x y = x * putere x (y-1)

-- c
inmultirerepetata :: Integer -> Integer -> Integer
inmultirerepetata x 0 = 0
inmultirerepetata x y = x + inmultirerepetata x (y - 1)

-- d 
sumacif :: Integer -> Integer
sumacif x = if (x < 10) 
                then x
                else (x `mod` 10) + sumacif (x `div` 10)

        
----- bonus:
-- a
nrcif :: Integer -> Integer
nrcif x = if (x < 10)
                then 1
                else 1 + nrcif (x `div` 10)

-- b
prodcifpar :: Integer -> Integer
prodcifpar x = if (x < 10)
                    then if (x `mod` 2 == 0)
                        then x
                        else 1
                else if (x `mod` 2 == 0)
                    then (x `mod` 10)    * prodcifpar (x `div` 10)
                    else prodcifpar (x `div` 10)

-- c
oglindire :: Integer -> Integer
oglindire x = if (x < 10)
                then x
            else 10 * (x `mod` 10) + oglindire (x `div` 10)

-- d
prim :: Integer -> Bool
prim x = if (nrdiv x == 2)
            then True
            else False
where nrdiv x d
    if  d < n:
        if (x `mod` d == 0)
            then 1 + nrdiv x (d + 1)
        else nrdiv x (d + 1)
    else 0 

-- e
nrapcif :: Integer -> Integer -> Integer
nrapcif x c = if (x < 10)
                if (x == c)
                    then 1
                    else 0
            else if (x `mod` 10 == c)
                    then 1 + nrapcif (x `div` 10) c
                    else nrapcif (x `div` 10) c

-- f 
stergecif :: Integer -> Integer -> Integer
stergecif x c = if (x < 10)
                    if (x == c)
                        then 0
                        else x
                else if (x `mod` 10 == c)
                        then stergecif (x `div` 10) c
                        else (x `mod` 10) + 10 * stergecif (x `div` 10) c


-- g 
ackerman :: Integer -> Integer -> Integer
ackerman m n = if (m == 0)
                then n + 1
            else if (m > 0 && n == 0)
                then ackerman (m - 1) 1
            else ackerman (m - 1) (ackerman m (n - 1))

