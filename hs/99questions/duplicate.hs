main = print $ dupli [1,2,3]

dupli :: [a] -> [a]
dupli = concatMap dupliHelper
    where 
        dupliHelper :: a -> [a]
        dupliHelper x = replicate 2 x


