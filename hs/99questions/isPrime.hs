module IsPrime where
import Data.List (group, nub)
import Control.Monad

-- Problem 31
isPrime :: Int -> Bool
isPrime n 
    | n < 2 = False
    | n == 2 = True
    | otherwise = not $ any (\x -> (n `mod` x) == 0) [2..n-1]


-- Problem 32
myGCD :: Int -> Int -> Int
myGCD m n = let abs_m = abs m
                abs_n = abs n
                a = max abs_m abs_n
                b = min abs_m abs_n
            in helper' a b
                where helper a b = let r = a `mod` b
                                   in if r == 0
                                      then b
                                      else helper b r 
                      helper' a b 
                        | b == 0 = a
                        | otherwise = helper' b (a `mod` b)

myGCD' :: Int -> Int -> Int
myGCD' a b 
    | b == 0 = abs a
    | otherwise = myGCD' b (a `mod` b) 


-- Problem 33
coprime :: Int -> Int -> Bool
coprime m n 
    | myGCD m n == 1 = True
    | otherwise = False

coprime' :: Int -> Int -> Bool
coprime' m n = gcd m n == 1


-- Problem 34
phi :: Int -> Int
phi 1 = 1
phi n = length $ totient n
    where totient :: Int -> [Int]
          totient n = foldr (\x acc -> if coprime n x then x:acc else acc) [] [1..n]

phi' :: Int -> Int
phi' 1 = 1
phi' n = foldl (\acc x -> if coprime n x then acc+1 else acc) 0 [1..n]

phi'' :: Int -> Int
phi'' 1 = 1
phi'' n = length $ filter (coprime n) [1..n]

                                
-- Problem 35
primeFactors :: Int -> [Int]
primeFactors 1 = []
primeFactors n 
    | max < 2 || factor == 1 = [n]
    | otherwise = factor : (primeFactors $ n `div` factor) 
    where max = fromIntegral $ floor $ sqrt $ fromIntegral n 
          factor = findFactor n [2..max]
        
          findFactor :: Int -> [Int] -> Int
          findFactor n [] = n
          findFactor n xs
            | (n `mod` head xs) == 0 = head xs
            | otherwise = findFactor n (tail xs)

-- Problem 36
primeFactorsMulti :: Int -> [(Int, Int)]
primeFactorsMulti n = let xxs = group $ primeFactors n
                      in foldr (\xs acc -> (head xs, length xs) : acc) [] xxs

-- Problem 37
phi_improved :: Int -> Int
phi_improved  = helper . primeFactorsMulti 
    where
        helper :: [(Int, Int)] -> Int
        helper = foldl (\acc (p, m) -> acc * (p-1) * (power p (m-1))) 1 
        
        power :: Int -> Int -> Int
        power a b = floor $ (fromIntegral a) ** (fromIntegral b)


-- Problem 39
primesR :: Int -> Int -> [Int]
primesR a b = drop (primesLength a) $ primes b
    where primesLength = length . primes 

primes :: Int -> [Int]
primes n = foldr (\x acc -> if isPrime x then x:acc else acc) [] [2..n]


-- Problem 40
goldbach :: Int -> (Int, Int)
goldbach n = head $ filter (\(x, y) -> x + y == n) $ makeTuple $ primes n
    where 
        makeTuple :: [Int] ->  [(Int, Int)]
        makeTuple xs = [(x, x') | x <- xs, x' <- xs]

-- Problem 41
goldbachList :: Int -> Int -> [(Int, Int)]
goldbachList a b = map goldbach [x | x <- [a..b], even x]

goldbachList' :: Int -> Int -> Int -> [(Int, Int)]
goldbachList' a b min = filter (\(x, y) -> min < x && min < y) $ map goldbach [x | x <- [a..b], even x]

-- Problem 46
and' :: Bool -> Bool -> Bool
and' True True = True
and' _ _ = False

or' :: Bool -> Bool -> Bool
or' True _ = True
or' _ True = True
or' _ _ = False

nand :: Bool -> Bool -> Bool
nand a  = not . (and' a) 

xor :: Bool -> Bool -> Bool
xor a b = (a /= b)

impl :: Bool -> Bool -> Bool
impl False _ = True
impl _ True = True
impl _ _ = False

equ :: Bool -> Bool -> Bool
equ a b = (a == b)

table :: (Bool -> Bool -> Bool) -> [(Bool, Bool, Bool)]
table f = [(a, b, f a b) | a <- [True, False], b <- [True, False]]


-- Problem 48
tablen n f = map f $ replicateM n [True, False]

-- Problem 49
gray :: Int -> [String]
gray n = replicateM n ['0', '1']

gray' :: Int -> [String]
gray' 0 = [""]
gray' n = 
    let xs = gray' (n-1)
    in  map ('0':) xs ++ map ('1':) xs


-- Problem 50
data Tree a = Empty | Node (a, Int) (Tree a) (Tree a) deriving (Show)

singleton :: (a, Int) -> Tree a
singleton (a, n) = Node (a, n) Empty Empty

treeInsert :: (Ord a) => (a, Int) -> Tree a -> Tree a
treeInsert (x, n) Empty = singleton (x, n)
treeInsert (x, n) (Node (y, m) left right)
    | n <= m = Node (y, m) (treeInsert (x, n) left) right
    | n > m  = Node (y, m) left (treeInsert (x, n) right)

treeMerge :: Tree a -> Tree a -> Tree a
treeMerge tree1@(Node (x,n) _ _) tree2@(Node (y,m) _ _)
    | n <= m = Node (x, n+m) tree1 tree2
    | n > m  = Node (y, n+m) tree2 tree1

huffman :: [(a, Int)] -> [(a, String)]
huffman = (map toAnswer) . findLeafs "" . fabricateTree . map singleton
    where fabricateTree :: [Tree a] -> Tree a
          fabricateTree [x] = x
          fabricateTree xs = 
              let x:x':xs' = sortTree xs
                  mergedTrees = (treeMerge x x') : xs'
              in  fabricateTree mergedTrees

          toAnswer :: (Tree a, String) -> (a, String)
          toAnswer (Node (x,_) _ _ , bits) = (x, bits)

sortTree :: [Tree a] -> [Tree a]
sortTree []  = []
sortTree (tree@(Node (x,n) _ _) : xs) = 
    let left  = [l | l@(Node (y,m) _ _) <- xs, m <= n]
        right = [r | r@(Node (z,k) _ _) <- xs, n < k]
    in  (sortTree left) ++ [tree] ++ (sortTree right)

{-
sortTupple :: (a, b) -> (
sortTupple []  = []
sortTupple (tree@(Node (x,n) _ _) : xs) = 
    let left  = [l | l@(Node (y,m) _ _) <- xs, m <= n]
        right = [r | r@(Node (z,k) _ _) <- xs, n < k]
    in  (sortTupple left) ++ [tree] ++ (sortTupple right)
-}
{-
findLeaf :: (Eq a) => (a, Int) -> (String, Tree a) -> String 
findLeaf (x, n) (bits, (Node (y, m) left right))
    | n == m && x == y = bits
    | n < m = findLeaf (x, n) (bits ++ "0", left)
    | n > m = findLeaf (x, n) (bits ++ "1", right)
-}


findLeafs :: String -> Tree a -> [(Tree a, String)]
findLeafs bits leaf@(Node _ Empty Empty) = [(leaf, bits)]
findLeafs bits (Node _ left right) = concat [findLeafs (bits++"0") left, findLeafs (bits++"1") right]
