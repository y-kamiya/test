{-# LANGUAGE Arrows #-}
module Main where

import Prelude hiding ((.))
import Control.Wire
import FRP.Netwire
import Graphics.UI.GLUT

import Data.IORef
import Control.Monad
import Control.Concurrent

type Pos = Double
type Vel = Double
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

draw :: (Pos, Vel) -> IO ()
draw (pos, vel) = do
    clear [ ColorBuffer, DepthBuffer ]
    loadIdentity
    renderPlayer $ Vector3 10 pos (-30)
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
    displayCallback $= return ()
    idleCallback $= Just (idle clockSession_ $ bouncingBall 10 0)
    mainLoop

-- idle :: Session IO (Timed NominalDiffTime ()) -> IO ()
idle session wire = do
  (dt, session') <- stepSession session 
  print dt
  let (Right o, wire') = runIdentity $ stepWire wire dt (Right ())
  print o
  draw o
  idleCallback $= Just (idle session' wire')
  -- testWire clockSession_ (fallingBall 0 0)

fallingBall :: (HasTime t s) => Pos -> Vel -> Wire s () Identity a (Pos, Vel)
fallingBall y0 v0 = time >>> integral v0 . pure (-9.81) >>> (integral y0 &&& WId)

bouncingBall :: (HasTime t s) => Pos -> Vel -> Wire s () Identity a (Pos, Vel)
bouncingBall y0 v0 = dSwitch (bb y0 v0)
  where bb y0 v0 = proc input -> do
                    (pos, vel) <- fallingBall y0 v0 -< input
                    event <- edge (<= 0) -< pos
                    returnA -< ((pos, vel), const (bouncingBall (-pos) $ -vel * 0.6) <$> event)

