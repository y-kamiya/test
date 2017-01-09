{-# LANGUAGE Arrows #-}
module Main where

-- import Control.Wire
-- import FRP.Netwire

import Graphics.UI.GLUT hiding (Level,Vector3(..),normalize)
import qualified Graphics.UI.GLUT as G(Vector3(..))

import Data.IORef
import Control.Monad
import Control.Concurrent

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

draw :: Pos -> IO ()
draw pos = do
    clear [ ColorBuffer, DepthBuffer ]
    loadIdentity
    renderPlayer $ vector3 2 (unsafeCoerce pos) (-30)
    flush
    where size2 :: R
          size2 = (fromInteger $ 6)/2
          green  = Color4 0.8 1.0 0.7 0.9 :: Color4 R
          greenG = Color4 0.8 1.0 0.7 1.0 :: Color4 R
          red    = Color4 1.0 0.7 0.8 1.0 :: Color4 R
          renderShapeAt s p = preservingMatrix $ do
            translate $ G.Vector3 (0.5 - size2 + vector3X p)
                                  (0.5 - size2 + vector3Y p)
                                  (0.5 - size2 + vector3Z p)
            renderObject Solid s
          renderObstacle = (color green >>) . (renderShapeAt $ Cube 1)
          renderPlayer   = (color red >>) . (renderShapeAt $ Sphere' 0.5 20 20)
          renderGoal     =
            (color greenG >>) . (renderShapeAt $ Sphere' 0.5 20 20)

main :: IO ()
main = do
    oldTime <- newIORef (0 :: Int)
    displayCallback $= return ()
    idleCallback $= Just idle
    oldTime' <- get elapsedTime
    writeIORef oldTime oldTime' 
    mainLoop

idle :: IO ()
idle = do
  print "aaaaaaaaaa"
