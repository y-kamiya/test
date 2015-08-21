{-# LANGUAGE RecordWildCards #-}

module Chat where

import Network
import System.IO
import Data.Monoid
import qualified Data.Map as M
import GHC.Conc.Sync
import Control.Concurrent
import Control.Monad
import FRP.Sodium

data ChatEvent = Join String | Message String String

chat :: IO ()
chat = do
  let port = 8888
  (event, push) <- sync newEvent
  sock <- listenOn $ PortNumber port
  print $ "start listening port " <> show port
  forever $ do
    (handle, host, port) <- accept sock
    let name = host <> show port
    unlisten <- sync $ listen event (handler handle)
    sync $ push $ Join name
    forkFinally (talk name handle push) (\_ -> hClose handle)
  where
    talk :: String -> Handle -> (ChatEvent -> Reactive ()) -> IO ()
    talk name h push = forever $ do
      msg <- hGetLine h
      print $ "get msg from handle " <> msg
      sync $ push $ Message name msg

    handler :: Handle -> ChatEvent -> IO ()
    handler h (Join name) = hPutStrLn h $ "Join " <> name
    handler h (Message name msg)
      | msg == "exit\r" = do
          print "handle is closed"
          hClose h
      | otherwise = hPutStrLn h $ "from " <> name <> ": " <> msg


data Server = Server { clients :: TVar (M.Map String Handle) }

normalChat :: IO ()
normalChat = do
  let port = 8889
  sock <- listenOn $ PortNumber port
  print $ "start listening port " <> show port
  tvar <- newTVarIO M.empty
  let server = Server tvar
  forever $ do
    (handle, host, port) <- accept sock
    let name = host <> show port
    print $ "connected from " <> name
    atomically $ addClient server handle name
    forkFinally (talk server handle name) (\_ -> hClose handle)
  where
    talk :: Server -> Handle -> String -> IO ()
    talk server@Server{..} h name = do
      msg <- hGetLine h
      clientMap <- atomically $ readTVar clients
      void $ flip M.traverseWithKey clientMap $ \_ handle ->
        hPutStrLn handle $ name <> ": " <> msg
      talk server h name

    addClient :: Server -> Handle -> String -> STM ()
    addClient Server{..} h name = do
      clientMap <- readTVar clients
      let newClientMap = M.insert name h clientMap
      writeTVar clients newClientMap

