main = print $ insertAt 'X' "abc" 2

insertAt :: a -> [a] -> Int -> [a]
insertAt x xs n 
    | n <= 1 = x:xs 
    | length xs < n = xs ++ [x]
    | otherwise = head xs : insertAt x (tail xs) (n-1)
