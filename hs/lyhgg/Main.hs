module Main where

import Control.Monad

type Pos = (Int, Int)
type Route = [Pos]

main :: IO ()
main = do
  print $ moveKnight (6,2)
  print $ findRoute (6,2) (6,1) 3
  print $ inMany (6,2) 2

moveKnight :: Pos -> [Pos]
moveKnight (c, r) = do
  (c', r') <- [(c+2,r+1), (c+2,r-1), (c-2,r+1), (c-2,r-1), (c+1,r+2), (c+1,r-2), (c-1,r+2), (c-1,r-2)]
  guard (c' `elem` [1..8] && r' `elem` [1..8])
  return (c', r')

in3 :: Pos -> [Pos]
in3 start = return start >>= moveKnight >>= moveKnight >>= moveKnight

canReachIn3 :: Pos -> Pos -> Bool
canReachIn3 start end = end `elem` in3 start

findRoute :: Pos -> Pos -> Int -> [Route]
findRoute from to moveCount = findRoute' [from] moveCount
  where
    findRoute' :: Route -> Int -> [Route]
    findRoute' route n 
      | n <= 0 = [reverse route | head route == to]
      | otherwise = do
          r <- map (:route) $ moveKnight $ head route
          findRoute' r (n-1)
          
inMany :: Pos -> Int -> [Pos]
inMany start x = return start >>= foldr (<=<) return (replicate x moveKnight)
