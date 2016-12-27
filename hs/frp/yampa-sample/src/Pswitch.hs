{-# LANGUAGE Arrows #-}
import FRP.Yampa
import Control.Concurrent
import FRP.Yampa.Vector3
import FRP.Yampa.Utilities
import Unsafe.Coerce
import Data.IORef

import Graphics.UI.GLUT hiding (Level,Vector3(..),normalize)
import qualified Graphics.UI.GLUT as G(Vector3(..))


type Pos = Double
type Vel = Double
type R = GLdouble


fallingBall :: Double -> Pos -> Vel -> SF () (Pos, Vel)
fallingBall a0 y0 v0 = (constant a0 >>> integral >>^ (+ v0)) >>> ((integral >>^ (+ y0)) &&& identity)

-- bouncingBall :: Pos -> Vel -> SF () (Pos, Vel)
-- bouncingBall y0 v0 = switch (bb y0 v0) (\(pos, vel) -> if abs vel <= 1 then constant (0, 0) else bouncingBall pos (-vel * 0.6))
--   where bb y0 v0 = proc input -> do
--                     (pos, vel) <- fallingBall y0 v0 -< input
--                     event <- edge -< pos <= 0
--                     returnA -< ((pos, vel), event `tag` (pos, vel))

balls :: [SF () (Pos, Vel)] -> SF () [(Pos, Vel)]
balls sfs = dpSwitchB sfs emitter $ \sflist tag -> balls [constant (0, 0), constant (0, 0)]
  where
    emitter :: SF ((), [(Pos, Vel)]) (Event ())
    emitter = proc (_, ((y1,_):(y2,_):_)) -> do
                e <- edge -< (y1 <= 0 || y2 <= 0)
                returnA -< e
                

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

draw :: [(Pos, Vel)] -> IO ()
draw ((p1,_):(p2,_):_) = do
    clear [ ColorBuffer, DepthBuffer ]
    loadIdentity
    renderPlayer $ vector3 2 (unsafeCoerce p1) (-30)
    renderPlayer $ vector3 10 (unsafeCoerce p2) (-30)
    flush
    where size2 :: R
          size2 = (fromInteger 6)/2
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

mainSF = balls  [fallingBall (-9.81) 10 0, fallingBall (-0.90) 10 0] >>^ draw

-- | Main, initializes Yampa and sets up reactimation loop
main :: IO ()
main = do
    oldTime <- newIORef (0 :: Int)
    rh <- reactInit initGL (\_ _ b -> b >> return False) 
                    mainSF
    displayCallback $= return ()
    idleCallback $= Just (idle  oldTime rh)
    oldTime' <- get elapsedTime
    writeIORef oldTime oldTime' 
    mainLoop

-- | Reactimation iteration, supplying the input
idle :: IORef Int -> ReactHandle () (IO ()) -> IO ()
idle oldTime rh = do
    newTime'  <- get elapsedTime
    oldTime'  <- get oldTime
    let dt = (fromIntegral $ newTime' - oldTime')/1000
    react rh (dt, Nothing)
    writeIORef oldTime newTime'
    return ()

