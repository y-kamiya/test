data Element a = Single a | Multiple Int a deriving Show

main = print $ encodeDirect [1,1,1,2,3,3,4,5,5]

encodeDirect :: (Eq a) => [a] -> [Element a]
encodeDirect [] = []
encodeDirect (x:xs) = let
    (first, rest) = span (==x) xs
    in [toElement $ (length (x:first), x)] ++ encodeDirect rest
        where 
            toElement :: (Int, a) -> Element a
            toElement (1, x) = Single x
            toElement (n, x) = Multiple n x

