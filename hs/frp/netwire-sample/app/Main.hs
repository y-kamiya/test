{-# LANGUAGE Arrows #-}
module Main where

-- import Control.Wire
-- import FRP.Netwire
import Prelude hiding ((.))

import qualified Graphics.Rendering.OpenGL as GL
import qualified Graphics.UI.GLFW as GLFW
import Data.IORef
import Control.Monad
import Control.Concurrent

main :: IO ()
main = do
  withWindow 640 480 "netwire-sample" $ \win -> do
    threadDelay 10000000
    -- draw win

draw :: GLFW.Window -> IO ()
draw win = do
  GL.clear [GL.ColorBuffer, GL.DepthBuffer]
  renderPoint (1,1)
  quit <- GLFW.windowShouldClose win
  unless quit $ draw win

renderPoint :: (Double, Double) -> IO () 
renderPoint (x, y) = GL.vertex $ GL.Vertex2 (realToFrac x :: GL.GLfloat) (realToFrac y :: GL.GLfloat)

-- copy from GLFW-b demo
withWindow :: Int -> Int -> String -> (GLFW.Window -> IO ()) -> IO ()
withWindow width height title f = do
    GLFW.setErrorCallback $ Just simpleErrorCallback
    r <- GLFW.init
    when r $ do
        m <- GLFW.createWindow width height title Nothing Nothing
        case m of
          (Just win) -> do
              GLFW.makeContextCurrent m
              f win
              GLFW.setErrorCallback $ Just simpleErrorCallback
              GLFW.destroyWindow win
          Nothing -> return ()
        GLFW.terminate
  where
    simpleErrorCallback e s =
        putStrLn $ unwords [show e, show s]
