{-# LANGUAGE TemplateHaskell #-}
{-# LANGUAGE QuasiQuotes #-}

module Main where

import Language.Haskell.TH
import Control.Monad

data Block = A | B deriving Show

main :: IO ()
main = print "aa"

sel :: Int -> Int -> ExpQ
sel count nth = do
  vars <- replicateM count $ newName "x"
  lamE [tupP $ map varP vars] (varE $ vars !! (nth-1))

deriveBlock :: Dec
deriveBlock = DataD [] (mkName "Block") [] [NormalC (mkName "A") [], NormalC (mkName "B") []] [''Show]

