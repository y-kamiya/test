main = print $ range' 4 9
--main = print $ range 4 9

range :: Int -> Int -> [Int]
range i j = [i..j]

range' :: Int -> Int -> [Int]
range' i j 
    | i > j = []
    | otherwise = i : range (i+1) j
