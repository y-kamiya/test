data Element a = Single a | Multiple Int a deriving (Eq, Show)
--data Multiple a = Multiple Int a deriving Eq
--data Single a = Single a deriving Eq

--main = print $ packEncode2  "aaaabccaadeeee"--[1,1,1,2,3,3,4,5,5]
main = print $ packEncode2'  "aaaabccaadeeee"--[1,1,1,2,3,3,4,5,5]

packEncode2 :: (Eq a) => [a] -> [Element a]
packEncode2 xs = encode $ foldr makeGroup [[]] xs

makeGroup :: (Eq a) => a -> [[a]] -> [[a]]
makeGroup x [[]] = [[x]]
makeGroup x acc@(ys:yss) 
    | head ys == x = ([x] ++ ys):yss
    | otherwise    = [[x]] ++ acc

encode :: (Eq a) => [[a]] -> [Element a]
encode zss = let 
    counts = map length zss
    values = map head zss
    in zipToElement counts values
        where
            zipToElement :: [Int] -> [a] -> [Element a]
            zipToElement [] [] = []
            zipToElement (x:xs) (y:ys) 
                | x == 1    = [Single y] ++ zipToElement xs ys
                | otherwise = [Multiple x y] ++ zipToElement xs ys
                


packEncode2' :: (Eq a) => [a] -> [Element a]
packEncode2' = map encodeHelper . packEncode' 

packEncode' :: (Eq a) => [a] -> [(Int, a)]
packEncode' [] = []
packEncode' (x:xs) = let 
    (first, rest) = span (==x) xs
    in [(length (x:first), x)] ++ packEncode' rest

encodeHelper :: (Int, a) -> Element a
encodeHelper (1, x) = Single x
encodeHelper (n, x) = Multiple n x
