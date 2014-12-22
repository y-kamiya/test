import System.Random
import Control.Monad

main = rnd_select [1..10] 5

rnd_select :: [a] -> Int -> IO [a]
rnd_selet [] _ = return []
rnd_select xs n 
    | n <= 0 = return []
    | otherwise = do rs <- replicateM n $ (getStdRandom $ randomR (0, length xs - 1))
                     return [xs!!r | r <- rs]  
