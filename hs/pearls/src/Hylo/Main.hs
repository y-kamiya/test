

data Tree a = Leaf a | Node [Tree a]

fold :: (a -> b) -> ([b] -> b) -> Tree a -> b
fold f g (Leaf x) = f x
fold f g (Node ts) = g $ map (fold f g) ts

unfold :: (b -> Bool) -> (b -> a) -> (b -> [b]) -> b -> Tree a
unfold p v h x = if p x then Leaf (v x)
                        else Node $ map (unfold p v h) (h x)

main :: IO ()
main = print "aa"
