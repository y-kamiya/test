--main = print $ dropEvery [1..10] 2
--main = print $ dropEvery' [1..10] 2
main = print $ dropEvery'' [1..10] 2

dropEvery :: [a] -> Int -> [a]
dropEvery [] _ = []
dropEvery xs n = (init $ take n xs) ++ dropEvery (drop n xs) n

dropEvery' :: (Eq a) => [a] -> Int -> [a]
dropEvery' xs n = concat $ map extract $ zip [0..] xs 
    where 
        extract :: (Int, a) -> [a]
        extract (index, value)
            | elem index [0,n..] = [value]
            | otherwise = []

dropEvery'' :: (Eq a) => [a] -> Int -> [a]
dropEvery'' xs n = [i | (i,c) <- (zip xs [1,2..]), (mod c n) /=0]
