module Types where

import Graphics.UI.GLUT hiding (Level,normalize)
import Control.Wire

type Pos = (Double, Double)
type Vel = (Double, Double)
type R = GLdouble

type SF a b = Wire TimeState () Identity a b

data GameEvent = MoveUp 
               | MoveRight 
               | MoveDown 
               | MoveLeft 
               | Shot 
               | GameMenu
               | PopEnemy EnemyKind Pos Vel
               | NoInput
               deriving (Eq, Show)

type GameInput = [GameEvent] 

data EnemyKind = EnemySimple
               deriving (Eq, Show)

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

type ObjectSF = SF GameInput GameOutput


