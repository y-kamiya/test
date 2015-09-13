module Main where

import System.Environment
import Control.Concurrent
import Control.Monad
import FRP.Sodium

import Chat
import Counter

main :: IO ()
main = do
  args <- getArgs
  case head args of
    "simple" -> simple
    "chat" -> chat
    "normalChat" -> normalChat
    "behaviour" -> behaviour
    "counter" -> counterMain

behaviour :: IO ()
behaviour = do
  (b, push) <- sync $ newBehaviour (1::Int)
  a <- sync $ sample b
  print a
  sync $ push 2
  aa <- sync $ sample b
  print aa
  let e = updates b
  _ <- sync $ listen e $ \x -> print x
  sync $ push 3
  let ee = value b
  _ <- sync $ listen ee $ \x -> print x
  sync $ push 4
  sync $ push 5

simple :: IO ()
simple = do
  (event, push) <- sync newEvent
  unlisten <- sync $ listen event $ \_ -> print "tick"
  behaviour <- sync $ hold 0 event
  forkIO $ interval push
  threadDelay 2000000
  print =<< sync (sample behaviour)
  unlisten

interval :: (Int -> Reactive ()) -> IO ()
interval push = countUp 1
  where countUp i = do
          sync $ push i
          threadDelay 1000000
          countUp (i+1)
