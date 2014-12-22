main = print $ mylength'' [1..3]

mylength :: [a] -> Int
mylength = sum . (map const1)
    where
        const1 :: a -> Int
        const1 = const 1

mylength' :: [a] -> Int
mylength' [] = 0
mylength' (_:xs) = 1 + mylength' xs

mylength'' = foldl (\n _ -> n + 1) 0
