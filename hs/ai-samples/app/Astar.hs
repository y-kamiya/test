module Main where

import qualified Data.Map as M
import qualified Data.List.Ordered as OL
import Data.Maybe

data Pos = Pos (Int, Int) | NonePos deriving (Show, Eq, Ord)
data NodeType = Road | Wall | Start | Goal deriving Show
data Node = Node { pos :: Pos
                 , nodeType :: NodeType
                 } deriving Show
type Field = M.Map Pos Node

data NodeState = Open | Close deriving Show
data NodeInfo = NodeInfo { nodeState :: NodeState
                         , realCost :: Int
                         , estimateCost :: Int
                         , score :: Int
                         , pos ::  Pos
                         } deriving Show
data FieldState = M.Map Pos NodeInfo

fieldSample = 
  [ "#######"
  , "#S....#"
  , "##.#.##"
  , "####.##"
  , "#G....#"
  , "#######"
  ]

findStartPos :: Field -> Pos
findStartPos field = case M.filter (== Node _ Start) field of
                       M.singleton pos _ -> pos
                       otherwise -> NonePos

findGoalPos :: Field -> Pos
findGoalPos field = case M.filter (== Node _ Goal) field of
                       M.singleton pos _ -> pos
                       otherwise -> NonePos

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
      | c == 'S'  = convert ts $ M.insert pos (Node pos Start) field
      | c == 'G'  = convert ts $ M.insert pos (Node pos Goal) field
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
          openList = buildOpenList nextOpens rest
          newFieldState = updateFieldState field fieldState current
      in searchNext openList newFieldState

buildOpenList :: [Node] -> [Pos] -> [Pos]
buildOpenList [] posList = posList
buildOpenList (node:rest) posList = let list = OL.insertSet (pos node) posList
                                    in  buildOpenList rest list

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

updateFieldState :: Field -> FieldState -> Pos -> FieldState
updateFieldState field fieldState current = let nodes = getExistingNextNodes field current
                                                currentNodeState = Maybe.fromJust $ M.lookup current fieldState
                                                goalPos = findGoalPos field
                                                newNodes = M.fromList $ map (\node -> ((pos node), buildNodeInfo (pos node) goalPos (realCost currentNodeState))) nodes
                                            in  mergeFieldState fieldState newFieldState

buildNodeInfo :: Pos -> Pos -> Int -> NodeInfo
buildNodeInfo nodePos goalPos currentCost = let real = calcRealCost currentCost
                                                estimate = calcEstimateCost nodePos goalPos
                                            in  NodeInfo Open real estimate (real + estimate) nodePos
  where
    calcEstimateCost :: Pos -> Pos -> Int
    calcEstimateCost (Pos (x1, y1)) (Pos (x2, y2)) = abs (x2 - x1) + abs (y2 - y1)

    calcRealCost :: Int -> Int
    calcRealCost = (+ 1)

mergeFieldState :: FieldState -> FieldState -> FieldState
mergeFieldState fsOld fsNew = M.unionWith combine fsOld fsNew
  where
    combine :: NodeState -> NodeState -> NodeState
    combine nsOld nsNew
      | score nsOld > score nsNew = nsNew
      | score nsOld <= score nsNew = nsOld
      | otherwise = case realCost nsOld <= realCost nsNew of
                      True -> nsOld
                      False -> nsNew




