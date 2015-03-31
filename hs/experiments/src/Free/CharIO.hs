{-# LANGUAGE GADTs #-}

module CharIO where

import Data.Char
import Control.Monad.Free

ex0 :: GenericIO ()
ex0 = do
    mapM_ putCh "hello, input char you like: \n"
    ch <- getCh
    mapM_ putCh "input char is "
    mapM_ putCh $ show ch
    mapM_ putCh "\nfinish\n"

-- data CharIO a = GetCh (Char -> a) | PutCh Char a
data CharIO a where
    GetCh :: (Char -> a) -> CharIO a
    PutCh :: Char -> a -> CharIO a

instance Functor CharIO where
    fmap f (GetCh g) = GetCh (f . g)
    fmap f (PutCh c x) = PutCh c (f x)

getCh :: Free CharIO Char
getCh = Free $ GetCh $ \ch -> Pure ch

putCh :: Char -> Free CharIO ()
putCh ch = Free $ PutCh ch (Pure ())

type GenericIO = Free CharIO

runStdIO :: Free CharIO a -> IO a
runStdIO (Pure a) = return a
runStdIO (Free (GetCh f)) = getChar >>= \ch -> runStdIO (f ch)
runStdIO (Free (PutCh c fm)) = putChar c >> runStdIO fm

defaultMain :: IO ()
defaultMain = runStdIO ex0
