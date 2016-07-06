{-# LANGUAGE NoImplicitPrelude #-}
module Main where

import           Prelude
import           JQuery
import           FFI
import qualified Fay.Text as T
import Data.Char (ord)
import Data.Function

alert :: String -> Fay ()
alert = ffi "alert(%1)"

select' :: String -> Fay JQuery
select' s = select $ T.pack s

charCodeOffset :: Int
charCodeOffset = 96

main :: Fay ()
main = do
  Main.load
  select' "#field table td" >>= onClick start
  select' "body" >>= keydown move
  return ()

load :: Fay ()
load = do
  input <- select' "#input" >>= getText 
  rowNum <- select' "#rowNum" >>= getVal 
  colNum <- select' "#colNum" >>= getVal >>= text2Int
  let innerTable =  "<table class=\"innerTable\"><tr><td></td><td></td></tr><tr><td></td><td></td></tr></table>"
      tuples = zip [0..] (T.unpack input)
      tdList = flip map tuples $ \(cellId, c) -> case c of
                                                 '.' -> buildTd cellId innerTable
                                                 otherwise -> buildTd cellId (show $ ord c - charCodeOffset)
      table = "<table><tr>" ++ (concat $ intercalate ["</tr><tr>"] (chunk colNum tdList)) ++ "</tr></table>"
  select' "#field" >>= append (T.pack table)
  return ()
  where
    buildTd :: Int -> String -> String
    buildTd i s = "<tr><td id=\"" ++ show i ++ "\">" ++ s ++ "</td>"

start :: Event -> Fay Bool
start e = undefined

move :: Event -> Fay ()
move e = undefined

handler e = do
  alert "hello"
  return False

chunk :: Int -> [String] -> [[String]]
chunk n [] = [[]]
chunk n ss = take n ss : chunk n (drop n ss)

text2Int :: T.Text -> Fay Int
text2Int = ffi "%1"
