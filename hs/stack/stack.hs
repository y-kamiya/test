module Stack (Stack, empty, pop, push, s) where

newtype Stack a  = Stack [a] deriving Show

empty :: Stack a
empty = Stack []

empty' :: Stack a -> ((), Stack a)
empty' _ = ((), Stack [])

pop :: Stack a -> (a, Stack a)
pop (Stack (x:xs)) = (x, Stack xs)

push :: a -> Stack a -> Stack a
push x (Stack xs) = Stack (x:xs)

push' :: a -> Stack a -> ((), Stack a)
push' x (Stack xs) = ((), Stack (x:xs))

s :: (Num a) => Stack a
s = push 5 $ push 4 $ push 3 $ push 2 $ push 1  empty




sumTwoElem :: Num a => Stack a -> (a, Stack a)
sumTwoElem stack =
       let (a1, stack1) = pop stack 
           (a2, stack2) = pop stack1
       in (a1 + a2, stack2)
 
                    
type StackOp a b = Stack a -> (b, Stack a)

comb ::  StackOp a b -> (b -> StackOp a c) ->  StackOp a c
comb m n = \stack0 -> 
        let (x1, stack1) = m stack0
            (x2, stack2) = n x1 stack1
        in (x2, stack2)

ret :: b -> StackOp a b
ret x = \stack -> (x, stack)

comb_ :: StackOp a b -> StackOp a c -> StackOp a c
comb_ m n = m `comb` (\_ -> n)


topis :: (a -> Bool) -> Stack a -> (Bool, Stack a)
topis p s = 
        let (a, s') = pop s
        in (p a, s')

main = print $ pop `comb` (\x -> 
          pop `comb` \y -> 
                pop `comb` \z ->
                    ret $ (x+z)*y) $ s 

useTopis = print $ topis (>4) `comb` (\x ->
                         topis (>3) `comb` \y ->
                               topis (>2) `comb` \z ->
                                     ret $ and [x,y,z]) $ s

usePush' = print $ pop `comb` push' $ s
