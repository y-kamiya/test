import System.Random
import Control.Monad

main = diff_select 6 49

diff_select :: Int -> Int -> IO [Int]
diff_select n max 
    | n <= 0  || max < 1 = return [] 
    | otherwise = do rs <- replicateM n $ (getStdRandom $ randomR (0, max - 1))
                     let list = [1..max]
                     return [list!!r | r <- rs]

