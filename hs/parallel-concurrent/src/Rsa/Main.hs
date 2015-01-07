import System.Environment (getArgs)
import Data.ByteString.Char8 (ByteString)
import qualified Data.ByteString.Char8 as B
import Control.Parallel.Strategies 

--encrypt :: Integer -> Integer -> ByteString -> ByteString
-- encrypt :: Integer -> Integer -> Integer -> Integer
-- encrypt n e x = x ^ e `mod` n

p, q, e, n, d, l :: Integer
p = 17
q = 11
e = l - 1 
n = p * q
d = let (d',_) = gcdEx e l in if d' < 0 then d' + l else d'
l = (p-1) * (q-1) `div` gcd (p-1) (q-1)

gcdEx :: Integer -> Integer -> (Integer,Integer)
gcdEx a b
  | b == 0 = (1,0)
  | otherwise = 
    let q = a `div` b
        r = a `mod` b
        (x,y) = gcdEx b r
    in (y, x - q * y)

byChar :: (Integer -> Integer) -> ByteString -> ByteString
byChar f = B.pack 
           . map (toEnum . fromIntegral . f . fromIntegral . fromEnum)
           . B.unpack

byLine :: ([ByteString] -> [ByteString]) -> ByteString -> ByteString
byLine f = B.unlines . f . B.lines

encrypt_seq :: ByteString -> ByteString
encrypt_seq = B.unlines 
            . map (byChar encode)
            . chunk 1000 

decrypt_seq :: ByteString -> ByteString
decrypt_seq = byLine $ map (byChar decode)

encrypt :: ByteString -> ByteString
encrypt = B.unlines 
        . withStrategy (parList rdeepseq) 
        . map (byChar encode)
        . chunk 1000

encode :: Integer -> Integer
encode x = x ^ e `mod` n

decode :: Integer -> Integer
decode x = x ^ d `mod` n

chunk :: Int -> ByteString -> [ByteString]
chunk n bs 
  | B.length bs < n = [bs]
  | otherwise = h : chunk n t
  where 
    (h, t) = B.splitAt n bs

main :: IO ()
main = do
  [command, input] <- getArgs
  content <- case input of
    "-" -> B.getContents
    x -> B.readFile input
  case command of
    "enc_seq" -> B.putStr . encrypt_seq $ content
    "dec_seq" -> B.putStr . decrypt_seq $ content
    "enc"     -> B.putStr . encrypt $ content
    _ -> error "pass `enc` ot `dec` as first argument"
