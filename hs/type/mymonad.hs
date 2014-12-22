module Mymonad where

import Data.Monoid

class Mymonad m where
    ret :: a -> m a
    bind :: m a -> (a -> m b) -> m b
    bind' :: m a -> m b -> m b
    bind' a b = a `bind` \_ -> b

instance Mymonad Maybe where
    ret x = Just x
    Just x `bind` k = k x
    Nothing `bind` k = Nothing

instance Mymonad (Either a) where
    ret x = Right x
    Left x `bind` _ = Left x
    Right x `bind` f = f x

instance Mymonad IO where
    ret = return
    m `bind` f = do 
        a <- m
        f a

instance Mymonad [] where
    ret x = [x]
    xs `bind` f = concatMap  f xs


-- Writer
newtype Writer w a = Writer { runWriter :: (a, w) }

instance Monoid w => Mymonad (Writer w) where
    ret x = Writer (x, mempty)
    Writer (x,a) `bind` f = let Writer (y,b) = f x
                            in Writer (y, a `mappend` b)

tell :: Monoid w => w -> Writer w ()
tell s = Writer ((), s)



fibo :: Int -> (Int, [String])
fibo n = fibo' n [] 
    where
        fibo' n xs = 
            let ys = xs ++ ["fibo " ++ show n ++ " called"]
            in if n < 2 
               then (n, ys ++ ["fibo " ++ show n ++ " = " ++ show n])
               else let (a, z1) = fibo' (n-1) ys
                        (b, z2) = fibo' (n-2) z1
                    in (a+b, z2 ++ ["fibo " ++ show n ++ " = " ++ show (a+b)])


fiboM :: Int -> Writer [String] Int
fiboM n = 
    tell [ "fibo " ++ show n ++ " called" ] `bind'` 
    if n < 2 then tell [ "fibo " ++ show n ++ " = " ++ show n ] `bind'` ret n
             else fiboM (n-1) `bind` \a -> 
                     fiboM (n-2) `bind` \b -> ret (a+b)
                        

--Reader
instance Mymonad ((->) r) where
    ret x = \_ -> x
    f `bind` g = \x -> g (f x) x 

newtype Reader e a = Reader { runReader :: e -> a }

instance Mymonad (Reader e) where
    ret x = Reader $ \_ -> x
    (Reader f) `bind` g = Reader $ \e -> runReader (g (f e)) e 

ask :: Reader a a 
ask = Reader id

local :: (e -> e) -> Reader e a -> Reader e a
local f c = Reader $ \e -> runReader c (f e)


-- State
type Stack a = [a]

pop :: Stack a -> (a, Stack a)
pop (x:xs) = (x, xs)

push :: Stack a -> a -> ((), Stack a)
push xs x = ((), x:xs)

stackTest :: Stack Int -> ((), Stack Int)
stackTest xs = let (y, ys) = pop xs
                   (z, zs) = pop ys
               in  push zs (y+z)


newtype State s a = State { runState :: s -> (a, s) }

instance Mymonad (State s) where
    ret x = State (\s -> (x, s))
    (State f) `bind` g = State $ \s -> let (x, s1) = f s
                                       in  runState (g x) s1

get :: State s s 
get = State $ \s -> (s,s)

put :: Stack a -> State s ()
put s = State $ \_ -> ((), s)




popM :: State (Stack a) Int
popM = 
