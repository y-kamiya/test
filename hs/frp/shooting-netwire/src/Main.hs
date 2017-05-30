module Main where

import Control.Wire
import Data.IORef
import Control.Wire.Unsafe.Event
import Graphics.UI.GLUT hiding (Level,normalize)
import System.Random
import Control.Monad.Reader

import Types
import Input
import Game
import Graphics

main :: IO ()
main = do
    window <- initGL
    displayCallback $= return ()
    newInput <- newIORef NoEvent
    keyboardMouseCallback $= Just 
        (\k ks m _ -> writeIORef newInput (Event $ Keyboard k ks m))
    gen <- newStdGen
    idleCallback $= Just (idle window newInput (randomRs (-10, 10) gen) clockSession_ mainSF)
    mainLoop

idle :: Window -> IORef (Event Input) -> [Double] -> Session IO TimeState -> SF (Event Input) GameOutput -> IO ()
idle window newInput (_:list) session wire = do
  (dt, session') <- stepSession session 
  newInput' <- get newInput
  let eOutput = flip runReader list $ stepWire wire dt (Right newInput')
  case eOutput of
    (Left _, _) -> do
      idleCallback $= Just (idle window newInput list clockSession_ mainSF)
    (Right output, wire') -> do
      render output
      idleCallback $= Just (idle window newInput list session' wire')

