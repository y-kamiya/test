import System.Random
import Control.Monad

main = rnd_permu [1..6] 

rnd_permu :: (Show a) => [a] -> IO [a]
rnd_permu [] = return []
rnd_permu xs = do 
    r <- getStdRandom $ randomR (1, length xs)
    rest <- (rnd_permu $ removeAt xs r)
    return ((xs!!(r-1)) : rest)
        where
            removeAt :: [a] -> Int -> [a]
            removeAt xs n = take (n-1) xs ++ drop n xs
