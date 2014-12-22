--main = print $ split [1..10] 3
main = print $ split' [1..10] 3

split :: [a] -> Int -> ([a],[a])
split xs n = (take n xs, drop n xs)

split' :: [a] -> Int -> ([a],[a])
split' l@(x:xs) n
    | n > 0 = (x:ys, zs)
    | otherwise = ([], l)
        where
            (ys, zs) = split' xs (n-1)
