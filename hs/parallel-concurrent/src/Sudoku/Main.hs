import Data.List
import Data.Tuple

-- data Cell = [Int] | ((Cell,Cell,Cell),(Cell,Cell,Cell),(Cell,Cell,Cell)) deriving (Eq, Show)

type Problem = [[Int]]
type Candidate = [[[Int]]]
-- type Pos = (Int, Int)
newtype Pos = Pos (Int, Int) deriving (Eq, Show)

toPos :: (Int, Int) -> Pos
toPos (a, b)
  | 0 <= a && a <= 8 && 0 <= b && b <= 8 = Pos (a, b)
  | otherwise = error "invalid"

fromPos :: Pos -> (Int, Int)
fromPos (Pos (a, b)) = (a, b)
               
instance Enum Pos where
  succ (Pos (a, b))
   | b == 8 = Pos (a+1, 0)
   | otherwise = Pos (a, b+1)
  pred (Pos (a, b))
   | b == 0 = Pos (a-1, 8)
   | otherwise = Pos (a, b-1)
  toEnum n = Pos (n `div` 9, n `mod` 9)
  fromEnum (Pos (a, b)) = a * 9 + b

instance Bounded Pos where
  minBound = Pos (0,0)
  maxBound = Pos (8,8)
  

-- difficult
problem :: Problem
problem = [[3,0,0,0,0,2,0,0,0]
          ,[0,4,0,8,0,5,0,3,0]
          ,[2,9,0,0,0,0,0,0,8]
          ,[4,0,0,1,7,0,0,0,5]
          ,[0,0,6,0,5,8,3,0,0]
          ,[0,0,0,2,4,6,0,0,0]
          ,[0,0,0,5,0,0,6,0,0]
          ,[0,8,0,6,0,4,0,5,0]
          ,[0,0,2,0,0,0,9,8,0]
          ]

-- easy
-- problem :: Problem
-- problem = [[0,9,0,0,0,3,0,2,0]
--          , [7,0,2,6,0,0,5,4,0]
--          , [0,0,0,0,0,8,0,0,7]
--          , [1,4,0,8,0,0,0,0,3]
--          , [0,5,9,7,3,0,0,0,1]
--          , [8,6,0,1,0,9,7,5,2]
--          , [9,2,1,3,0,4,6,0,5]
--          , [0,8,0,9,0,7,2,1,4]
--          , [4,0,6,0,0,5,8,3,0]
--          ]
         
lookupP :: Problem -> Pos -> Int
lookupP pro (Pos (x,y)) = (pro !! x) !! y

chunk :: [a] -> [[a]]
chunk [] = [[]]
chunk xs = h : chunk t
  where (h,t) = splitAt 9 xs

p2c :: Problem -> Candidate
p2c problem = filter (not . null) $ chunk $ map (candidateInPos problem) ([minBound..maxBound]::[Pos])


c2p :: Candidate -> Problem
c2p = map (map convert)
  where
    convert :: [Int] -> Int
    convert ns
      | length ns == 1 = head ns
      | otherwise = 0

decide :: Candidate -> Candidate
decide = id


candidateInPos :: Problem -> Pos -> [Int]
candidateInPos problem pos
  | e == 0 = rowdiff `intersect` coldiff `intersect` celldiff 
  | otherwise = [e]
  where 
    e = lookupP problem pos
    rowdiff = [1..9] \\ findRow problem pos 
    coldiff = [1..9] \\ findCol problem pos
    celldiff = [1..9] \\ findCell problem pos


findRow, findCol, findCell :: Problem -> Pos -> [Int]
findRow p (Pos (x,_)) = (!!x) p
findCol p (Pos (_,y)) = map (!!y) p
findCell p pos = concatMap (splice3 y) . splice3 x $ p
  where
    Pos (x, y) = cell2Pos . pos2Cell $ pos
    splice3 :: Int -> [a] -> [a]
    splice3 n = drop n . take (n+3)

pos2Cell :: Pos -> Int
pos2Cell (Pos (x,y)) = (x `div` 3) * 3 + (y `div` 3)
  
cell2Pos :: Int -> Pos
cell2Pos n = toPos ((*) 3 $ div n 3, (*) 3 $ mod n 3)


main :: IO ()
main = do
  print $ loop problem [[]]
  where
    loop problem prev 
      | problem == prev = problem
      | otherwise = let c = p2c problem
                        c' = decide c
                        p = c2p c'
                    in loop p problem
