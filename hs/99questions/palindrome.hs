main = print $ isPalindrome [1,2,3,2,1]

isPalindrome :: Eq a => [a] -> Bool
isPalindrome = (\xs -> xs == reverse xs)
