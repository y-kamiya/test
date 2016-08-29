module Main where

import qualified Data.Map as M

data Pos = Pos (Int, Int) deriving (Show, Eq, Ord)
data NodeType = Road | Wall deriving Show
data Node = Node Pos NodeType deriving Show
type Field = M.Map Pos Node

data NodeState = NodeState Int Int Int
data FieldState = M.Map Pos FieldState

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
searchPath field startPos goalPos = searchNext [startPos] [] [] M.empty
  where
    searchNext :: [Pos] -> [Pos] -> [Pos] -> FieldState -> [Pos]
    searchNext [] _ path _ -> path
    searchNext (pos:rest) closeList path fieldState = 
    // this logic cant introduce correct path
      let nextOpens = getNextOpens pos
          closed = pos:closeList
          newPath = head nextOpens : path
          newFieldState = updateFieldState nextOpens
      in searchNext (rest ++ nextOpens) closed newPath newFieldState










