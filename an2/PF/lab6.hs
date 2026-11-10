data Fruct
  = Mar String Bool
  | Portocala String Int

ionatanFaraVierme = Mar "Ionatan" False
goldenCuVierme = Mar "Golden Delicious" True
portocalaSicilia10 = Portocala "Sanguinello" 10
listaFructe = [Mar "Ionatan" False,
                Portocala "Sanguinello" 10,
                Portocala "Valencia" 22,
                Mar "Golden Delicious" True,
                Portocala "Sanguinello" 15,
                Portocala "Moro" 12,
                Portocala "Tarocco" 3,
                Portocala "Moro" 12,
                Portocala "Valencia" 2,
                Mar "Golden Delicious" False,
                Mar "Golden" False,
                Mar "Golden" True]

--- 1. 
-- a
ePortocalaDeSicilia :: Fruct -> Bool
ePortocalaDeSicilia (Portocala soi _) = elem soi ["Tarocco", "Moro", "Sanguinello"]
ePortocalaDeSicilia (Mar _ _) = False

test_ePortocalaDeSicilia1 = ePortocalaDeSicilia (Portocala "Moro" 12) == True
test_ePortocalaDeSicilia2 = ePortocalaDeSicilia (Mar "Ionatan" True) == False

-- b
nrfeliiportocala :: Fruct -> Int
nrfeliiportocala (Mar _ _) = 0
nrfeliiportocala (Portocala _ n) = n

nrFeliiSicilia :: [Fruct] -> Int
nrFeliiSicilia l = sum (map nrfeliiportocala (filter ePortocalaDeSicilia l))

test_nrFeliiSicilia = nrFeliiSicilia listaFructe == 52

-- c
areviermi :: Fruct -> Bool
areviermi (Portocala _ _) = False
areviermi (Mar _ v) = v

nrMereViermi :: [Fruct] -> Int
nrMereViermi l = length (filter areviermi l)

test_nrMereViermi = nrMereViermi listaFructe == 2


--- 2. 
type NumeA = String
type Rasa = String
data Animal = Pisica NumeA | Caine NumeA Rasa
    deriving Show

-- b
vorbeste :: Animal -> String
vorbeste  (Pisica _) = "meow :3"
vorbeste (Caine _ _) = "woof!!"

-- c
rasa :: Animal -> Maybe String
rasa (Pisica _) = Nothing
rasa (Caine _ r) = Just r


--- 3.
data Linie = L [Int]
   deriving Show
data Matrice = M [Linie]
   deriving Show

-- a
sumlin :: Linie -> Int
sumlin (L l) = sum l

verifica :: Matrice -> Int -> Bool
verifica (M linii) n = foldr (&&) True (map (\linie -> sumlin linie == n) linii)

test_verif1 = verifica (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 10 == False
test_verif2 = verifica (M[L[2,20,3], L[4,21], L[2,3,6,8,6], L[8,5,3,9]]) 25 == True

-- b
positive :: Linie -> Bool
positive (L l) = foldr (&&) True (map (\x -> x > 0) l)

doarPozN :: Matrice -> Int -> Bool
doarPozN (M linii) n = foldr (&&) True (map positive (filter (\(L l) -> length l == n) linii))

testPoz1 = doarPozN (M [L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3 == True

testPoz2 = doarPozN (M [L[1,2,-3], L[4,5], L[2,3,6,8], L[8,5,3]]) 3 == False

-- c
corect :: Matrice -> Bool
corect (M []) = True
corect (M (L h : t)) = foldr (&&) True (map (\(L l) -> length l == length h) t)

testcorect1 = corect (M[L[1,2,3], L[4,5], L[2,3,6,8], L[8,5,3]]) == False
testcorect2 = corect (M[L[1,2,3], L[4,5,8], L[3,6,8], L[8,5,3]]) == True

--- 4.

-- a
data Dir = N | NE | E | SE | S | SV | V | NV
  deriving Show

data Turtle = T Int Int Dir
  deriving Show

-- b
data Action = Step | Turn | Seq Command Command
  deriving Show

-- c
data Command = Do Action | Repeat Int Action | Wait
  deriving Show

-- d 
turn45 :: Dir -> Dir
turn45 N  = NE
turn45 NE = E
turn45 E  = SE
turn45 SE = S
turn45 S  = SV
turn45 SV = V
turn45 V  = NV
turn45 NV = N

movecell :: Dir -> (Int, Int)
movecell N  = (0, 1)
movecell NE = (1, 1)
movecell E  = (1, 0)
movecell SE = (1, -1)
movecell S  = (0, -1)
movecell SV = (-1, -1)
movecell V  = (-1, 0)
movecell NV = (-1, 1)

stepTurtle :: Turtle -> (Int, Int) -> Turtle
stepTurtle (T x y d) (dx, dy) = T (x + dx) (y + dy) d

doAction :: Turtle -> Action -> Turtle
doAction (T x y d) Turn = T x y (turn45 d)
doAction (T x y d) Step = stepTurtle (T x y d) (movecell d)
doAction t (Seq c1 c2) = doCommand (doCommand t c1) c2

doCommand :: Turtle -> Command -> Turtle
doCommand t (Do a) = doAction t a
doCommand t Wait = t
doCommand t (Repeat n a) = if n <= 0
                             then t
                           else doCommand (doAction t a) (Repeat (n - 1) a)

pozitie :: Turtle -> (Int, Int)
pozitie (T x y _) = (x, y)

getPizza :: Turtle -> [Command] -> (Int, Int)
getPizza t cmds = pozitie (foldl doCommand t cmds)

-- f
combina :: [Command] -> Command
combina cmds = foldr (\c acc -> Do (Seq c acc)) Wait cmds