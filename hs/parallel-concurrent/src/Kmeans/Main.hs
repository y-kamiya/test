import Data.List
import Data.Ord
import Data.Tuple
import Data.Binary 
import Data.Functor 
import qualified Data.Vector as V
import qualified Data.Vector.Mutable as MV 

data Point = Point !Double !Double deriving (Eq, Show, Read)
data PointSum = PointSum !Int !Double !Double           
data Cluster = Cluster { clId :: Int, clCent :: Point } deriving (Eq, Show, Read)

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

findClosestCluster :: [Cluster] -> Point -> Cluster
findClosestCluster cs p = fst $ minimumBy (comparing snd) ds
  where
    ds = [(c, sqDistance p $ clCent c) | c <- cs]

assign :: [Point] -> [Cluster] -> V.Vector PointSum
assign ps cs = V.create $ do
  vps <- MV.replicate (length cs) (PointSum 0 0 0)
  let addPoint p = do
        let n = clId $ findClosestCluster cs p
        ps' <- MV.read vps n
        MV.write vps n $ addToPointSum ps' p
  mapM_ addPoint ps
  return vps

makeNewClusters :: V.Vector PointSum -> [Cluster]
makeNewClusters vps = map (uncurry pointSumToCluster) $ zip [0..] $ V.toList vps

main :: IO ()
main = do
    points <- decodeFile "points.bin"
    clusters <- read <$> readFile "clusters"
    r <- loop 0 points clusters
    print r
    where
      loop :: Int -> [Point] -> [Cluster] -> IO (Either String [Cluster])
      loop 100 _ _ = return $ Left "not converged"
      loop n ps cs = let cs' = makeNewClusters $ assign ps cs 
                     in  case cs == cs' of
                           True -> return $ Right cs'
                           False -> do
                             print (n,cs')
                             loop (n+1) ps cs'

