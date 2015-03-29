{-# LANGUAGE GADTs #-}

import System.Environment
import Control.Monad.Operational

import qualified StackT as T
import qualified Question as Q

type Stack s = [s]

data StackI s a where
  Push :: s -> StackI s ()
  Pop  :: StackI s s

type StackP s a = Program (StackI s) a

push :: s -> StackP s ()
push = singleton . Push

pop :: StackP s s
pop = singleton Pop

interpret :: StackP s a -> Stack s -> Stack s
interpret = eval . view
  where
    eval :: ProgramView (StackI s) a -> Stack s -> Stack s
    eval (Push x :>>= is) stack   = interpret (is ()) (x:stack)
    eval (Pop :>>= is) (x:stack)  = interpret (is x) stack
    eval (Return _) stack         = stack

add :: StackP Int ()
add = do
  x <- pop
  y <- pop
  push (x + y)

main :: IO ()
main = do
  (arg:_) <- getArgs    
  case arg of
    "stacks" -> (putStrLn . show) $ interpret add [1,2]
    "stackt" -> T.defaultMain
    "question" -> Q.defaultMain
