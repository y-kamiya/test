{-# LANGUAGE Arrows #-}
import Prelude hiding ((.))
import Control.Wire
import FRP.Netwire
import Control.Wire.Unsafe.Event
import Control.Concurrent
import Unsafe.Coerce
import Data.IORef
import Data.Functor

import Graphics.UI.GLUT hiding (Level,normalize)

import Input


type Pos = (Double, Double)
type Vel = (Double, Double)
type R = GLdouble

data ObjectKind = KindPlayer
                | KindShot
                | KindEnemy
                deriving (Eq, Show)

data GameObject = GameObject { 
                    objKind :: ObjectKind
                  , objPos :: Pos
                  , objVel :: Vel
                  } deriving (Eq, Show)

type GameOutput = [GameObject]

type TimeState = Timed NominalDiffTime ()
type ObjectSF = Wire TimeState () Identity GameInput GameOutput

integrals :: (HasTime t s, Fractional a) => (a, a) -> Wire s () Identity (a, a) (a, a)
integrals (x,y) = first (integral x) >>> second (integral y)

fallingBall :: Pos -> Vel -> ObjectSF
fallingBall (x0,y0) (vx0,vy0) = (mkConst (Right (-9.81)) >>> integral vy0) 
                            >>> ((integral y0) &&& mkId) 
                            >>^ (\(y, v) -> [GameObject KindEnemy (x0,y) (vx0,v)])

bouncingBall :: Pos -> Vel -> ObjectSF
bouncingBall pos@(_,y0) vel@(_,v0) = dSwitch bb
  where bb = proc input -> do
              (obj@(GameObject _ (x,y) (vx,vy)):_) <- fallingBall pos vel -< input
              event <- edge (<= 0) -< y
              returnA -< ([obj], event $> bouncingBall (x,-y) (vx, -0.6 * vy))

movingPlayer :: ObjectSF
movingPlayer = (arr makeVelocity) >>> (integrals (0,0) &&& mkId) >>^ (\(pos, vel) -> [GameObject KindPlayer pos vel])
  where 
    makeVelocity :: GameInput -> Vel
    makeVelocity MoveUp    = (0,10)
    makeVelocity MoveRight = (10,0)
    makeVelocity MoveDown  = (0,-10)
    makeVelocity MoveLeft  = (-10,0)
    makeVelocity _ = (0,0)

shot :: Pos -> Vel -> ObjectSF
shot p0 v0 = mkConst (Right v0) >>> ((integrals p0) &&& mkId) >>^ uncurry (GameObject KindShot) >>> (\o -> [o])

updateGame ::  [ObjectSF] -> [ObjectSF]
updateGame objsfs = map updateSF objsfs
  where
    updateSF :: ObjectSF -> ObjectSF 
    updateSF sf = dkSwitch sf nextWire

    nextWire :: Wire TimeState () Identity (GameInput, GameOutput) (Event (ObjectSF -> ObjectSF))
    nextWire = proc (input, output) -> do
      event <- edge isShot -< (input, head output)
      returnA -< func <$> event

    func :: (GameInput,GameObject) -> ObjectSF -> ObjectSF
    func (input, (GameObject _ pos _)) sf = updateSF $ mconcat [sf, shot pos (0,10)]

    isShot :: (GameInput,GameObject) -> Bool
    isShot (Shot, GameObject KindPlayer _ _) = True
    isShot _ = False

mainSF :: Wire TimeState () Identity (Event Input) GameOutput
mainSF = parseInput >>> shootingScene

shootingScene :: Wire TimeState () Identity GameInput GameOutput
shootingScene = mconcat $ updateGame initialObjectSFs

initialObjectSFs :: [ObjectSF]
initialObjectSFs = [movingPlayer
                   ,bouncingBall (10,10) (0,0)
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
  -- print dt
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

          renderEnemy' :: GameObject -> IO ()
          renderEnemy' GameObject {objPos = pos} = renderObstacle $ Vector3 (fst pos) (unsafeCoerce (snd pos)) (-30)

          renderObejcts obj@(GameObject {objKind = KindPlayer}) = renderPlayer' obj
          renderObejcts obj@(GameObject {objKind = KindEnemy}) = renderEnemy' obj

