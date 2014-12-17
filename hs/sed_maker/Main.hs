module Main where

import Data.Functor
import Data.List

data Action = S String String | D String deriving Show

main :: IO ()
main = do
    as <- toAction <$> lines <$> getContents
    let es = map construct as
    putStr $ "sed -i -e " ++ intercalate " -e " es ++ " $1"

construct :: Action -> String
construct (S a b) = concat ["\"s/", a, "/", b, "/g\""]
construct (D d) = concat ["\"/", d, "/d\""]

toAction :: [String] -> [Action]
toAction = map toAction'
  where
    toAction' :: String -> Action
    toAction' s@(c:_) 
      | c == 'S' = S (ws!!1) (ws!!2)
      | c == 'D' = D (ws!!1)
      where ws = words s
