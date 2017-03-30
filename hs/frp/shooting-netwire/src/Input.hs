{-# LANGUAGE Arrows #-}
module Input ( parseInput
             , getInput
             , Input(..)
             , GameInput(..)
             ) where

import Prelude hiding ((.))
import Control.Wire
import Control.Wire.Unsafe.Event
import Graphics.UI.GLUT

import Types

data Input = Keyboard { key       :: Key,
                        keyState  :: KeyState,
                        modifiers :: Modifiers }
                        deriving (Eq, Show)

filterKeyDowns :: (HasTime t s) => Wire s () Identity (Event Input) (Event Input)
filterKeyDowns = filterE ((==Down) . keyState)

parseInput :: (HasTime t s) => Wire s () Identity (Event Input) (Event GameInput)
parseInput = proc i -> do
    down <- filterKeyDowns          -< i
    gameEvent <- arr (fmap translateInput) -< down
    returnA -< gameEvent

translateInput :: Input -> GameInput
translateInput (Keyboard {key = SpecialKey KeyUp   }) = MoveUp
translateInput (Keyboard {key = SpecialKey KeyRight}) = MoveRight
translateInput (Keyboard {key = SpecialKey KeyDown }) = MoveDown
translateInput (Keyboard {key = SpecialKey KeyLeft }) = MoveLeft
translateInput (Keyboard {key = Char 's' }) = Shot
translateInput (Keyboard {key = Char 'Q' }) = GameMenu
translateInput (Keyboard {key = Char 'p' }) = PopEnemy
translateInput _  = NoInput

getInput :: Event GameInput -> GameInput
getInput (Event a) = a
getInput noEvent = NoInput
