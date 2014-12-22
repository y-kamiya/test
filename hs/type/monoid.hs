module Mymonoid where

class Mymonoid a where
    mempty :: a
    mappend :: a -> a -> a
    mconcat :: [a] -> a
    mconcat = foldr mappend mempty


instance Mymonoid [a] where
    mempty = []
    mappend = (++)

newtype Sum a = Sum { getSum :: a } deriving (Show, Eq, Ord)

instance Num a => Mymonoid (Sum a) where
    mempty = Sum 0
    a `mappend` b  = Sum $ (getSum a) + (getSum b) 

newtype Product a = Product { getProduct :: a }  deriving (Show, Eq, Ord)              

instance Num a => Mymonoid (Product a) where
    mempty = Product 1
    a `mappend` b = Product $ (getProduct a) * (getProduct b)


instance Mymonoid a => Mymonoid (Maybe a) where
    mempty = Nothing
    Just x `mappend` Nothing = Just x
    Nothing `mappend` Just x = Just x
    Just x `mappend` Just y = Just (x `mappend` y)
