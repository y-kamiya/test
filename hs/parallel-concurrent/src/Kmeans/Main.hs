import Data.List
import Data.Ord
import Data.Tuple
import Data.Binary 

data Point = Point !Double !Double deriving (Eq, Show, Read)
data PointSum = PointSum !Int !Double !Double           
data Cluster = Cluster { clId :: Int, clCent :: Point } deriving (Eq, Show)

instance Binary Point where
    put (Point a b) = put a >> put b
    get = do a <- get; b <- get; return (Point a b)

zeroPoint :: Point
zeroPoint = Point 0 0

sqDistance :: Point -> Point -> Double
sqDistance (Point x1 y1) (Point x2 y2) = (x2 - x1)^2 + (y2 - y1)^2 

addToPointSum :: PointSum -> Point -> PointSum
addToPointSum (PointSum count x0 y0) (Point x y) = PointSum (count + 1) (x0 + x) (y0 + y)

pointSumToCluster :: Int -> PointSum -> Cluster
pointSumToCluster i (PointSum count x y) = Cluster i $ Point (x / n) (y / n)
  where n = fromIntegral count

findClosestCluster :: [Cluster] -> Point -> Int
findClosestCluster cs p = fst $ minimumBy (comparing snd) $ zip [0..] ds
  where
    ds = map (sqDistance p) $ map clCent cs

assign :: [Point] -> [Cluster] -> [Cluster]
assign ps cs = map (uncurry pointSumToCluster) $ zip [0..] newPointSums
  where
    newPointSums = foldr (makeNewPointSums cs) initialPointSums ps
    initialPointSums = take (length cs) $ infinitePointSums 0
    infinitePointSums n = PointSum n 0 0 : infinitePointSums (n+1) 

makeNewPointSums :: [Cluster] -> Point -> [PointSum] -> [PointSum]
makeNewPointSums cs p pss = take n pss ++ [psum] ++ drop (n+1) pss
  where
    n = findClosestCluster cs p
    psum = addToPointSum (pss!!n) p

main :: IO ()
main = do
    points <- decodeFile "points.bin"
    let -- points = [Point 1.0 1.0, Point 1.0 2.0, Point 12.0 13.0, Point 13.0 11.0]
        clusters = [Cluster 0 zeroPoint, Cluster 1 (Point 11.0 11.0)]
    r <- loop 0 points clusters
    print r
    where
      loop :: Int -> [Point] -> [Cluster] -> IO (Either String [Cluster])
      loop 100 ps cs = return $ Left "not converged"
      loop n ps cs = let cs' = assign ps cs 
                     in  case cs == cs' of
                           True -> return $ Right cs'
                           False -> do
                             print (n,cs')
                             loop (n+1) ps cs'

