{-# LANGUAGE OverloadedStrings #-}
import Conduit
import Data.Conduit.Network
import Control.Concurrent.Async (concurrently)
import Control.Monad (void)


main :: IO ()
main = runTCPClient (clientSettings 30000 "localhost") $ \appData ->
  void $ concurrently
    (stdinC $$ appSink appData)
    (appSource appData $$ stdoutC)
  

