module StateEval where

import Data.List.Split
import Control.Monad.State

eval :: String -> Float
eval = evalState expr . splitOn " "

expr :: 
