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
               deriving (Eq, Show)

data Input = Keyboard { key       :: Key,
                        keyState  :: KeyState,
                        modifiers :: Modifiers }
                        deriving (Eq, Show)

-- data ParsedInput = ParsedInput { upEvs    :: Event Input, 
--                                  downEvs  :: Event Input, 
--                                  rightEvs :: Event Input, 
--                                  leftEvs  :: Event Input }
--                                  deriving Show
--
filterKeyDowns :: (HasTime t s) => Wire s () IO (Event Input) (Event Input)
filterKeyDowns = filterE ((==Down) . keyState)
--                        
-- parseInput :: (HasTime t s) => Wire s () IO (Event Input) ParsedInput
-- parseInput = proc i -> do
--     down <- filterKeyDowns                  -< i
--     uEvs <- filterKey (SpecialKey KeyUp)    -< down
--     dEvs <- filterKey (SpecialKey KeyDown)  -< down
--     rEvs <- filterKey (SpecialKey KeyRight) -< down
--     lEvs <- filterKey (SpecialKey KeyLeft)  -< down
--     returnA -< ParsedInput uEvs dEvs rEvs lEvs
--     where filterKey k = arr $ filterE ((==k) . key)
--
parseInput :: (HasTime t s) => Wire s () IO (Event Input) (Event GameInput)
parseInput = proc i -> do
    down <- filterKeyDowns          -< i
    gameEvent <- arr translateInput -< down
    returnA -< gameEvent

translateInput :: Event Input -> Event GameInput
translateInput (Event (Keyboard {key = SpecialKey KeyUp   })) = Event MoveUp
translateInput (Event (Keyboard {key = SpecialKey KeyRight})) = Event MoveRight
translateInput (Event (Keyboard {key = SpecialKey KeyDown })) = Event MoveDown
translateInput (Event (Keyboard {key = SpecialKey KeyLeft })) = Event MoveLeft
translateInput (Event (Keyboard {key = Char 's' })) = Event Shot
translateInput _  = NoEvent
