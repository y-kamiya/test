--main = print $ repli [1,2,3] 3
main = print $ repli' [1,2,3] 3

repli :: [a] -> Int -> [a]
repli xs n = concatMap (replicate n) xs

repli' :: [a] -> Int -> [a]
repli' xs n = foldl (\acc x -> acc ++ replicate n x) [] xs
