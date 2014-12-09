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
