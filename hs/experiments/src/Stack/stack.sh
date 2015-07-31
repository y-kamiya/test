#!/usr/bin/env stack
-- stack runghc --package=shelly

{-# LANGUAGE ExtendedDefaultRules #-}
{-# LANGUAGE OverloadedStrings    #-}
{-# OPTIONS_GHC -fno-warn-type-defaults #-}
import           Control.Monad
import qualified Data.Text     as T
import           Shelly
default (T.Text, Int)

main :: IO ()
main = shelly $ do
    withTmpDir $ \temp -> do
        forM_ [1..10] $ \i -> do
            touchfile $ temp </> show i <.> "txt"
        inspect temp
        cmd "ls" "-alF" temp
