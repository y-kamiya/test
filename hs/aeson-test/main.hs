{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE TemplateHaskell #-}

import Prelude 
import Data.Aeson
import Data.Aeson.TH
import Control.Applicative
import Control.Monad
import Data.Char (toLower)
import Data.Text hiding (drop, map, toLower)
import Data.Map hiding (map)
import qualified Data.ByteString.Lazy.Char8 as C

data Person = Person
    { name :: Text
    , age  :: Int
    } deriving Show

instance FromJSON Person where
    parseJSON (Object v) = Person <$>
                           v .: "name" <*>
                           v .: "age"
    parseJSON _ = mzero

instance ToJSON Person where
    toJSON (Person name age) = object [ "name" .= name, "age" .= age ]

data D a = Nullary
         | Unary Int
         | Product String Char a
         | Record { testOne   :: Double
                  , testTwo   :: Bool
                  , testThree :: D a
                  } deriving Eq

$(deriveJSON defaultOptions{ fieldLabelModifier = drop 4, constructorTagModifier = map toLower } ''D)

main :: IO ()
main = do
    let d = Record { testOne = 3.14159
           , testTwo = True
           , testThree = Product "test" 'A' 123
           } :: D Int

    print $ fromJSON (toJSON d) == Success d



