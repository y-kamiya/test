{-# LANGUAGE GADTs #-}

module Question where

import Control.Applicative
import Control.Monad
import Control.Monad.Trans
import Control.Monad.Operational
import System.Random

data Question = Question Int Int

data CalcI a where
  GetQuestion :: CalcI Question
  Answer      :: Int -> CalcI ()

type CalcP m a = ProgramT CalcI m a

getQuestion :: (Monad m) => CalcP m Question
getQuestion = singleton GetQuestion

answer :: (Monad m) => Int -> CalcP m ()
answer = singleton . Answer

interpret :: (RandomGen g) => g -> CalcP IO a -> IO ()
interpret g is = do
  let (m, g') = randomR (1, 9) g
      (n, g'') = randomR (1, 9) g'
  liftIO . putStrLn $ (show m) ++ " + " ++ (show n) ++ " = ?"
  eval g'' is (Question m n)
  where
    eval :: (RandomGen g) => g -> CalcP IO a -> Question -> IO ()
    eval g is q = (\v -> eval' g v q) =<< (viewT is)

    eval' :: (RandomGen g) => g -> ProgramViewT CalcI IO a -> Question -> IO ()
    eval' g (GetQuestion :>>= is) q = eval g (is q) q
    eval' g (Answer x :>>= is) (Question m n)
      | x == m + n = (liftIO . putStrLn) "correct" >> interpret g (is ())
      | otherwise = (liftIO . putStrLn) "incorrect"
    eval' _ (Return _) _ = return ()

human :: CalcP IO ()
human = forever $ do
  x <- read <$> liftIO getLine
  answer x

defaultMain :: IO ()
defaultMain = do
  g <- getStdGen
  -- interpret g human
  interpret g fancyAI

fancyAI :: CalcP IO ()
fancyAI = forever $ do
  (Question m n) <- getQuestion
  let x = if odd m
            then m + n
            else 0
  liftIO . putStrLn $ show x
  answer x
