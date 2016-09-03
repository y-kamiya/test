module Main where

import qualified Data.Map as M
import qualified Data.List.Ordered as OL
import qualified Data.Maybe as MB
import System.Environment

data Pos = Pos (Int, Int) | NonePos deriving (Show, Eq, Ord)
data NodeType = Road | Wall | Start | Goal deriving (Show, Eq)
data Node = Node { pos :: Pos
                 , nodeType :: NodeType
                 } deriving Show
type Field = M.Map Pos Node

data NodeState = Open | Close deriving Show
data NodeInfo = NodeInfo { nodeState :: NodeState
                         , parentPos :: Pos
                         , realCost :: Int
                         , estimateCost :: Int
                         , score :: Int
                         } deriving Show

type FieldState = M.Map Pos NodeInfo

fieldSample = 
  [ "#######"
  , "#S....#"
  , "##.#.##"
  , "####.##"
  , "#G....#"
  , "#######"
  ]

findStartPos :: Field -> Pos
findStartPos field = let ((_, node):_) = M.toList $ M.filter (\node -> nodeType node == Start) field
                     in pos node

findGoalPos :: Field -> Pos
findGoalPos field = let ((_, node):_) = M.toList $ M.filter (\node -> nodeType node == Goal) field
                    in pos node

printField :: [String] -> IO ()
printField = mapM_ print

printMap :: (Show a, Show b) => M.Map a b -> IO ()
printMap aMap = mapM_ print $ M.toList aMap

main :: IO ()
main = do
    (path:_) <- getArgs
    contents <- lines <$> readFile path
    printField contents
    let field = mkField contents
    -- printMap field
    print "-----FieldState -----------------------------------"
    let fieldState = calculateScore field (findStartPos field)
    printMap fieldState 
    print "---- Path -------------------------------------"
    mapM_ print $ findPath field fieldState

findPath :: Field -> FieldState -> [NodeInfo]
findPath field fieldState = buildPath [] $ findGoalPos field
  where
    buildPath :: [NodeInfo] -> Pos -> [NodeInfo]
    buildPath list NonePos = list
    buildPath list currentPos = let nodeInfo = MB.fromJust $ M.lookup currentPos fieldState
                                in  buildPath (nodeInfo:list) (parentPos nodeInfo)

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
        pos = Pos (id `mod` col, id `div` col)
        col = length $ head input

calculateScore :: Field -> Pos -> FieldState
calculateScore field startPos = searchNext [startPos] $ buildInitialState field startPos
  where
    searchNext :: [Pos] -> FieldState -> FieldState
    searchNext [] field = field
    searchNext (currentPos:rest) fieldState = 
      let nextOpens = getNewOpenNodes field fieldState currentPos
          openList = buildOpenList nextOpens rest
          newFieldState = updateFieldState field fieldState currentPos
      in searchNext openList newFieldState

    buildInitialState :: Field -> Pos -> FieldState
    buildInitialState field startPos = let nodeInfo = buildNodeInfo NonePos startPos (findGoalPos field) (-1)
                                       in  M.insert startPos nodeInfo M.empty

buildOpenList :: [Node] -> [Pos] -> [Pos]
buildOpenList [] posList = posList
buildOpenList (node:rest) posList = let list = OL.insertSet (pos node) posList
                                    in  buildOpenList rest list

getExistingNextNodes :: Field -> Pos -> [Node]
getExistingNextNodes field pos = let nextPos = getNextPosList pos
                                     existingPos = filter (`M.member` field) nextPos
                                     existingNodes = map (MB.fromJust . flip M.lookup field) existingPos 
                                 in  filter isRoad existingNodes
  where
    isRoad :: Node -> Bool
    isRoad (Node _ Road) = True
    isRoad (Node _ Goal) = True
    isRoad _ = False

getNewOpenNodes :: Field -> FieldState -> Pos -> [Node]
getNewOpenNodes field fieldState currentPos = let nodes = getExistingNextNodes field currentPos
                                              in  filter (\node -> M.notMember (pos node) fieldState) nodes

getNextPosList :: Pos -> [Pos]
getNextPosList (Pos (x, y)) = [Pos (x,y+1), Pos (x+1,y), Pos (x,y-1), Pos (x-1,y)]

updateFieldState :: Field -> FieldState -> Pos -> FieldState
updateFieldState field fieldState currentPos = M.update toClose currentPos $ mergeFieldState fieldState newFieldState
  where
    nodes = getExistingNextNodes field currentPos
    currentNodeState = MB.fromJust $ M.lookup currentPos fieldState
    goalPos = findGoalPos field
    newFieldState = M.fromList $ map build nodes

    build :: Node -> (Pos, NodeInfo)
    build node = (pos node, buildNodeInfo currentPos (pos node) goalPos (realCost currentNodeState))

    toClose :: NodeInfo -> Maybe NodeInfo
    toClose nodeInfo = Just $ nodeInfo { nodeState = Close }
       

buildNodeInfo :: Pos -> Pos -> Pos -> Int -> NodeInfo
buildNodeInfo parentPos nodePos goalPos currentCost = let real = calcRealCost currentCost
                                                          estimate = calcEstimateCost nodePos goalPos
                                                      in  NodeInfo Open parentPos real estimate (real + estimate)
  where
    calcEstimateCost :: Pos -> Pos -> Int
    calcEstimateCost (Pos (x1, y1)) (Pos (x2, y2)) = abs (x2 - x1) + abs (y2 - y1)

    calcRealCost :: Int -> Int
    calcRealCost = (+ 1)

mergeFieldState :: FieldState -> FieldState -> FieldState
mergeFieldState = M.unionWith combine
  where
    combine :: NodeInfo -> NodeInfo -> NodeInfo
    combine nsOld nsNew
      | score nsOld > score nsNew = nsNew
      | score nsOld <= score nsNew = nsOld
      | otherwise = case realCost nsOld <= realCost nsNew of
                      True -> nsOld
                      False -> nsNew




