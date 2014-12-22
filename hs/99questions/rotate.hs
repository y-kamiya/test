main = print $ rotate' [1..10] (-13)

rotate :: [a] -> Int -> [a]
rotate xs n 
    | n == 0 = xs
    | n > 0 = drop n xs ++ take n xs
    | n < 0 = drop n' xs ++ take n' xs
        where n' = length xs + n

rotate' :: [a] -> Int -> [a]
rotate' xs n 
    | n == 0 = xs
    | n < 0 = rotate' xs (length xs + n) 
rotate' (x:xs) n = rotate' (xs ++ [x]) (n-1)
