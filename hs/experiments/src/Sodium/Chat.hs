module Chat where

import Network
import System.IO
import Data.Monoid
import Control.Concurrent
import Control.Monad
import FRP.Sodium

data Chat = Join | Message String

chat :: IO ()
chat = do
  (event, push) <- sync newEvent
  sock <- listenOn $ PortNumber 8888
  forever $ do
    (handle, host, port) <- accept sock
    let name = host <> show port
    unlisten <- sync $ listen event (handler name handle)
    sync $ push Join
    forkFinally (talk handle push) (\_ -> hClose handle)

talk :: Handle -> (Chat -> Reactive ()) -> IO ()
talk h push = forever $ do
  msg <- hGetLine h
  print $ "get msg from handle " <> msg
  sync $ push $ Message msg

handler :: String -> Handle -> Chat -> IO ()
handler name h Join = hPutStrLn h $ "Join " <> name
handler name h (Message msg) 
  | msg == "exit\r" = do
      print "handle is closed"
      hClose h
  | otherwise = hPutStrLn h $ "from " <> name <> ": " <> msg

