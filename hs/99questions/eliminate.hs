main = print $ eliminate' "aaaabbcdaabbb5"

eliminate :: (Eq a) => [a] -> [a]
eliminate (x:y:ys) = (if x == y then [] else [x]) ++ eliminate (y:ys)
eliminate (x:[]) = [x] 

eliminate' :: (Eq a) => [a] -> [a]
eliminate' = foldr exe [] 

exe :: (Eq a) => a -> [a] -> [a]
exe y [] = [y]
exe y ys  
    | y /= head ys = y:ys
    | otherwise    = ys
