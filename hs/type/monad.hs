module MonadTest where

import Control.Monad

permutation :: Eq a => Int -> [a] -> [[a]]
permutation n xs = iter 0 [] where  
    iter m ys 
        | m == n = return (reverse ys)
        | otherwise = do
            x <- xs
            guard (x `notElem` ys) 
            iter (m+1)  (x:ys)

permutation' :: Eq a => Int -> [a] -> [[a]]
permutation' n xs = iter 0 [] where  
    iter m ys 
        | m == n = return (reverse ys)
        | otherwise = xs >>= \x -> guard (x `notElem` ys) >> iter (m+1)  (x:ys)
