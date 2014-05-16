import System.IO
import Data.Conduit
import qualified Data.Conduit.List as CL
import Control.Monad.IO.Class
import Control.Monad.Trans.Resource

source' :: Source IO Int 
source' = CL.sourceList [1..10]

sink' :: Sink String IO ()
sink' = CL.mapM_ putStrLn

toString :: Conduit Int IO String
toString = CL.map show

multiple2 :: Conduit Int IO Int
multiple2 = CL.map (*2)

main :: IO ()
main = do
    source' $$ multiple2 =$= toString =$ sink'
    testFlow
    mySourceList [1..4] $$ leftoverTest =$ awaitTest'



yieldTest :: Source IO Int
yieldTest = do
    yield 1
    yield 2
    yield 3
    yield 4
    
awaitTest :: Sink String IO ()
awaitTest = do
    mstr <- await
    case mstr of
      Nothing -> return ()
      Just str -> do
        liftIO $ putStrLn str
        awaitTest
        

leftoverTest :: Conduit Int IO String
leftoverTest = do
    mi1 <- await
    mi2 <- await
    case (mi1, mi2) of
      (Just i1, Just i2) -> do
        yield $ show (i1,i2)
        leftover i2
        leftoverTest
      _ -> return ()  
      

testFlow = yieldTest $$ leftoverTest =$ awaitTest


mySourceList :: Monad m => [a] -> Source m a
mySourceList list = mapM_ yield list

awaitTest' :: Sink String IO ()
awaitTest' = myAwaitForever $ liftIO .putStrLn

myAwaitForever :: Monad m => (a -> Conduit a m b) -> Conduit a m b
myAwaitForever f = do
    mi <- await
    case mi of
      Nothing -> return ()
      Just i -> f i >> myAwaitForever f
          
myAwaitForever' :: Monad m => (a -> Conduit a m b) -> Conduit a m b
myAwaitForever' f = await >>= maybe (return ()) (\x -> f x >> myAwaitForever' f)
              

triple :: Monad m => Conduit i m i
triple = do
    ma <- await 
    case ma of
      Nothing -> return ()
      Just a -> do
        CL.sourceList [a,a,a]
        triple
        
triple' :: Monad m => Conduit i m i
triple' = awaitForever $ CL.sourceList . replicate 3 

useTriple = CL.sourceList [1..4] $$ triple' =$ CL.mapM_ print

multiplyByFirst :: Monad m => Conduit Int m Int
multiplyByFirst = do
    mi <- await
    case mi of
      Nothing -> return ()
      Just i -> CL.map (*i)
    
useMuliplyByFirst = CL.sourceList [2..4] $$ multiplyByFirst =$ CL.mapM_ print


-- check order of processing echo function
source :: Source IO Int
source = do
    liftIO $ putStrLn "source: yielding 1"
    yield 1
    liftIO $ putStrLn "source: yielding 2"
    yield 2
    liftIO $ putStrLn "source: yielding 3"
    yield 3
    
conduit = do
    liftIO $ putStrLn "conduit calling await"
    mx <- await
    case mx of
        Nothing -> liftIO $ putStrLn "Nothing left, exiting"
        Just x -> do
            liftIO $ putStrLn $ "conduit yielding " ++ show x
            yield x
            conduit
            
sink 0 = liftIO $ putStrLn "sink is finished, terminating"
sink i = do
    liftIO $ putStrLn $ "sink: still waiting for " ++ show i
    mx <- await
    case mx of
        Nothing -> liftIO $ putStrLn "sink: Nothing from upstream, exiting"
        Just x -> do
            liftIO $ putStrLn $ "sink received: " ++ show x
            sink (i - 1)
            
main' = source $$ conduit =$ sink 4




-- process something when terminated 
source2 = loop 1
  where
    loop i = do
      yieldOr i $ putStrLn $ "Teminated when yielding: " ++ show i
      loop $ i+1

main2 = source2 $$ CL.isolate 7 =$ CL.mapM_ print


-- addCleanup sample
source3 = do
    handle <- liftIO $ openFile "test.txt" ReadMode
    addCleanup (const $ putStrLn "Closing handle" >> hClose handle) $ loop handle
  where
    loop handle = do
      eof <- liftIO $ hIsEOF handle  
      if eof
        then return ()
        else do
          c <- liftIO $ hGetChar handle
          yield c
          loop handle
          
main3 = source3 $$ CL.isolate 5 =$ CL.mapM_ print


-- modify to be exception safe
source4 :: Source (ResourceT IO) Char
source4 = 
    bracketP
      (openFile "test.txt" ReadMode)
      (\handle -> putStrLn "Closing handle" >> hClose handle)
      loop
  where
    loop handle = do
      eof <- liftIO $ hIsEOF handle  
      if eof
        then return ()
        else do
          c <- liftIO $ hGetChar handle
          yield c
          loop handle
          
exceptionalSink = do
    c <- await
    liftIO $ print c
    error "This throws an exception"
    
main4 = runResourceT $ source4 $$ exceptionalSink


-- Connect and resume
main5 = do
    (rsrc1, result1) <- CL.sourceList [1..10] $$+ CL.take 3
    (rsrc2, result2) <- rsrc1 $$++ CL.take 3
    result3 <- rsrc2 $$+- CL.consume
    print (result1,result2,result3)
    
