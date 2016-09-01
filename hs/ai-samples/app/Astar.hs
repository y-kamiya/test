module Main where

import qualified Data.Map as M
import qualified Data.List.Ordered as OL
import Data.Maybe

data Pos = Pos (Int, Int) | NonePos deriving (Show, Eq, Ord)
data NodeType = Road | Wall deriving Show
data Node = Node { pos :: Pos
                 , nodeType :: NodeType
                 } deriving Show
type Field = M.Map Pos Node

data NodeState = Open | Close
data NodeInfo = NodeInfo { nodeState :: NodeState
                         , realCost :: Int
                         , estimateCost :: Int
                         , score :: Int
                         , pos ::  Pos
                         }
data FieldState = M.Map Pos NodeInfo

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

searchPath :: Field -> Pos -> Pos -> FieldState
searchPath field startPos goalPos = searchNext [startPos] $ M.insert startPos (NodeInfo Open 0 0 0 NonePos) M.empty
  where
    searchNext :: [Pos] -> FieldState -> FieldState
    searchNext [] field -> field
    searchNext (current:rest) fieldState = 
      let nextOpens = getNewOpenNodes field fieldState current
          newFieldState = updateFieldState field fieldState current
      in searchNext (rest ++ nextOpens) newFieldState

getExistingNextNodes :: Field -> FieldState -> Pos -> [Node]
getExistingNextNodes field fieldState pos = let nextPos = getNextPosList pos
                                                existingPos = filter (\pos -> M.member pos field) nextPos
                                                existingNodes = map (Maybe.fromJust . flip M.lookup field) existingPos 
                                            in  filter (\node -> nodeType node == Road) existingNodes

getNewOpenNodes :: Field -> FieldState -> Pos -> [Node]
getNewOpenNodes field fieldState current = let nodes = getExistingNextNodes field current
                                       in  filter (\node -> M.notMember (pos node) fieldState) nodes

getNextPosList :: Pos -> [Pos]
getNextPosList (Pos (x, y)) = [Pos (x,y+1), Pos (x+1,y), Pos (x,y-1), Pos (x-1,y)]

updateFieldState :: Field -> FieldState -> Pos -> [Node]
updateFieldState field fieldState current = let nodes = getExistingNextNodes field current






