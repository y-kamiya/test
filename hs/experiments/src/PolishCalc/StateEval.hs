module StateEval where

import Data.List.Split
import Control.Monad.State

eval :: String -> Float
eval = evalState expr . splitOn " "

pop = do
  (x:xs) <- get
  put xs
  return x

{-
expr :: State [String] Float
expr = do
  y <- term
  expr' y

expr' x = do
  src <- get
  case src of
    ("+":_) -> do
      pop
      y <- term
      expr' $ x + y
    ("-":_) -> do
      pop
      y <- term
      expr' $ x - y
    _ -> return x

term = do
  y <- factor
  term' y

term' x = do
  src <- get
  case src of
    ("*":_) -> do
      pop
      y <- factor
      term' $ x * y
    ("/":_) -> do
      pop
      y <- factor
      term' $ x / y
    _ -> return x

factor = do
  x <- pop
  case x of
    "(" -> do
      y <- expr
      z <- pop
      case z of
        ")" -> return y
    _ -> return $ read x
-}

expr = term >>= expr'

expr' x = get >>= f
  where
    f ("+":_) = pop >> (x+) <$> term >>= expr'
    f ("-":_) = pop >> (x-) <$> term >>= expr'
    f _ = return x

term = factor >>= term'

term' x = get >>= f
  where
    f ("*":_) = pop >> (x*) <$> factor >>= term'
    f ("/":_) = pop >> (x/) <$> factor >>= term'
    f _ = return x

factor = pop >>= f
  where
    f "(" = do
      y <- expr
      z <- pop
      case z of
        ")" -> return y
    f x = return $ read x
