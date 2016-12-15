{-# LANGUAGE Arrows #-}
module Input (parseInput
             ,Input(..)
             ,ParsedInput(..)
             ) where

import FRP.Yampa
import Graphics.UI.GLUT

data Input = Keyboard { key       :: Key,
                        keyState  :: KeyState,
                        modifiers :: Modifiers }
                        deriving (Eq, Show)

data ParsedInput = ParsedInput { upEvs    :: Event Input, 
                                 downEvs  :: Event Input, 
                                 rightEvs :: Event Input, 
                                 leftEvs  :: Event Input }
                                 deriving Show

filterKeyDowns :: SF (Event Input) (Event Input)
filterKeyDowns = arr $ filterE ((==Down) . keyState)
                       
parseInput :: SF (Event Input) ParsedInput
parseInput = proc i -> do
    down <- filterKeyDowns                  -< i
    uEvs <- filterKey (SpecialKey KeyUp)    -< down
    dEvs <- filterKey (SpecialKey KeyDown)  -< down
    rEvs <- filterKey (SpecialKey KeyRight) -< down
    lEvs <- filterKey (SpecialKey KeyLeft)  -< down
    returnA -< ParsedInput uEvs dEvs rEvs lEvs
    where filterKey k = arr $ filterE ((==k) . key)

