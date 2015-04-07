{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE TemplateHaskell #-}

import Prelude 
import Data.Aeson
import Data.Aeson.TH
import Control.Applicative
import Control.Monad
import Data.Char (toLower, toUpper)
import Data.Text hiding (drop, map, toLower, toUpper)
import Data.Map hiding (map, size)
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
        fruits = Fruits { color = "green", shape = "ball", size = 1 }

    print $ toJSON d
    print $ fromJSON (toJSON d) == Success d
    print $ (decode "{\"name\":\"Joe\",\"age\":12}" :: Maybe Person)
    print $ (decode "{\"color\":\"red\",\"shape\":\"ball\",\"size\":1}" :: Maybe Fruits)
    print $ toJSON fruits
    print $ fromJSON (toJSON fruits) == Success fruits


data Fruits = Fruits
    { color :: String
    , shape :: String
    , size  :: Int
    } deriving (Eq, Show)

$(deriveJSON defaultOptions { fieldLabelModifier = drop 1, constructorTagModifier = map toUpper } ''Fruits)

{-
instance FromJSON Fruits where
    parseJSON (Object v) = Fruits <$>
                           v .: "color" <*>
                           v .: "shape" <*>
                           v .: "size"
    parseJSON _ = mzero

instance ToJSON Fruits where
    toJSON (Fruits color shape size) = object [ "color" .= color, "shape" .= shape, "size" .= size ]
-}
