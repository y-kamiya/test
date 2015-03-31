{-# LANGUAGE GADTs #-}

module Stack where

import Control.Monad.Free

type Stack = [Int]

data StackI a = Pop (Int -> a) | Push Int a

instance Functor StackI where
    fmap f (Pop g) = Pop (f . g)
    fmap f (Push n x) = Push n (f x)

pop :: Free StackI Int
pop = Free $ Pop $ \n -> Pure n

push :: Int -> Free StackI ()
push n = Free $ Push n (Pure ())

add :: Free StackI ()
add = do
    x <- pop
    y <- pop
    push (x + y)

runStack :: Free StackI a -> Stack -> Stack
runStack (Pure _) xs = xs
runStack (Free (Pop f)) (x:xs) = runStack (f x) xs
runStack (Free (Push n next)) xs = runStack next (n:xs)

