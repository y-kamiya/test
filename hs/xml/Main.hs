{-# LANGUAGE OverloadedStrings #-}
import Prelude hiding (readFile)
import Text.XML
import Text.XML.Cursor
import qualified Data.Text as T

main :: IO ()
main = do
    doc <- readFile def "test.xml"
    let cursor = fromDocument doc
    --print $ child cursor >>= element "body" >>= child >>= element "hgroup" >>= child >>= element "h1" >>= child >>= content    
    print $ cursor $/ element "body" &/ element "hgroup" &/ element "h1" &/ content
    print $ T.concat $ 
      cursor $// element "h2"
             >=> attributeIs "class" "bar"
             >=> precedingSibling
             >=> element "h1"
             &// content
    
