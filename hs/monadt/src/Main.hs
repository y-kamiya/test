module Main where

import Control.Monad.State

main :: IO ()
main = do
  let st = StateT $ \s -> return ("test", s)
  print =<< runStateT st 0


lift' m = StateT $ \s -> m >>= \a -> return (a, s)
get' = StateT $ \s -> return (s,s)
modify' f = StateT $ \s -> ((), f s)

a `bind` f = StateT $ \s -> runStateT a s >>= \(a', s') -> runStateT (f a') s'
