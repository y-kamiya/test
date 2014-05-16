main :: IO ()
main = fizzbuzz 0
        
-- normal
fizzBuzz :: Int -> IO ()
fizzBuzz n 
    | n == 100 = print n
    | n `mod` 15 == 0 = print "FizzBuzz" >> fizzBuzz (n+1)
    | n `mod` 3 == 0 = print "Fizz" >> fizzBuzz (n+1)
    | n `mod` 5 == 0 = print "Buzz" >> fizzBuzz (n+1)
    | otherwise = print n >> fizzBuzz (n+1)
    

-- not use arithmetic operator
list = ["a","a","Fizz","a","Buzz","Fizz","a","a","Fizz","Buzz","a","Fizz","a","a","FizzBuzz"]

fizzBuzz' :: IO ()
fizzBuzz' = mapM_ putStrLn $ tail $ f (take 100 $ concat $ repeat list) ["0"]
    where f :: [String] -> [String] -> [String]
          f [] as = as
          f ss as = case head ss of 
                    "a" -> f (tail ss) (as ++ [show (length as)])
                    _   -> f (tail ss) (as ++ [head ss])
    

-- created by takebe
data Nat = Zero | Succ Nat
         
isThreeMulti Zero = True
isThreeMulti (Succ (Succ (Succ x))) = isThreeMulti x
isThreeMulti _ = False

isFiveMulti Zero = True
isFiveMulti (Succ (Succ (Succ (Succ (Succ x))))) = isFiveMulti x
isFiveMulti _ = False

showNat' (n:ns) Zero = n
showNat' (n:ns) (Succ x) = showNat' ns x

showNat = show . showNat' [0..]

fizzbuzz'' x | isThreeMulti x && isFiveMulti x = "FizzBuzz"
             | isThreeMulti x = "Fizz"
             | isFiveMulti x = "Buzz"
             | otherwise = showNat x
             

main'' :: IO ()
main'' = print $ map fizzbuzz'' $ take 100 (iterate Succ (Succ Zero))
