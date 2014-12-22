main = print $ removeAt [1..5] 2

removeAt :: [a] -> Int -> (Maybe a, [a])
removeAt [] _ = (Nothing, [])
removeAt (x:xs) 1 = (Just x, xs)
removeAt all@(x:xs) n 
    | n > 0 = (y, x:ys)
    | n <= 0 = (Nothing, all)
    where (y, ys) = removeAt xs (n-1)

