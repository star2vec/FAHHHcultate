data Expr = Const Int -- integer constant
          | Expr :+: Expr -- addition
          | Expr :*: Expr -- multiplication
           deriving Eq

data Operation = Add | Mult deriving (Eq, Show)

data Tree = Lf Int -- leaf
          | Node Operation Tree Tree -- branch
           deriving (Eq, Show)

-- 1.1

instance Show Expr where
  show (Const x) = show x
  show (e1 :+: e2) = "(" ++ show e1 ++ " + " ++ show e2 ++ ")"
  show (e1 :*: e2) = "(" ++ show e1 ++ " * " ++ show e2 ++ ")"

-- 1.2
evalExp :: Expr -> Int
evalExp (Const x) = x
evalExp (e1 :+: e2) = evalExp e1 + evalExp e2
evalExp (e1 :*: e2) = evalExp e1 * evalExp e2

exp1 = ((Const 2 :*: Const 3) :+: (Const 0 :*: Const 5))
exp2 = (Const 2 :*: (Const 3 :+: Const 4))
exp3 = (Const 4 :+: (Const 3 :*: Const 3))
exp4 = (((Const 1 :*: Const 2) :*: (Const 3 :+: Const 1)) :*: Const 2)
test11 = evalExp exp1 == 6
test12 = evalExp exp2 == 14
test13 = evalExp exp3 == 13
test14 = evalExp exp4 == 16

-- 1.3
evalArb :: Tree -> Int
evalArb (Lf x) = x
evalArb (Node Add l r) = evalArb l + evalArb r
evalArb (Node Mult l r) = evalArb l * evalArb r

arb1 = Node Add (Node Mult (Lf 2) (Lf 3)) (Node Mult (Lf 0)(Lf 5))
arb2 = Node Mult (Lf 2) (Node Add (Lf 3)(Lf 4))
arb3 = Node Add (Lf 4) (Node Mult (Lf 3)(Lf 3))
arb4 = Node Mult (Node Mult (Node Mult (Lf 1) (Lf 2)) (Node Add (Lf 3)(Lf 1))) (Lf 2)

test21 = evalArb arb1 == 6
test22 = evalArb arb2 == 14
test23 = evalArb arb3 == 13
test24 = evalArb arb4 == 16


-- 1.4
expToArb :: Expr -> Tree
expToArb (Const x) = Lf x
expToArb (e1 :+: e2) = Node Add (expToArb e1) (expToArb e2)
expToArb (e1 :*: e2) = Node Mult (expToArb e1) (expToArb e2)


---- 2.

data Punct = Pt [Int]

data Arb = Vid | F Int | N Arb Arb
          deriving Show

class ToFromArb a where
      toArb :: a -> Arb
      fromArb :: Arb -> a
-- Pt [1,2,3]
-- (1, 2, 3)

-- Pt []
-- ()

-- 2.1
dimn :: [Int] -> String
dimn [] = ""
dimn [x] = show x
dimn (h:t) = show h ++ ", " ++ dimn t

instance Show Punct where
  show (Pt l) = "(" ++ dimn l ++ ")"

-- 2.2
frontier :: Arb -> [Int]
frontier Vid = []
frontier (F x) = [x]
frontier (N l r) = frontier l ++ frontier r

instance ToFromArb Punct where
  toArb (Pt []) = Vid
  toArb (Pt (h:t)) = N (F h) (toArb (Pt t))
  fromArb a = Pt (frontier a)


-- toArb (Pt [1,2,3])
-- N (F 1) (N (F 2) (N (F 3) Vid))
-- fromArb $ N (F 1) (N (F 2) (N (F 3) Vid)) :: Punct
--  (1,2,3)

---- 3.

data Geo a = Square a | Rectangle a a | Circle a
    deriving Show

class GeoOps g where
  perimeter :: (Floating a) => g a -> a
  area :: (Floating a) =>  g a -> a

-- 3.1
instance GeoOps Geo where
  perimeter (Square l) = 4*l
  perimeter (Rectangle l w) = 2 * (l+w)
  perimeter (Circle r) = 2*pi*r
  area (Square l) = l*l
  area (Rectangle l w) = l*w
  area (Circle r) = pi*r*r

-- 3.2
instance (Floating a, Eq a) => Eq (Geo a) where
  g1 == g2 = perimeter g1 == perimeter g2

-- ghci> pi
-- 3.141592653589793

