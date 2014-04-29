import Network.HTTP.Conduit
import System.Environment
import Control.Monad.IO.Class (liftIO)
import qualified Data.ByteString.Lazy as L

main :: IO ()
main = getArgs >>= printResponseHeader 

printResponseHeader :: [String] -> IO ()
printResponseHeader urls = do
    case urls of
        [urlString] -> 
            case parseUrl urlString of
                Nothing -> putStrLn "invalid url"
                Just req -> withManager $ \manager -> do
                    let reqHead = req { method = "HEAD" }
                    res <- http req manager
                    liftIO $ do
                        print $ responseStatus res
                        mapM_ print $ responseHeaders res
        _ -> putStrLn "Sorry, please provide example one URL"

