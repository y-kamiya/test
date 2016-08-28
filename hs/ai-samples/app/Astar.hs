module Main where

import qualified Data.Map as M

data Pos = Pos (Int, Int) deriving (Show, Eq, Ord)
data NodeType = Road | Wall deriving Show
data Node = Node Pos NodeType deriving Show
type Field = M.Map Pos Node

fieldSample = 
  [ "#######"
  , "#.....#"
  , "##.#.##"
  , "####.##"
  , "#.....#"
  , "#######"
  ]

startPos = Pos (1, 1)
goalPos = Pos (1, 5)


printField :: IO ()
printField = mapM_ print fieldSample

main :: IO ()
main = print $ M.lookup (Pos (1,1)) $ mkField fieldSample

mkField :: [String] -> Field
mkField input = convert (zip [0..] $ concat input) M.empty
  where
    convert :: [(Int, Char)] -> Field -> Field
    convert [] field = field
    convert ((id, c):ts) field 
      | c == '.'  = convert ts $ M.insert pos (Node pos Road) field
      | otherwise = convert ts $ M.insert pos (Node pos Wall) field
      where
        pos = Pos (id `div` m, id `mod` n)
        n = length $ head input
        m = length input

searchPath :: Field -> Pos -> Pos -> [Pos]
searchPath field startPos goalPos = searchNext [startPos] []
  where
    searchNext :: [Pos] -> [Pos] -> [Pos]
    searchNext openList closeList = 










