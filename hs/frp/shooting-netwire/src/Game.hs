{-# LANGUAGE Arrows #-}
module Game where

import Prelude hiding ((.))
import Control.Wire
import FRP.Netwire
import Data.Functor
import Data.List (find)
import Data.Maybe (isNothing)
import Graphics.UI.GLUT hiding (Level,normalize)

import Types
import Input

integrals :: (Fractional a) => (a, a) -> SF (a, a) (a, a)
integrals (x,y) = first (integral x) >>> second (integral y)

simpleEnemy :: Pos -> Vel -> ObjectSF
simpleEnemy (x0,y0) (vx0,vy0) = mkConst (Right vy0) >>> integral y0 >>^ (\y -> [GameObject KindEnemy (x0,y) (vx0,vy0)])

movingPlayer :: Pos -> ObjectSF
movingPlayer pos = proc input -> do
  vel' <- arr makeVelocity -< input
  pos' <- integrals pos -< vel'
  returnA -< createOutput pos' vel' input
  where 
    makeVelocity :: GameInput -> Vel
    makeVelocity (MoveUp:_)    = (0,10)
    makeVelocity (MoveRight:_) = (10,0)
    makeVelocity (MoveDown:_)  = (0,-10)
    makeVelocity (MoveLeft:_)  = (-10,0)
    makeVelocity (PopEnemy{}:rest) = makeVelocity rest
    makeVelocity _ = (0,0)

    createOutput :: Pos -> Vel -> GameInput -> GameOutput
    createOutput pos vel (Shot:_) = [GameObject KindPlayer pos vel, GameObject KindShot pos (0,10)]
    createOutput pos vel (_:rest) | not $ null rest = [GameObject KindPlayer pos vel]
    createOutput pos vel _ = [GameObject KindPlayer pos vel]

shot :: Pos -> Vel -> ObjectSF
shot p0 v0 = mkConst (Right v0) >>> (integrals p0 &&& mkId) >>^ uncurry (GameObject KindShot) >>> (:[])

updateGame ::  ObjectSF -> ObjectSF
updateGame sf = dkSwitch sf nextWire
  where
    nextWire :: SF (GameInput, GameOutput) (Event (ObjectSF -> ObjectSF))
    nextWire = proc (input, output) -> do
      event <- edge shouldSwitch -< (input, output)
      returnA -< updateSF <$> event

    shouldSwitch :: (GameInput,GameOutput) -> Bool
    shouldSwitch (is, os) =  isCollide || any isCreatedOrDeleted is
      where
        isCollide = foldl (\acc o -> acc || collide os o) False os
        isCreatedOrDeleted i = foldl (\acc o -> acc || judge (i,o)) False os

        judge (Shot, _) = True
        judge (PopEnemy _ _ _, _) = True
        judge (_, GameObject KindShot pos _) | isOut pos = True
        judge (_, GameObject KindEnemy pos _) | isOut pos = True
        judge _ = False

    updateSF :: (GameInput,GameOutput) -> ObjectSF -> ObjectSF
    updateSF (is, os) sf 
      | isNothing (find ((== KindPlayer) . objKind) os) = inhibit ()
      | otherwise = updateGame $ mconcat $ foldl (\acc o -> acc ++ createSFs o) [] $ concatMap addNewObjects is ++ updateByOut (updateByCollide os)
      where
        createSFs (GameObject KindEnemy pos vel) = [simpleEnemy pos vel]
        createSFs (GameObject KindPlayer pos _)  = [movingPlayer pos]
        createSFs (GameObject KindShot pos vel)  = [shot pos vel]

    addNewObjects :: GameEvent -> GameOutput
    addNewObjects (PopEnemy _ pos vel) = [GameObject KindEnemy pos vel]
    addNewObjects _ = []

    updateByOut :: GameOutput -> GameOutput
    updateByOut os = filter (not . outside) os
      where
        outside (GameObject KindEnemy pos _) | isOut pos = True
        outside (GameObject KindShot pos _) | isOut pos = True
        outside  _ = False

    isOut :: Pos -> Bool
    isOut (_,y) 
      | y < -20 || 20 < y = True
      | otherwise = False 

    updateByCollide :: GameOutput -> GameOutput
    updateByCollide os = filter (not . collide os) os

    collide :: GameOutput -> GameObject -> Bool
    collide os (GameObject KindPlayer pos _) = any (collideAt 1 pos . objPos) $ filter ((== KindEnemy) . objKind) os
    collide os (GameObject KindEnemy pos _) = any (collideAt 1 pos . objPos) $ filter ((== KindShot) . objKind) os
    collide os (GameObject KindShot pos _) = any (collideAt 1 pos . objPos) $ filter ((== KindEnemy) . objKind) os

    collideAt :: Double -> Pos -> Pos -> Bool
    collideAt r (x1,y1) (x2,y2) = d < r
      where d = sqrt $ ((x2-x1)^2) + ((y2-y1)^2)

mainSF :: SF (Event Input) GameOutput
mainSF = parseInput >>> systemInput >>> unless (notElem GameMenu) >>> shootingScene

shootingScene :: SF GameInput GameOutput
shootingScene = updateGame initialObjectSFs

initialObjectSFs :: ObjectSF
initialObjectSFs = mconcat [movingPlayer (0,0)]


