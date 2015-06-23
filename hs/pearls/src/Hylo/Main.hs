

data Tree a = Leaf a | Node [Tree a] deriving Show

fold :: (a -> b) -> ([b] -> b) -> Tree a -> b
fold f g (Leaf x) = f x
fold f g (Node ts) = g $ map (fold f g) ts

unfold :: (b -> Bool) -> (b -> a) -> (b -> [b]) -> b -> Tree a
unfold p v h x = if p x then Leaf (v x)
                        else Node $ map (unfold p v h) (h x)


data LTree a = LLeaf a | LNode a [LTree a] deriving Show

fill :: (a -> b) -> ([b] -> b) -> Tree a -> LTree b
fill f g = fold (lleaf f) (lnode g)

lleaf f x = LLeaf (f x)
lnode g ts = LNode (g (map label ts)) ts

label (LLeaf x) = x
label (LNode x ts) = x

hylo :: ([a] -> b) -> ([b] -> b) -> ([a] -> [[a]]) -> [a] -> b
hylo f g h = fold f g . mkTree h

mkTree h = unfold single id h

single xs = length xs == 1

-- three examples
-- 1.
split xs = [take n xs, drop n xs] where n = length xs `div` 2

-- 2.
isegs xs = [init xs, tail xs]

recover xss = head (head xss) : last xss

-- 3.
minors [x,y] = [[x],[y]]
minors (x:xs) = map (x:) (minors xs) ++ [xs]


-- compose nexus
mkNexus f g = label . extractL . until singleL (stepL g) . initialL f

type Layer a = [a]

initialL :: ([a] -> b) -> [a] -> Layer (LTree b)
initialL f = map (lleaf f . wrap)
wrap x = [x]

singleL :: Layer (LTree b) -> Bool
singleL = single

extractL :: Layer (LTree b) -> LTree b
extractL = head

stepL :: ([b] -> b) -> Layer (LTree b) -> Layer (LTree b)
stepL g = map (lnode g) . group

group [] = []
group (x:y:xs) = [x,y] : group xs


-- why make Nexus
solve :: ([a] -> b) -> ([b] -> b) -> [a] -> b
solve f g = head . until single (map g . group) . map (f . wrap)

uncats [x,y] = [([x],[y])]
uncats (x:xs) = ([x],xs) : map (cons x) (uncats xs)
  where cons x (ys, zs) = (x:ys, zs)

lnode' g [u,v] = LNode (g $ zip (lspine u) (rspine v)) [u,v]

lspine, rspine :: LTree a -> [a]
lspine (LLeaf x) = [x]
lspine (LNode x [u,v]) = lspine u ++ [x]
rspine (LLeaf x) = [x]
rspine (LNode x [u,v]) = [x] ++ rspine v

main :: IO ()
main = print $ mkNexus id merge "abcd"
  where merge = concat
