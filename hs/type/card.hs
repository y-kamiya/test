module Card where 

data Suit = Club | Diamond | Heart | Spade
          deriving (Read, Show, Enum, Eq, Ord)

data CardValue = Two | Three | Four | Five 
           | Six | Seven | Eight | Nine | Ten 
           | Jack | Queen | King | Ace
           deriving (Read, Show, Enum, Eq, Ord)


data Card = Card { value :: CardValue
          , suit :: Suit}
            deriving (Read, Show, Eq)

instance Ord Card where
        compare c1 c2 
            | value c1 == value c2 = compare (suit c1) (suit c2)
            | otherwise = compare (value c1) (value c2)



