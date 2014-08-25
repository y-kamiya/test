{-# LANGUAGE OverloadedStrings #-}
import Conduit
import Data.Conduit.Network
import Data.Word8 (toUpper)
import Data.ByteString (pack)

serverApp :: AppData -> IO ()
serverApp appData = appSource appData 
  $$ omapCE toUpper 
  =$= concatMapCE (\w -> pack [w, w])
  =$ appSink appData

main :: IO ()
main = runTCPServer (serverSettings 30000 "*") serverApp
  

