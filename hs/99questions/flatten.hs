data NestedList a = Elem a | List [NestedList a] deriving Show

main = print $ flatten (List [Elem 1, List [Elem 2, List [Elem 3, Elem 4]]])

flatten :: NestedList a -> [a]
flatten (Elem x) = [x]
flatten (List xs) = concat $ map flatten xs

flatten' :: NestedList a -> [a]
flatten' (Elem x) = [x]
flatten' (List (x:xs)) = flatten' x ++ flatten' (List xs)
flatten' (List []) = []
