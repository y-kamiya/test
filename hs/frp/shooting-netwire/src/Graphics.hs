module Graphics where

import Unsafe.Coerce
import Graphics.UI.GLUT hiding (Level,normalize)

import Types

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


