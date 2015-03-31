{-# LANGUAGE GADTs #-}

import System.Environment
import Control.Monad.Free

import qualified CharIO as CharIO

-- data Stack a where
--     Push :: Int -> Stack ()
--     Pop  :: Stack Int
--     End  :: Stack ()
-- 
-- instance Functor Stack where
--     fmap f (Push x) = Push (f x)
--     fmap f Pop = Pop
--     fmap f End = End
-- 
-- instruction :: Free Stack ()
-- instruction = Push 


main :: IO ()
main = do
  (arg:_) <- getArgs    
  case arg of
    "chario" -> CharIO.defaultMain
