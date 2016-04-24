{-# LANGUAGE OverloadedStrings #-}
module Main where

import Network.Wai (responseLBS, Application)
import Network.HTTP.Types (status200)
import Network.Wai.Handler.Warp (run, Port)

main :: IO () 
main = do
  print $ "start server on port " ++ show port
  run port app

app :: Application
app req res = res $ responseLBS status200 [] "sample of wai"

port :: Port
port = 8012

