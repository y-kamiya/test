import Data.List

main = print $ groups [2,3,4] [1..10]


groups :: [Int] -> [a] -> [[[a]]]
groups ns xs = 
    where xxxs = [combinations n xs | n <- ns]

combinations :: Int -> [a] -> [[a]]
combinations 0 _ = [[]]
combinations n xs = [y:ys | y:ys' <- tails xs, ys <- combinations (n-1) ys']
