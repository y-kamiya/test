module Main where

import Data.List.Split
import qualified StateEval as SE

type Result = (Float, [String])

main :: IO ()
main = do
  print $ eval "1 + 2 * 3 - 1"
  print $ eval "( 1 + 2 ) * 3 - 1"
  print $ SE.eval "1 + 2 * 3 - 1"
  print $ SE.eval "( 1 + 2 ) * 3 - 1"

eval :: String -> Float
eval = fst . expr . splitOn " "

expr :: [String] -> Result
expr src = let (y,  src') = term src in expr' y src'

expr' :: Float -> [String] -> Result
expr' x ("+":src) = let (y, src') = term src in expr' (x + y) src'
expr' x ("-":src) = let (y, src') = term src in expr' (x - y) src'
expr' x src = (x, src)

term :: [String] -> Result
term src = let (y, src') = factor src in term' y src'

term' :: Float -> [String] -> Result
term' x ("*":src) = let (y, src') = factor src in term' (x * y) src'
term' x ("/":src) = let (y, src') = factor src in term' (x / y) src'
term' x src = (x, src)

factor :: [String] -> Result
factor ("(":src) = case expr src of
                     (y, (")":src')) -> (y, src')
factor (x:xs) = (read x, xs)

