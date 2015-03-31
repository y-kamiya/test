{-# LANGUAGE DeriveFunctor #-}

module Game where

import Prelude hiding (Right, Left)
import System.Random
import Control.Monad.Free

data MoveI a = Go a | Back a | Right a | Left a 
    deriving (Show, Functor)

go :: Free MoveI ()
go = liftF $ Go ()

back :: Free MoveI ()
back = liftF $ Back ()

right :: Free MoveI ()
right = liftF $ Right ()

left :: Free MoveI ()
left = liftF $ Left ()

runStdIO :: Free MoveI a -> IO a
runStdIO (Pure a) = return a
runStdIO (Free (Go next))    = putStr "Go " >> runStdIO next
runStdIO (Free (Back next))  = putStr "Back " >> runStdIO next
runStdIO (Free (Right next)) = putStr "Right " >> runStdIO next
runStdIO (Free (Left next))  = putStr "Left " >> runStdIO next

calcPoint :: (Int, Int) -> Free MoveI a -> (Int, Int)
calcPoint t (Pure _) = t
calcPoint (x,y) (Free (Go next))    = calcPoint (x,y+1) next
calcPoint (x,y) (Free (Back next))  = calcPoint (x,y-1) next
calcPoint (x,y) (Free (Right next)) = calcPoint (x+1,y) next
calcPoint (x,y) (Free (Left next))  = calcPoint (x-1,y) next

getActionAI :: RandomGen g => g -> Free MoveI ()
getActionAI g = foldr (>>) (Pure ()) $ getMoves g 5 []
  where
    getMoves g 0 moves = moves
    getMoves g n moves = do
      let (x, g') = randomR (1 :: Int,4) g
      let moves' = case x of
            1 -> go : moves
            2 -> back : moves
            3 -> right : moves
            4 -> left : moves
      getMoves g' (n-1) moves'

defaultMain :: IO ()
defaultMain = do
  g <- getStdGen
  runStdIO $ getActionAI g

defaultMain' :: (Int, Int) -> IO ()
defaultMain' t = do
  g <- getStdGen
  print $ calcPoint t $ getActionAI g

defaultMain'' :: (Int, Int) -> (Int, Int)
defaultMain'' t = calcPoint t actions

actions :: Free MoveI ()
actions = go >> go >> right >> right >> back
