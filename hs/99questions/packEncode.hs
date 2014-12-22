main = print $ packEncode' [1,1,1,2,3,3,4,5,5]

packEncode :: (Eq a) => [a] -> [(Int, a)]
packEncode xs = encode $ foldr makeGroup [[]] xs

makeGroup :: (Eq a) => a -> [[a]] -> [[a]]
makeGroup x [[]] = [[x]]
makeGroup x acc@(ys:yss) 
    | head ys == x = ([x] ++ ys):yss
    | otherwise    = [[x]] ++ acc

encode :: [[a]] -> [(Int, a)]
encode zss = let 
    counts = map length zss
    values = map head zss
    in zip counts values


packEncode' :: (Eq a) => [a] -> [(Int, a)]
packEncode' [] = []
packEncode' (x:xs) = let 
    (first, rest) = span (==x) xs
    in [(length (x:first), x)] ++ packEncode' rest
