{-# LANGUAGE Arrows #-}
import FRP.Yampa
import Control.Concurrent
import FRP.Yampa.Vector3
import FRP.Yampa.Utilities
import Unsafe.Coerce
import Data.IORef

import Graphics.UI.GLUT hiding (Level,Vector3(..),normalize)
import qualified Graphics.UI.GLUT as G(Vector3(..))

import Input


type Pos = (Double, Double)
type Vel = (Double, Double)
type R = GLdouble


{-
fallingBall :: Pos -> Vel -> SF () (Pos, Vel)
fallingBall y0 v0 = (constant (-9.81) >>> integral >>^ (+ v0)) >>> ((integral >>^ (+ y0)) &&& identity)

bouncingBall :: Pos -> Vel -> SF () (Pos, Vel)
bouncingBall y0 v0 = switch (bb y0 v0) (\(pos, vel) -> if abs vel <= 1 then constant (0, 0) else bouncingBall pos (-vel * 0.6))
  where bb y0 v0 = proc input -> do
                    (pos, vel) <- fallingBall y0 v0 -< input
                    event <- edge -< pos <= 0
                    returnA -< ((pos, vel), event `tag` (pos, vel))
    -- (fallingBall y0 v0) >>> (identity &&& (arr (\(pos, vel) -> pos <= 0) &&& \(pos, vel) -> edgeTag (pos, vel)))
-}

movingPlayer :: SF (Event GameInput) (Pos, Vel)
movingPlayer = arr makeVelocity >>> (position &&& velocity)
  where 
    position = first $ integral >>^ (+ 1)
    velocity = identity

    makeVelocity :: Event GameInput -> Vel
    makeVelocity (Event MoveUp) = (1,1)
    makeVelocity _ = (1,0)

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

draw :: SF (Pos, Vel) (IO ())
draw = arr render

render :: (Pos, Vel) -> IO ()
render (pos, _) = do
    clear [ ColorBuffer, DepthBuffer ]
    loadIdentity
    renderPlayer $ vector3 (fst pos) (unsafeCoerce (snd pos)) (-30)
    flush
    where size2 :: R
          size2 = 6 / 2
          green  = Color4 0.8 1.0 0.7 0.9 :: Color4 R
          greenG = Color4 0.8 1.0 0.7 1.0 :: Color4 R
          red    = Color4 1.0 0.7 0.8 1.0 :: Color4 R
          renderShapeAt s p = preservingMatrix $ do
            translate $ G.Vector3 (0.5 - size2 + vector3X p)
                                  (0.5 - size2 + vector3Y p)
                                  (0.5 - size2 + vector3Z p)
            renderObject Solid s
          renderObstacle = (color green >>) . renderShapeAt (Cube 1)
          renderPlayer   = (color red >>) . renderShapeAt (Sphere' 0.5 20 20)
          renderGoal     =
            (color greenG >>) . renderShapeAt (Sphere' 0.5 20 20)

-- mainSF = (bouncingBall 10.0 0.0) >>^ (\ (pos, vel)-> putStrLn ("pos: " ++ show pos ++ ", vel: " ++ show vel) >> draw pos)
-- mainSF = movingPlayer >>^ (\arg@(pos, vel) -> outputLog arg >> draw pos)
mainSF :: SF (Event Input) (IO ())
mainSF = parseInput >>> movingPlayer >>> draw

outputLog :: (Pos, Vel) -> IO ()
outputLog (pos, vel) = putStrLn ("pos: " ++ show pos ++ ", vel: " ++ show vel)

-- | Main, initializes Yampa and sets up reactimation loop
main :: IO ()
main = do
    oldTime <- newIORef (0 :: Int)
    rh <- reactInit (initGL >> return NoEvent)
                    (\_ _ b -> b >> return False) 
                    mainSF
    displayCallback $= return ()
    newInput <- newIORef NoEvent
    keyboardMouseCallback $= Just 
        (\k ks m _ -> writeIORef newInput (Event $ Keyboard k ks m))
    idleCallback $= Just (idle newInput oldTime rh)
    oldTime' <- get elapsedTime
    writeIORef oldTime oldTime' 
    mainLoop

-- | Reactimation iteration, supplying the input
idle :: IORef (Event Input) -> IORef Int -> ReactHandle (Event Input) (IO ()) -> IO ()
idle newInput oldTime rh = do
    newInput' <- get newInput
    newTime'  <- get elapsedTime
    oldTime'  <- get oldTime
    let dt = fromIntegral (newTime' - oldTime') / 1000
    react rh (dt, Just newInput')
    writeIORef oldTime newTime'
    return ()
