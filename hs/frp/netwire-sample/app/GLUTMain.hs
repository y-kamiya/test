{-# LANGUAGE Arrows #-}
module Main where

import Prelude hiding ((.))
import Control.Wire
import FRP.Netwire
import Graphics.UI.GLUT

import Data.IORef
import Control.Monad
import Control.Concurrent

type R = GLdouble

initGL :: IO ()
initGL = do
    getArgsAndInitialize
    createWindow "Bounce"
    initialDisplayMode $= [ WithDepthBuffer, DoubleBuffered ]
    depthFunc          $= Just Less
    clearColor         $= Color4 0 0 0 0
    light (Light 0)    $= Enabled
    lighting           $= Enabled
    lightModelAmbient  $= Color4 0.5 0.5 0.5 1
    diffuse (Light 0)  $= Color4 1 1 1 1
    blend              $= Enabled
    blendFunc          $= (SrcAlpha, OneMinusSrcAlpha)
    colorMaterial      $= Just (FrontAndBack, AmbientAndDiffuse)
    reshapeCallback    $= Just resizeScene
    return ()

resizeScene :: Size -> IO ()
resizeScene (Size w 0) = resizeScene (Size w 1) -- prevent divide by zero
resizeScene s@(Size width height) = do
  -- putStrLn "resizeScene"
  viewport   $= (Position 0 0, s)
  matrixMode $= Projection
  loadIdentity
  perspective 45 (w2/h2) 1 1000
  matrixMode $= Modelview 0
 where
   w2 = half width
   h2 = half height
   half z = realToFrac z / 2

draw :: IORef Int -> IO ()
draw oldTime = do
    clear [ ColorBuffer, DepthBuffer ]
    loadIdentity
    time <- get oldTime
    renderString Fixed8By13 $ show time
    renderPlayer $ Vector3 10 10 (-30)
    flush
    where size2 :: R
          size2 = (fromInteger $ 6)/2
          green  = Color4 0.8 1.0 0.7 0.9 :: Color4 R
          greenG = Color4 0.8 1.0 0.7 1.0 :: Color4 R
          red    = Color4 1.0 0.7 0.8 1.0 :: Color4 R
          renderShapeAt s (Vector3 x y z) = preservingMatrix $ do
            translate $ Vector3 (0.5 - size2 + x)
                                (0.5 - size2 + y)
                                (0.5 - size2 + z)
            renderObject Solid s
          renderObstacle = (color green >>) . (renderShapeAt $ Cube 1)
          renderPlayer   = (color red >>) . (renderShapeAt $ Sphere' 0.5 20 20)
          renderGoal     = (color greenG >>) . (renderShapeAt $ Sphere' 0.5 20 20)

main :: IO ()
main = do
    initGL
    oldTime <- newIORef (0 :: Int)
    time <- get oldTime
    displayCallback $= return ()
    idleCallback $= Just (idle clockSession)
    oldTime' <- get elapsedTime
    writeIORef oldTime oldTime' 
    mainLoop

idle :: Session IO s -> IO ()
idle session = do
  (s, session') <- stepSession session
  -- print s
  (e', wire') <- stepWire wire s $ Right ()
  print e'
  idle session'

wire :: Wire s () IO () Double
wire = integral 0 . pure 9.8
