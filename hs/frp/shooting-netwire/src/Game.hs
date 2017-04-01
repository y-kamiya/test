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

integrals :: (HasTime t s, Fractional a) => (a, a) -> Wire s () Identity (a, a) (a, a)
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
    makeVelocity MoveUp    = (0,10)
    makeVelocity MoveRight = (10,0)
    makeVelocity MoveDown  = (0,-10)
    makeVelocity MoveLeft  = (-10,0)
    makeVelocity _ = (0,0)

    createOutput :: Pos -> Vel -> GameInput -> GameOutput
    createOutput pos vel Shot = [GameObject KindPlayer pos vel, GameObject KindShot pos (0,10)]
    createOutput pos vel _ = [GameObject KindPlayer pos vel]

shot :: Pos -> Vel -> ObjectSF
shot p0 v0 = mkConst (Right v0) >>> (integrals p0 &&& mkId) >>^ uncurry (GameObject KindShot) >>> (:[])

updateGame ::  ObjectSF -> ObjectSF
updateGame sf = dkSwitch sf nextWire
  where
    nextWire :: Wire TimeState () Identity (GameInput, GameOutput) (Event (ObjectSF -> ObjectSF))
    nextWire = proc (input, output) -> do
      event <- edge shouldSwitch -< (input, output)
      returnA -< updateSF <$> event

    shouldSwitch :: (GameInput,GameOutput) -> Bool
    shouldSwitch (i, os) =  isCollide || isCreatedOrDeleted
      where
        isCollide = foldl (\acc o -> acc || collide os o) False os
        isCreatedOrDeleted = foldl (\acc o -> acc || judge (i,o)) False os

        judge (Shot, _) = True
        judge (PopEnemy _ _ _, _) = True
        judge (_, GameObject KindShot pos _) | isOut pos = True
        judge (_, GameObject KindEnemy pos _) | isOut pos = True
        judge _ = False

    updateSF :: (GameInput,GameOutput) -> ObjectSF -> ObjectSF
    updateSF (i, os) sf 
      | isNothing (find ((== KindPlayer) . objKind) os) = inhibit ()
      | otherwise = updateGame $ mconcat $ foldl (\acc o -> acc ++ createSFs (i, o) sf) [] $ addNewObjects i ++ (updateByOut $ updateByCollide os)
      where
        createSFs (_, GameObject KindEnemy pos vel) _ = [simpleEnemy pos vel]
        createSFs (_, GameObject KindPlayer pos _) _  = [movingPlayer pos]
        createSFs (_, GameObject KindShot pos vel) _  = [shot pos vel]

    addNewObjects :: GameInput -> GameOutput
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

mainSF :: Wire TimeState () Identity (Event Input) GameOutput
mainSF = parseInput >>> systemInput >>> arr getInput >>> unless (==GameMenu) >>> shootingScene

systemInput :: Wire TimeState () Identity (Event GameInput) (Event GameInput)
systemInput = proc input -> do
  popEnemyEvent <- periodic 1 -< PopEnemy EnemySimple (-10,20) (0, -10)
  returnA -< mergeL input popEnemyEvent

shootingScene :: Wire TimeState () Identity GameInput GameOutput
shootingScene = updateGame initialObjectSFs

initialObjectSFs :: ObjectSF
initialObjectSFs = mconcat [movingPlayer (0,0)]


