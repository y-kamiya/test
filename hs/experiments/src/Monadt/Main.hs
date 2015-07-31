module Main where

import Control.Monad.State

main :: IO ()
main = do
  let st = StateT $ \s -> return ("test", s)
  print =<< runStateT st 0


lift' :: Monad m => m a -> StateT s m a
lift' m = StateT $ \s -> m >>= \a -> return (a, s)

get' :: Monad m => StateT s m s
get' = StateT $ \s -> return (s,s)

modify' :: Monad m => (s -> s) -> StateT s m ()
modify' f = StateT $ \s -> return ((), f s)

a `bind` f = StateT $ \s -> runStateT a s >>= \(a', s') -> runStateT (f a') s'
