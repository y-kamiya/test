{-# LANGUAGE GADTs #-}

import System.Environment
import Control.Monad.Free

import qualified CharIO as CharIO
import qualified Stack as Stack
import qualified Game as Game

main :: IO ()
main = do
  (arg:_) <- getArgs    
  case arg of
    "chario" -> CharIO.defaultMain
    "stack" -> print $ Stack.runStack Stack.add [1,3]
    "game1" -> Game.defaultMain
    "game2" -> print $ Game.defaultMain' (0,0)
