module StateTEval where

import Data.List.Split
import Data.Maybe
import Control.Monad.State
import Control.Applicative

eval :: String -> Float
eval = fromJust . evalStateT expr . splitOn " "

is :: String -> StateT [String] Maybe ()
is x = do
  (y:ys) <- get
  guard $ x == y
  put ys

pop = do
  (x:xs) <- get
  put xs
  return x

expr :: StateT [String] Maybe Float
expr = term >>= expr'

expr' x = do is "+"; (x+) <$> term >>= expr'
      <|> do is "-"; (x-) <$> term >>= expr'
      <|> return x

term = factor >>= term'

term' x = do is "*"; (x*) <$> factor >>= term'
      <|> do is "/"; (x/) <$> factor >>= term'
      <|> return x

factor = do is "("; x <- expr; is ")"; return x
      <|> read <$> pop

