import Data.ConfigFile
import Control.Monad
import Control.Monad.Except

main :: IO ()
main = do
  r <- runExceptT $ do
    cp <- join $ liftIO $ readfile emptyCP "./config"
    a <- get cp "DEFAULT" "a"
    return a
  print r
