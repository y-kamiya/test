{-# LANGUAGE DeriveDataTypeable #-}

import System.Environment
import System.Console.CmdArgs

modeList = ["hoge", "fuga"]

data Modes = Sample {hello :: String} 
            | Hoge {
                   hoges :: String
              }
            | Fuga {
                   fugas :: String
              }
            deriving (Show, Data, Typeable)

detail = details . lines

sample :: Modes
sample = Sample{hello = def &= name "tid" &= help "World argument" &= opt "world"}

hoge :: Modes
hoge = Hoge {
    hoges = def &= explicit &= name "tid" &= help "aaa"
} &= name "hogehoge"
  &= details ["bbbbbbbbbbbb"]

fuga :: Modes
fuga = Fuga {
    fugas = def
}

samples = cmdArgsMode $ modes [sample, hoge, fuga] 
         &= summary "Sample v1"

main = do
    name <- getProgName
    args <- getArgs
    print name
    print args
    a <- cmdArgsRun samples
    print a
