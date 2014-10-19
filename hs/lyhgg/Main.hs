import Control.Monad

type Pos = (Int, Int)
type Route = [Pos]

main :: IO ()
main = do
  print $ moveKnight (6,2)
  print $ findRoute (6,2) (6,1) 3

moveKnight :: Pos -> [Pos]
moveKnight (c, r) = do
  (c', r') <- [(c+2,r+1), (c+2,r-1), (c-2,r+1), (c-2,r-1), (c+1,r+2), (c+1,r-2), (c-1,r+2), (c-1,r-2)]
  guard (c' `elem` [1..8] && r' `elem` [1..8])
  return (c', r')

in3 start = return start >>= moveKnight >>= moveKnight >>= moveKnight

canReachIn3 :: Pos -> Pos -> Bool
canReachIn3 start end = end `elem` in3 start

findRoute :: Pos -> Pos -> Int -> [Route]
findRoute from to moveCount = findRoute' [from] moveCount
  where
    findRoute' :: Route -> Int -> [Route]
    findRoute' route n 
      | n <= 0 = if head route == to then [reverse route] else []
      | otherwise = do
          r <- map (\p -> p:route) $ moveKnight $ head route
          findRoute' r (n-1)
          

