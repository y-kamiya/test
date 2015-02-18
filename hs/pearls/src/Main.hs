import Data.Array
import Data.List

main :: IO ()
main = do
  -- print $ sort list
  -- print $ smallestNotExist list
  -- print $ answerWithArrayBasedApproach list
  print $ solutions [1,2,3,4,5,6,7]

list :: [Int]
list = [8,23,9,0,12,11,1,10,13,7,41,4,14,21,5,17,3,19,2,6]

smallestNotExist :: [Int] -> Int
smallestNotExist xs = fst $ head $ dropWhile (uncurry (==)) $ zip [0..] $ sort xs


answerWithArrayBasedApproach :: [Int] -> Int
answerWithArrayBasedApproach = minFree
  where
    minFree :: [Int] -> Int
    minFree = search . checklist

    search :: Array Int Bool -> Int
    search = length . takeWhile id . elems

    checklist :: [Int] -> Array Int Bool
    checklist ns = accumArray (||) False (0,n) $ zip (filter (<=n) ns) $ repeat True
      where n = length ns




-- #6
type Expression = [Term]
type Term = [Factor]
type Factor = [Digit]
type Digit = Int

valExpr :: Expression -> Int
valExpr = sum . map valTerm

valTerm :: Term -> Int
valTerm = product . map valFact

valFact :: Factor -> Int
valFact = foldl1 (\n d -> 10 * n + d)

good :: Int -> Bool
good v = (v == 100)

extend :: Int -> [Expression] -> [Expression]
extend x [] = [[[[x]]]]
extend x es = concatMap (glue x) es
  where
    glue :: Digit -> Expression -> [Expression]
    glue x ((xs:xss):xsss) = [((x:xs):xss):xsss, ([x]:xs:xss):xsss, [[x]]:(xs:xss):xsss]

expressions :: [Digit] -> [Expression]
expressions = foldr extend []

solutions = filter (good . valExpr) . expressions


-- #7 
data Tree = Leaf Int | Fork Tree Tree deriving Show

cost (Leaf x) = x
cost (Fork u v) = 1 + (cost u `max` cost v)

--mincostTree = minBy cost . trees

trees :: [Int] -> [Tree]
trees [x] = [Leaf x]
trees (x:xs) = concatMap (prefixes x) (trees xs)

prefixes :: Int -> Tree -> [Tree]
prefixes x t@(Leaf y) = [Fork (Leaf x) t]
prefixes x t@(Fork u v) = [Fork (Leaf x) t] ++ [Fork u' v | u' <- prefixes x u]

foldrn :: (a -> b -> b) -> (a -> b) -> [a] -> b
foldrn f g [x] = g x
foldrn f g (x:xs) = f x (foldrn f g xs)

trees' :: [Int] -> [Tree]
trees' = foldrn (concatMap . prefixes) (wrap . Leaf)

wrap x = [x]
