import Text.ParserCombinators.Parsec hiding (spaces)
import System.Environment
import Control.Monad

data LispVal = Atom String
             | List [LispVal]
             | DottedList [LispVal] LispVal
             | Number Integer
             | String String
             | Bool Bool

-- instance Show LispVal where
--   show = showVal
-- 
-- showVal :: LispVal -> String
-- showVal (String s) = "\"" ++ s ++ "\""
-- showVal (Number n) = show n
-- showVal (Atom s) = s
-- showVal (Bool True) = "#t"
-- showVal (Bool False) = "#f"
-- showVal (List list) = "(" ++ unwordList list ++ ")"
-- showVal (DottedList list v) = "(" ++ unwordList list ++ " . " ++ showVal v ++ ")"
-- 
-- eval :: LispVal -> LispVal
-- eval val@(String _) = val
-- eval val@(Number _) = val
-- eval val@(Bool _) = val
-- eval (List [Atom "quote", val]) = val
-- 
-- unwordList :: [LispVal] -> String
-- unwordList = unwords . map showVal

symbol :: Parser Char
symbol = oneOf "!#$%&|*+-/:<=>?@^_~"

spaces :: Parser ()
spaces = skipMany1 space

readExpr :: String -> String
readExpr input = case parse parseExpr "lisp" input of
  Left err -> "No match: " ++ show err
  Right val -> "Found " ++ show val

parseString :: Parser LispVal
parseString = do
  char '"'
  x <- many $ noneOf "\""
  char '"'
  return $ String x

parseAtom :: Parser LispVal
parseAtom = do
  first <- letter <|> symbol
  rest <- many $ letter <|> digit <|> symbol
  let atom = first : rest
  return $ case atom of
             "#t" -> Bool True
             "#f" -> Bool False
             _    -> Atom atom

parseNumber :: Parser LispVal
parseNumber = liftM (Number . read) $ many1 digit

parseExpr :: Parser LispVal
parseExpr = parseAtom
        <|> parseString
        <|> parseNumber
        <|> do char '('
               x <- try parseList <|> parseDottedList
               char ')'
               return x

parseList :: Parser LispVal
parseList = liftM List $ sepBy parseExpr spaces

parseDottedList :: Parser LispVal
parseDottedList = do
  head <- endBy parseExpr spaces
  tail <- char '.' >> spaces >> parseExpr
  return $ DottedList head tail

main :: IO ()
main = do
  [s] <- getArgs
  putStrLn $ readExpr s

