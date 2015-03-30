{-# LANGUAGE GADTs #-}

import Control.Monad.Free

data Stack a where
    Push :: Int -> Stack ()
    Pop  :: Stack Int
    End  :: Stack ()

instance Functor Stack where
    fmap f (Push x) = Push (f x)
    fmap f Pop = Pop
    fmap f End = End

instruction :: Free Stack ()
instruction = Push 
