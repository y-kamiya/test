module Main where

import Control.Concurrent
import Control.Monad
import FRP.Sodium

main :: IO ()
main = do
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
