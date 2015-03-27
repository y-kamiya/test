import Data.Char
import Data.Monoid
import Data.Traversable
import qualified Data.Foldable as FO
import Control.Applicative

uppers :: [Char] -> [Int]
uppers [] = []
uppers (x:xs)
  | isUpper x = fromEnum x - fromEnum 'A' : uppers xs
  | otherwise = uppers xs

uppers' :: Monoid r => (Int -> r) -> [Char] -> r
uppers' f [] = mempty
uppers' f (x:xs)
  | isUpper x = f (fromEnum x - fromEnum 'A') `mappend` uppers' f xs
  | otherwise = uppers' f xs

data Count = Count { getCount :: Int } deriving Show

instance Monoid Count where
  mempty = Count 0
  Count x `mappend` Count y = Count (x + y)

single :: a -> Count
single _ = Count 1




filtering :: Monoid r => (a -> Bool) -> (a -> r) -> a -> r
filtering p f a
  | p a = f a
  | otherwise = mempty

maps :: (a -> b) -> (b -> r) -> a -> r
maps f g = g . f

uppers'' :: (FO.Foldable f, Monoid r) => (Int -> r) -> f Char -> r
uppers'' = FO.foldMap
         . filtering isUpper
         . maps (subtract (fromEnum 'A') . fromEnum)




uppers''' :: (Applicative f) => (Int -> f Int) -> [Char] -> f [Char]
uppers''' f [] = pure []
uppers''' f (x:xs)
  | isUpper x = liftA2 (:) x' (uppers''' f xs)
  | otherwise = liftA2 (:) (pure x) (uppers''' f xs)
  where
    x' = fmap (\n -> toEnum $ n + fromEnum 'A') (f (fromEnum x - fromEnum 'A'))

myuppers''' :: (Int -> Int) -> [Char] -> [Char]
myuppers''' f [] = []
myuppers''' f (x:xs)
  | isUpper x = (:) x' (myuppers''' f xs)
  | otherwise = (:) x  (myuppers''' f xs)
  where
    x' = (\n -> toEnum $ n + fromEnum 'A') (f (fromEnum x - fromEnum 'A'))

newtype Identity a = Identity { runIdentity :: a }

instance Functor Identity where
  fmap f (Identity a) = Identity (f a)

instance Applicative Identity where
  pure = Identity
  Identity f <*> Identity x = Identity (f x)

caesar :: Int -> [Char] -> [Char]
caesar k = runIdentity . uppers''' (Identity . (`mod` 26) . (+k))

purely :: ((a -> Identity a) -> s -> Identity s) -> (a -> a) -> s -> s
purely t f = runIdentity . t (Identity . f)



-- newtype Const r a = Const { getConst :: r }
-- 
-- instance Functor (Const r) where
--   fmap _ (Const r) = Const r
-- 
-- instance Monoid r => Applicative (Const r) where
--   pure _ = Const mempty
--   Const a <*> Const b = Const (a `mappend` b)

smash :: ((a -> Const r a) -> s -> Const r s) -> (a -> r) -> s -> r
smash t f = getConst . t (Const . f)

filtered :: Applicative f => (a -> Bool) -> (a -> f a) -> a -> f a
filtered p f a
  | p a = f a
  | otherwise = pure a

isomorphoic :: Functor f => (s -> a) -> (a -> s) -> (a -> f a) -> s -> f s
isomorphoic f g c = fmap g . c . f

uppers'''' :: (Applicative f, Traversable t) => (Int -> f Int) -> t Char -> f (t Char)
uppers'''' = traverse
           . filtered isUpper
           . isomorphoic (subtract (fromEnum 'A') . fromEnum) (\n -> toEnum $ n + fromEnum 'A')







myupppers :: ([Int] -> [Int]) -> [Char] -> [Int]
myupppers _ [] = []
myupppers f (x:xs)
  | isUpper x = f $ (fromEnum x - fromEnum 'A') : uppers xs
  | otherwise = f $ uppers xs
