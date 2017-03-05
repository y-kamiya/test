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

movingPlayer :: Pos -> ObjectSF
movingPlayer pos = (arr makeVelocity) >>> (integrals pos &&& mkId) >>^ (\(pos, vel) -> [GameObject KindPlayer pos vel])
  where 
    makeVelocity :: GameInput -> Vel
    makeVelocity MoveUp    = (0,10)
    makeVelocity MoveRight = (10,0)
    makeVelocity MoveDown  = (0,-10)
    makeVelocity MoveLeft  = (-10,0)
    makeVelocity _ = (0,0)

shot :: Pos -> Vel -> ObjectSF
shot p0 v0 = mkConst (Right v0) >>> (integrals p0 &&& mkId) >>^ uncurry (GameObject KindShot) >>> (:[])

updateGame ::  ObjectSF -> ObjectSF
updateGame sf = dkSwitch sf nextWire
  where
    nextWire :: Wire TimeState () Identity (GameInput, GameOutput) (Event (ObjectSF -> ObjectSF))
    nextWire = proc (input, output) -> do
      event <- edge shouldSwitch -< (input, output)
      returnA -< updateSF <$> event

    updateSF :: (GameInput,GameOutput) -> ObjectSF -> ObjectSF
    updateSF (i, os) sf = updateGame $ mconcat $ foldl (\acc o -> acc ++ createSFs (i, o) sf) [] $ updateByCollide os
      where
        createSFs (Shot, GameObject KindPlayer pos _) _ = [movingPlayer pos, shot pos (0,10)]
        createSFs (_   , GameObject KindPlayer pos _) _ = [movingPlayer pos]
        createSFs (_   , GameObject KindShot pos@(_,y) vel) _ 
          | 10 <= y = []
          | otherwise = [shot pos vel]
        createSFs (_   , GameObject KindEnemy pos vel) _ = [bouncingBall pos vel]

    shouldSwitch :: (GameInput,GameOutput) -> Bool
    shouldSwitch (i, os) = foldl (\acc o -> acc || judge (i,o)) False os
      where
        judge (Shot, GameObject KindPlayer _ _) = True
        judge (_, GameObject KindShot (_,y) _) | 10 <= y = True
        judge _ = False

    updateByCollide :: GameOutput -> GameOutput
    updateByCollide os = filter (notCollide os) os
      where
        notCollide :: GameOutput -> GameObject -> Bool
        notCollide os (GameObject KindPlayer pos _) = not $ any (collide 2 pos . objPos) $ filter ((== KindEnemy) . objKind) os
        notCollide _ _ = True

collide :: Double -> Pos -> Pos -> Bool
collide r (x1,y1) (x2,y2) = d < r
  where d = sqrt $ ((x2-x1)^2) + ((y2-y1)^2)

mainSF :: Wire TimeState () Identity (Event Input) GameOutput
mainSF = parseInput >>> unless (==GameMenu) >>> shootingScene

-- selectScene :: ObjectSF
-- selectScene = arr $ \input -> case 

shootingScene :: Wire TimeState () Identity GameInput GameOutput
shootingScene = updateGame initialObjectSFs

initialObjectSFs :: ObjectSF
initialObjectSFs = mconcat [movingPlayer (0,0) ,bouncingBall (10,10) (0,0)]

-- | Main, initializes Yampa and sets up reactimation loop
main :: IO ()
main = do
    window <- initGL
    displayCallback $= return ()
    newInput <- newIORef NoEvent
    keyboardMouseCallback $= Just 
        (\k ks m _ -> writeIORef newInput (Event $ Keyboard k ks m))
    idleCallback $= Just (idle window newInput clockSession_ mainSF)
    mainLoop

-- idle :: Window -> IORef (Event Input) -> Session IO TimeState -> Wire TimeState () Identity (Event Input) GameOutput -> IO ()
idle window newInput session wire = do
  (dt, session') <- stepSession session 
  -- print dt
  newInput' <- get newInput
  let eOutput = runIdentity $ stepWire wire dt (Right newInput')
  case eOutput of
    (Left _, _) -> do
      destroyWindow window
      idleCallback $= Nothing
    (Right output, wire') -> do
      render output
      idleCallback $= Just (idle window newInput session' wire')

-- graphics
initGL :: IO Window
initGL = do
    getArgsAndInitialize
    window <- createWindow "Bounce"
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
    return window

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
    mapM_ renderObjects output
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
          renderShot     = (color green >>) . renderShapeAt (Sphere' 0.5 5 5)
          renderGoal     =
            (color greenG >>) . renderShapeAt (Sphere' 0.5 20 20)

          renderPlayer' :: GameObject -> IO ()
          renderPlayer' GameObject {objPos = pos} = renderPlayer $ Vector3 (fst pos) (unsafeCoerce (snd pos)) (-30)

          renderEnemy' :: GameObject -> IO ()
          renderEnemy' GameObject {objPos = pos} = renderObstacle $ Vector3 (fst pos) (unsafeCoerce (snd pos)) (-30)

          renderShot' :: GameObject -> IO ()
          renderShot' GameObject {objPos = pos} = renderShot $ Vector3 (fst pos) (unsafeCoerce (snd pos)) (-30)

          renderObjects obj@(GameObject {objKind = KindPlayer}) = renderPlayer' obj
          renderObjects obj@(GameObject {objKind = KindEnemy}) = renderEnemy' obj
          renderObjects obj@(GameObject {objKind = KindShot}) = renderShot' obj

