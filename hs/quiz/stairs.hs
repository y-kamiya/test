main :: IO ()
main = print $ stairs 4

stairs :: Int -> Int
stairs n 
    | n == 1 = 1
    | n == 2 = 2
    | n == 3 = 4
    | otherwise = stairs (n-1) + stairs (n-2) + stairs (n-3)
