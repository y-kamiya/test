--main = print $ slice [1..10] 3 7
main = print $ slice' [1..10] 3 6

slice :: [a] -> Int -> Int -> [a]
slice xs i k = drop (i-1) $ take k xs

slice' :: [a] -> Int -> Int -> [a]
slice' l@(x:xs) i k 
    | 1 < i = slice' xs (i-1) (k-1)
    | k == 1 = [x]
    | i == 1 = x:slice' xs 1 (k-1)
