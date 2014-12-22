main = print $ elementAt' [1..10] 5

elementAt :: [a] -> Int -> a
elementAt xs n = xs!!(n-1)

elementAt' :: [a] -> Int -> a
elementAt' (x:_) 1 = x
elementAt' (_:xs) n = elementAt' xs (n-1)
