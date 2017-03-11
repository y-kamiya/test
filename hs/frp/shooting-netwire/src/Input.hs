{-# LANGUAGE Arrows #-}
module Input ( parseInput
             , Input(..)
             , GameInput(..)
             ) where

import Prelude hiding ((.))
import Control.Wire
import Control.Wire.Unsafe.Event
import Graphics.UI.GLUT

data GameInput = MoveUp 
               | MoveRight 
               | MoveDown 
               | MoveLeft 
               | Shot 
               | GameMenu
               | PopEnemy
               | NoInput
               deriving (Eq, Show)

data Input = Keyboard { key       :: Key,
                        keyState  :: KeyState,
                        modifiers :: Modifiers }
                        deriving (Eq, Show)

filterKeyDowns :: (HasTime t s) => Wire s () Identity (Event Input) (Event Input)
filterKeyDowns = filterE ((==Down) . keyState)

parseInput :: (HasTime t s) => Wire s () Identity (Event Input) GameInput
parseInput = proc i -> do
    down <- filterKeyDowns          -< i
    gameEvent <- arr translateInput -< down
    returnA -< gameEvent

translateInput :: Event Input -> GameInput
translateInput (Event (Keyboard {key = SpecialKey KeyUp   })) = MoveUp
translateInput (Event (Keyboard {key = SpecialKey KeyRight})) = MoveRight
translateInput (Event (Keyboard {key = SpecialKey KeyDown })) = MoveDown
translateInput (Event (Keyboard {key = SpecialKey KeyLeft })) = MoveLeft
translateInput (Event (Keyboard {key = Char 's' })) = Shot
translateInput (Event (Keyboard {key = Char 'Q' })) = GameMenu
translateInput (Event (Keyboard {key = Char 'p' })) = PopEnemy
translateInput _  = NoInput
