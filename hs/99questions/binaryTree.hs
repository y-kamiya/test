import Data.List
import qualified Data.Foldable as F
import Data.Monoid 

data Tree a = Empty | Branch a (Tree a) (Tree a) deriving (Show, Eq)

leaf a = Branch a Empty Empty


-- Program 55
cbalTree :: Int -> [Tree Char]
cbalTree 0 = [Empty]
cbalTree n = let (q, r) = (n-1) `quotRem` 2
             in  [Branch 'x' left right | i <- [q..q+r],
                                          left <- cbalTree i,
                                          right <- cbalTree (n-i-1)]
-- Program 56
symmetric :: Tree a -> Bool
symmetric (Branch x left right) = eq left right 
    where
        eq :: Tree a -> Tree a -> Bool
        eq Empty Empty = True
        eq (Branch _ _ _) Empty = False
        eq Empty (Branch _ _ _) = False
        eq (Branch y ll lr) (Branch z rl rr) = eq ll rr && eq lr rl

-- Program 57
construct :: [Int] -> Tree Int
construct [] = Empty
construct [x] = leaf x
construct xs = let (left, middle, right) = separate xs
               in  Branch middle (construct left) (construct right)
    where
        separate :: [Int] -> ([Int], Int, [Int])
        separate xs = 
            let sortedList = sort xs
                middle = sortedList!!((length xs) `div` 2)
                left = takeWhile (< middle) sortedList
                right = dropWhile (<= middle) sortedList
            in  (left, middle, right)

construct' :: (Ord a) => [a] -> Tree a
construct' = foldl (flip insertTree) Empty 
    where 
        insertTree :: (Ord a) => a -> Tree a -> Tree a
        insertTree x Empty = leaf x
        insertTree x tree@(Branch y left right)
            | x < y = Branch y (insertTree x left) right
            | x > y = Branch y left (insertTree x right)
            | x == y = tree

-- Program 58
symCbalTrees :: Int -> [Tree Char]
symCbalTrees n = filter symmetric (cbalTree n)




tree4 = Branch 1 (Branch 2 Empty (Branch 4 Empty Empty))
                 (Branch 2 Empty Empty)
-- Program 61
countLeaves :: Tree a -> Int
countLeaves = foldl (+) 0 . tree2List 
    where
        tree2List :: Tree a -> [Int]
        tree2List Empty = [0]
        tree2List (Branch _ Empty Empty) = [1]
        tree2List (Branch _ left right) = concat $ [tree2List left, tree2List right]


-- Program 61A
leaves :: Tree a -> [a]
leaves Empty = []
leaves (Branch x Empty Empty) = [x]
leaves (Branch x left right) = concat [leaves left, leaves right]

-- Program 62
internals :: Tree a -> [a]
internals Empty = []
internals (Branch _ Empty Empty) = []
internals (Branch x left right) = concat [[x], internals left, internals right]


-- Program 62B
atLevel :: Tree a -> Int -> [a]
atLevel Empty n = []
atLevel (Branch x l r) 1 = [x]
atLevel (Branch x l r) n 
    | n < 1 = []
    | otherwise = concat [atLevel l (n-1), atLevel r (n-1)]    

    

-- Program 63
completeBinaryTree :: Int -> Tree Char
completeBinaryTree n = insertNode 1
    where  
        insertNode :: Int -> Tree Char
        insertNode x 
            | x > n = Empty
            | otherwise = Branch 'x' (insertNode (2*x)) (insertNode (2*x+1)) 


-- Program 64
tree64 = Branch 'n'
                (Branch 'k'
                        (Branch 'c'
                                (Branch 'a' Empty Empty)
                                (Branch 'h'
                                        (Branch 'g'
                                                (Branch 'e' Empty Empty)
                                                Empty
                                        )
                                        Empty
                                )
                        )
                        (Branch 'm' Empty Empty)
                )
                (Branch 'u'
                        (Branch 'p'
                                Empty
                                (Branch 's'
                                        (Branch 'q' Empty Empty)
                                        Empty
                                )
                        )
                        Empty
                )

type Pos = (Int, Int)
layout :: Tree Char -> Tree (Char, Pos)
layout = makeTree 1 1
    where
        makeTree :: Int -> Int -> Tree Char -> Tree (Char,Pos)
        makeTree _ _ Empty = Empty
        makeTree x y tree@(Branch c l r) = let leftNum = (countLeftNodes tree)
                                           in Branch (c, (leftNum+x, y)) (makeTree x (y+1) l) (makeTree (leftNum+x+1) (y+1) r) 
            
        
        
countLeftNodes :: Tree Char -> Int
countLeftNodes Empty = 0
countLeftNodes (Branch _ l r) = foldl (+) 0 $ makeList l
    where
        makeList :: Tree Char -> [Int]
        makeList Empty = [0]
        makeList (Branch _ l r) = [1] ++ (makeList l) ++ (makeList r)



-- Program 65
tree65 = Branch 'n'
                (Branch 'k'
                        (Branch 'c'
                                (Branch 'a' Empty Empty)
                                (Branch 'e'
                                        (Branch 'd' Empty Empty)
                                        (Branch 'g' Empty Empty)
                                )
                        )
                        (Branch 'm' Empty Empty)
                )
                (Branch 'u'
                        (Branch 'p'
                                Empty
                                (Branch 'q' Empty Empty)
                        )
                        Empty
                )


layout' :: Tree Char -> Tree (Char, Pos)
layout' tree = layoutFromRootPos tree ((rootX tree 1),1) 
    where
        layoutFromRootPos :: Tree Char -> Pos -> Tree (Char, Pos) 
        layoutFromRootPos Empty _ = Empty 
        layoutFromRootPos (Branch c l r) pos@(x,y) = Branch (c,pos) (layoutFromRootPos l (x-d,y+1)) (layoutFromRootPos r (x+d,y+1))
            where d = 2^((level tree) - (y+1))

        rootX :: Tree a -> Int -> Int
        rootX Empty _ = 0
        rootX (Branch _ l _) n = 2^(n-1) + (rootX l (n+1))

level :: Tree a -> Int
level Empty = 0
level tree@(Branch _ _ _) = F.foldl max 1 $ levelTree tree 1
    where   
        levelTree :: Tree a -> Int -> Tree Int
        levelTree Empty _ = Empty
        levelTree (Branch _ l r) n = Branch n (levelTree l (n+1)) (levelTree r (n+1))

level' :: Tree a -> Int
level' Empty = 0
level' (Branch _ l r) = max (level' l) (level' r) + 1


-- Program 66

-- Program 67
stringToTree :: String -> Tree Char
stringToTree xs = foldl parse Empty xs
    where  
        parse :: Tree Char -> Char -> Tree Char
        parse Empty x 
            | x `elem` ['a'..'z'] = leaf x
            | otherwise = Empty
        parse (Branch _ l r) x
            | x == 

instance Functor Tree where
    fmap f Empty = Empty
    fmap f (Branch x l r) = Branch (f x) (fmap f l) (fmap f r)

instance F.Foldable Tree where
    foldMap f Empty = mempty
    foldMap f (Branch x l r) = F.foldMap f l `mappend`
                               f x           `mappend`
                               F.foldMap f r
