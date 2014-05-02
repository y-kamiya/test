import Network.HTTP.Conduit
import Data.Conduit
import Data.Conduit.Binary (sinkFile)
import System.Environment
import Control.Monad.IO.Class (liftIO)
import qualified Data.ByteString.Lazy as L
import qualified Data.ByteString.Lazy.Char8 as C8

main :: IO ()
main = getArgs >>= printResponseHeader 

printResponseHeader :: [String] -> IO ()
printResponseHeader urls = do
    case urls of
        [urlString] -> 
            case parseUrl urlString of
                Nothing -> putStrLn "invalid url"
                Just req -> withManager $ \manager -> do
                    let reqHead = req { method = L.toStrict $ C8.pack "HEAD" }
                    res <- http req manager
                    liftIO $ do
                        print $ responseStatus res
                        mapM_ print $ responseHeaders res
        _ -> putStrLn "Sorry, please provide example one URL"

useSimpleHttp :: IO ()
useSimpleHttp = do
        simpleHttp "http://www.yesodweb.com/book/http-conduit" >>= L.writeFile "foo.txt"
        
effiecientHttp :: IO ()
effiecientHttp = do
        runResourceT $ do
            manager <- liftIO $ newManager conduitManagerSettings
            req <- liftIO $ parseUrl "http://www.yesodweb.com/book/http-conduit"
            res <- http req manager
            print $ responseBody res 
