{-# LANGUAGE Arrows #-}
module Main where

import Control.Category
import Control.Arrow
import Prelude hiding (id, (.))

newtype SimpleFunc a b = SimpleFunc { runF :: a -> b }

instance Arrow SimpleFunc where
  arr f = SimpleFunc f
  first (SimpleFunc f) = SimpleFunc (mapFst f)
    where mapFst g (a,b) = (g a, b)
  second (SimpleFunc f) = SimpleFunc (mapSnd f)
    where mapSnd g (a,b) = (a, g b)

instance Category SimpleFunc where
  (SimpleFunc g) . (SimpleFunc f) = SimpleFunc (g . f)
  id = arr id

main :: IO ()
main = do
  print $ runF f 8
  print $ runF g 8
  print $ runF h 8
  -- arrow notation of liftA2
  let h' = proc x -> do
             fx <- f -< x
             gx <- g -< x
             returnA -< (fx + gx)
  print $ runF h' 8

f :: SimpleFunc Int Int
f = arr (`div` 2)

g :: SimpleFunc Int Int
g = arr (\x -> x*3 + 1)

h :: SimpleFunc Int Int
h = liftA2 (+) f g

liftA2 :: (Arrow a) => (b -> c -> d) -> a e b -> a e c -> a e d
liftA2 op f g = arr (\x -> (x,x)) >>> first f >>> second g >>> (arr . uncurry) op
