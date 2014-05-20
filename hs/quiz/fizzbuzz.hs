main :: IO ()
main = fizzBuzz 0
        
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
    
