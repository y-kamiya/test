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
    GL.clear [GL.ColorBuffer, GL.DepthBuffer]
    renderPoint (1,1)
    GLFW.swapBuffers win
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
    GLFW.windowHint $ GLFW.WindowHint'ContextVersionMajor 3
    GLFW.windowHint $ GLFW.WindowHint'ContextVersionMinor 3
    GLFW.windowHint $ GLFW.WindowHint'OpenGLForwardCompat True
    GLFW.windowHint $ GLFW.WindowHint'OpenGLProfile GLFW.OpenGLProfile'Core
    m <- GLFW.createWindow width height title Nothing Nothing
    case m of
      (Just win) -> do
          GLFW.makeContextCurrent m
          major <- GLFW.getWindowContextVersionMajor win
          minor <- GLFW.getWindowContextVersionMinor win
          compat <- GLFW.getWindowOpenGLForwardCompat win
          profile <- GLFW.getWindowOpenGLProfile win
          print major
          print minor
          print compat
          print profile
          print "aaaaaaaaaaaa"
          f win
          GLFW.setErrorCallback $ Just simpleErrorCallback
          GLFW.destroyWindow win
      Nothing -> print "Failed to open GLFW window"
    GLFW.terminate
  where
    simpleErrorCallback e s =
        putStrLn $ unwords [show e, show s]
