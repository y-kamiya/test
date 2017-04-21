{-# LANGUAGE Arrows #-}
module Input ( parseInput
             , systemInput
             , getInput
             , Input(..)
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

filterKeyDowns :: SF (Event Input) (Event Input)
filterKeyDowns = filterE ((==Down) . keyState)

parseInput :: SF (Event Input) (Event GameEvent)
parseInput = proc i -> do
    down <- filterKeyDowns          -< i
    gameEvent <- arr (fmap translateInput) -< down
    returnA -< gameEvent

translateInput :: Input -> GameEvent
translateInput (Keyboard {key = SpecialKey KeyUp   }) = MoveUp
translateInput (Keyboard {key = SpecialKey KeyRight}) = MoveRight
translateInput (Keyboard {key = SpecialKey KeyDown }) = MoveDown
translateInput (Keyboard {key = SpecialKey KeyLeft }) = MoveLeft
translateInput (Keyboard {key = Char 's' }) = Shot
translateInput (Keyboard {key = Char 'Q' }) = GameMenu
translateInput _  = NoInput

getInput :: Event GameEvent -> GameEvent
getInput (Event a) = a
getInput noEvent = NoInput

systemInput :: SF (Event GameEvent) GameInput
systemInput = proc input -> do
  popEnemyEvent <- periodic 1 -< PopEnemy EnemySimple (-10,20) (0, -10)
  returnA -< filter (/= NoInput) $ map getInput [input, popEnemyEvent]
  -- returnA -< mergeL input popEnemyEvent
