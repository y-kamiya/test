{-# LANGUAGE Arrows #-}
import Prelude hiding ((.))
import Control.Wire
import FRP.Netwire
import Control.Wire.Unsafe.Event
import Control.Concurrent
import Unsafe.Coerce
import Data.IORef

import Graphics.UI.GLUT hiding (Level,normalize)

import Input


type Pos = (Double, Double)
type Vel = (Double, Double)
type R = GLdouble

data ObjectKind = KindPlayer
                | KindShot
                deriving (Eq, Show)

data GameObject = GameObject { 
                    objKind :: ObjectKind
                  , objPos :: Pos
                  , objVel :: Vel
                  } deriving (Eq, Show)

type GameOutput = [GameObject]

type ObjectSF = Wire () () Identity (Event GameInput) GameObject

movingPlayer :: ObjectSF
movingPlayer = (arr makeVelocity >>^ (10 *^)) >>> (position &&& velocity) >>^ (\(pos, vel) -> GameObject KindPlayer pos vel)
  where 
    position = integral 0
    velocity = identity

    makeVelocity :: Event GameInput -> Vel
    makeVelocity (Event MoveUp)    = (0,1)
    makeVelocity (Event MoveRight) = (1,0)
    makeVelocity (Event MoveDown)  = (0,-1)
    makeVelocity (Event MoveLeft)  = (-1,0)
    makeVelocity _ = (0,0)

shot :: Pos -> Vel -> ObjectSF
shot p0 v0 = constant v0 >>> ((integral >>^ (^+^ p0)) &&& identity) >>^ uncurry (GameObject KindShot)


updateGame :: (HasTime t s) => [ObjectSF] -> Wire s () Identity (Event GameInput) GameOutput
updateGame objsfs = dpSwitchB objsfs 
                      (arr emitter)
                      (\sfs input -> updateGame $ updateObjectSFs sfs input)

updateObjectSFs :: [ObjectSF] -> GameInput -> [ObjectSF]
updateObjectSFs sfs Shot = shot (0,0) (0,0) : sfs
updateObjectSFs sfs _ = sfs

emitter :: (Event GameInput, GameOutput) -> Event GameInput
emitter (input, _) = input

mainSF :: (HasTime t s) => Wire s () Identity (Event Input) GameOutput
mainSF = parseInput >>> shootingScene

shootingScene :: (HasTime t s) => Wire s () Identity (Event GameInput) GameOutput
shootingScene = updateGame initialObjectSFs

initialObjectSFs :: [ObjectSF]
initialObjectSFs = [movingPlayer
                   ,fallingBall (0,0) (0,0)
                   ]

-- | Main, initializes Yampa and sets up reactimation loop
main :: IO ()
main = do
    initGL
    displayCallback $= return ()
    newInput <- newIORef NoEvent
    keyboardMouseCallback $= Just 
        (\k ks m _ -> writeIORef newInput (Event $ Keyboard k ks m))
    idleCallback $= Just (idle newInput clockSession_ mainSF)
    mainLoop

-- idle :: IORef (Event Input) -> Session IO (Timed NominalDiffTime ()) -> IO ()
idle newInput session wire = do
  (dt, session') <- stepSession session 
  print dt
  newInput' <- get newInput
  let (Right output, wire') = runIdentity $ stepWire wire dt (Right newInput')
  render output
  idleCallback $= Just (idle newInput session' wire')



-- graphics
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

render :: GameOutput -> IO ()
render output = do
    clear [ ColorBuffer, DepthBuffer ]
    loadIdentity
    print output
    mapM_ renderPlayer' output
    flush
    where size2 :: R
          size2 = 6 / 2
          green  = Color4 0.8 1.0 0.7 0.9 :: Color4 R
          greenG = Color4 0.8 1.0 0.7 1.0 :: Color4 R
          red    = Color4 1.0 0.7 0.8 1.0 :: Color4 R
          renderShapeAt s (Vector3 x y z) = preservingMatrix $ do
            translate $ Vector3 (0.5 - size2 + x)
                                (0.5 - size2 + y)
                                (0.5 - size2 + z)
            renderObject Solid s
          renderObstacle = (color green >>) . renderShapeAt (Cube 1)
          renderPlayer   = (color red >>) . renderShapeAt (Sphere' 0.5 20 20)
          renderGoal     =
            (color greenG >>) . renderShapeAt (Sphere' 0.5 20 20)

          renderPlayer' :: GameObject -> IO ()
          renderPlayer' GameObject {objPos = pos} = renderPlayer $ Vector3 (fst pos) (unsafeCoerce (snd pos)) (-30)

