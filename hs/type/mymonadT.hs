module MymonadT where

import Control.Monad
import Control.Monad.Trans

newtype MaybeT m a = MaybeT { runMaybeT :: m (Maybe a) } 

instance Monad m => Monad (MaybeT m) where
    return x = MaybeT $ return (Just x)
    m >>= k  = MaybeT $ do
                a <- runMaybeT m
                case a of
                    Nothing -> return Nothing
                    Just x  -> runMaybeT (k x)
    fail _   = MaybeT $ return Nothing

instance Monad m => Functor (MaybeT m) where
    fmap f x = MaybeT $ do
                a <- runMaybeT x
                case a of
                    Nothing -> return Nothing
                    Just v  -> return $ Just (f v)
                            
instance MonadTrans MaybeT where
    lift m = MaybeT $ m >>= (\x -> return (Just x))
    



getWord :: MaybeT IO String
getWord = do
    lift (putStr "input> ")
    a <- lift getLine
    when (a == "") (fail "")
    return a


test01 :: MaybeT IO String
test01 = do
    a <- getWord
    b <- getWord
    return (a ++ b)

test01' :: IO ()
test01' = do 
    a <- runMaybeT test01
    case a of
        Nothing -> return ()
        Just s  -> putStrLn s >> test01'




