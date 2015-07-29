{-# LANGUAGE TypeFamilies #-}

module Main where

import Prelude hiding (lookup)
import System.Environment
import qualified Data.IntMap as MI

class GMapKey k where
  data GMap k :: * -> *
  empty       :: GMap k v
  lookup      :: k -> GMap k v -> Maybe v
  insert      :: k -> v -> GMap k v -> GMap k v

instance GMapKey Int where
  data GMap Int v      = GMapInt (MI.IntMap v)
  empty                = GMapInt MI.empty
  lookup k (GMapInt m) = MI.lookup k m
  insert k v (GMapInt m) = GMapInt $ MI.insert k v m

instance GMapKey Char where
  data GMap Char v        = GMapChar (MI.IntMap v)
  empty                   = GMapChar MI.empty
  lookup k (GMapChar m)   = MI.lookup (fromEnum k) m
  insert k v (GMapChar m) = GMapChar $ MI.insert (fromEnum k) v m

mapInt :: GMap Int String
mapInt = insert 3 "key is 3" $
         insert 2 "key is 2" $
         insert 1 "key is 1" $
         empty

mapChar :: GMap Char String
mapChar = insert 'c' "key is c" $
          insert 'b' "key is b" $
          insert 'a' "key is a" $
          empty

main :: IO ()
main = do
  (arg:_) <- getArgs
  case arg of
    "int" -> print $ lookup 1 mapInt
    "char" -> print $ lookup 'a' mapChar
