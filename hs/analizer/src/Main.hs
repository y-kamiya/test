module Main where

import System.Environment
import Data.Functor ((<$>))
import Data.Monoid ((<>))
import Text.Printf

main :: IO ()
main = do
    args <- getArgs
    if length args /= 2
      then print "usage: analizer file1 file2"
      else analize args

analize :: [String] -> IO ()
analize [file1, file2] = do
    content1 <- map readFloat <$> lines <$> readFile file1
    content2 <- map readFloat <$> lines <$> readFile file2
    print $ "average of content1: " <> show (average content1)
    print $ "average of content2: " <> show (average content2)
    print $ "average of difference: " <> show (average $ zipWith (-) content2 content1)
    print $ "variance of difference: " <> show (variance $ zipWith (-) content2 content1)

average :: [Float] -> Float
average nums = sum nums / fromIntegral (length nums)

variance :: [Float] -> Float
variance nums = sum list / fromIntegral (length nums)
  where list = map (\num -> (num - ave) ^ 2) nums
        ave = average nums

readFloat :: String -> Float
readFloat s = read s

