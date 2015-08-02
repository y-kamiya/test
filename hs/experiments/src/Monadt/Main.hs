module Main where

import Control.Monad.State
import Control.Monad.Reader
import Control.Monad.Trans.Either

main :: IO ()
main = do
  let st = StateT $ \s -> return ("test", s)
  print =<< runStateT st 0
  (a, s) <- runStateT (runReaderT (runEitherT monadt') "reader") "state"
  case a of
    Left e -> print $ "left " ++ e
    Right r -> print $ "right " ++ r
  print s


lift' :: Monad m => m a -> StateT s m a
lift' m = StateT $ \s -> m >>= \a -> return (a, s)

get' :: Monad m => StateT s m s
get' = StateT $ \s -> return (s,s)

modify' :: Monad m => (s -> s) -> StateT s m ()
modify' f = StateT $ \s -> return ((), f s)

a `bind` f = StateT $ \s -> runStateT a s >>= \(a', s') -> runStateT (f a') s'

monadt :: EitherT e (ReaderT String (StateT s IO)) String
monadt = EitherT $ ReaderT $ \r -> StateT $ \s -> return (Right (r ++ "IO"), s)

monadt' :: EitherT String (ReaderT String (StateT String IO)) String
monadt' = do 
  -- EitherT $ do
  -- ReaderT $ \r -> do
  -- StateT $ \s -> do
  liftIO $ print "aaaaaaaa"
  s <- lift get
  rr <- lift ask
  left $ (rr ++ s ++ "IO")
  -- return (Right (r ++ s ++ "IO"), s)

-- statet :: StateT s IO a
-- statet = StateT $ \s -> return (1, s)
--
-- readert :: ReaderT r IO a
-- readert = ReaderT $ \r -> return (
