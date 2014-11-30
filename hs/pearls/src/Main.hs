import Data.Array
import Data.List

main :: IO ()
main = do
  print $ sort list
  print $ smallestNotExist list
  print $ answerWithArrayBasedApproach list

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

