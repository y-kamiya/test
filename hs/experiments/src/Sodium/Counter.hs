module Counter where

import FRP.Sodium
import Data.Functor
import Control.Concurrent
import Control.Monad

buildCounter :: Event Char -> Reactive (Behaviour Int)
buildCounter charEvent = accum 0 increases
  where
    increases = const (+1) <$> charEvent

printCounter :: Behaviour Int -> Event () -> Event (IO ())
printCounter counter clockEvent = counterPrintE `merge` clockPrintE
  where
    counterChangeE = updates counter
    counterPrintE = (putStrLn . show) <$> counterChangeE
    clockPrintE = snapshot clockPrintF clockEvent counter
    clockPrintF () i = putStrLn $ "Timer event: " ++ (show i)

clockThread :: Int -> (() -> Reactive ()) -> IO ThreadId
clockThread sleepS pushE = forkIO $ forever $ do
  threadDelay $ sleepS * 1000 * 1000
  sync $ pushE ()

gatherStdIn :: (Char -> Reactive ()) -> IO ()
gatherStdIn pushChar = forever $ getChar >>= (sync . pushChar)

counterMain :: IO ()
counterMain = do
  (clockE, pushClock) <- sync newEvent
  (inputE, pushInput) <- sync newEvent

  counter <- sync $ buildCounter inputE
  clockThread 2 pushClock
  sync $ listen (printCounter counter clockE) id
  gatherStdIn pushInput

