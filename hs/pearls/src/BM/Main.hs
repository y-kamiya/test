import System.Environment
import Data.List

main :: IO ()
main = do
  args <- getArgs
  case args of
    ("1":ws:xs:[]) -> print $ matches1 ws xs


matches1 :: Eq a => [a] -> [a] -> [Int]
matches1 ws = map length . filter (endswish ws) . inits

endswish :: Eq a => [a] -> [a] -> Bool
endswish ws = initialMatch (reverse ws) . reverse
  where
    initialMatch [] _ = True
    initialMatch _ [] = False
    initialMatch (u:us) (v:vs) 
      |  u == v = initialMatch us vs
      | otherwise = False
