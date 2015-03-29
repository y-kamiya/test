{-# LANGUAGE GADTs #-}

module StackT where

import Control.Monad.Operational
import Control.Monad.IO.Class
import Data.Functor ((<$>))

type Stack s = [s]

data StackI s a where
  Push :: s -> StackI s ()
  Pop  :: StackI s s

type StackP s m a = ProgramT (StackI s) m a

push :: (Monad m) => s -> StackP s m ()
push = singleton . Push

pop :: (Monad m) => StackP s m s 
pop = singleton Pop

interpret :: (Monad m) => StackP s m a -> Stack s -> m (Stack s)
interpret is stack = (\v -> eval v stack) =<< (viewT is)
  where
    eval :: (Monad m) => ProgramViewT (StackI s) m a -> Stack s-> m (Stack s)
    eval (Push x :>>= is) stack   = interpret (is ()) (x:stack)
    eval (Pop :>>= is) (x:stack)  = interpret (is x) stack
    eval (Return _) stack         = return stack

add :: (Monad m) => StackP Int m ()
add = do
  x <- pop
  y <- pop
  push (x + y)

addInput :: StackP Int IO ()
addInput = do
  push =<< read <$> liftIO getLine 
  push =<< read <$> liftIO getLine 
  add

defaultMain :: IO ()
defaultMain = (putStrLn . show) =<< interpret addInput [1,2]
