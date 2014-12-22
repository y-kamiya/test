main = print $ pack [1,1,1,2,3,3,4,5,5]

pack :: (Eq a) => [a] -> [[a]]
pack xs = foldr makeGroup [[]] xs

makeGroup :: (Eq a) => a -> [[a]] -> [[a]]
makeGroup x [[]] = [[x]]
makeGroup x acc@(ys:yss) 
    | head ys == x = ([x] ++ ys):yss
    | otherwise    = [[x]] ++ acc
