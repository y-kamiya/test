import System.Environment

main :: IO ()
main = do
    argv <- getArgs
    if  "--case" `elem` argv
      then print argv
      else print "default"
    withArgs (tail argv) $ do 
      a <- getArgs
      let i = readIO' $ head a
      i
      

readIO' :: String -> IO ()
readIO' s = read s

hoge :: IO ()
hoge = print "HOGE"
      
