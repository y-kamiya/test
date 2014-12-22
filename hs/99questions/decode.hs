data Element a = Single a | Multiple Int a

main = print $ decodeModified' [Multiple 4 'a',Single 'b',Multiple 2 'c', Multiple 2 'a',Single 'd',Multiple 4 'e']

decodeModified :: [Element a] -> [a]
decodeModified = concatMap decode 
    where
        decode :: Element a -> [a]
        decode (Single x) = [x]
        decode (Multiple n x) = replicate n x
    
decodeModified' :: [Element a] -> [a]
decodeModified' = concatMap (uncurry replicate . toTupple)
    where
        toTupple :: Element a -> (Int, a)
        toTupple (Single x) = (1,x)
        toTupple (Multiple n x) = (n,x)
