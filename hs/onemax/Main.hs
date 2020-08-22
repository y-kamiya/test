module Main where

import System.Random
import System.Environment
import System.Console.GetOpt
import Data.List
import Data.Ord
import Data.Maybe
import Control.Monad
import Text.Printf

type Individual = [Bool]
                
type Population = [Individual]

evolve :: Int -> Int -> Population -> IO Population
evolve 0 _ population = return population
evolve generation crossRate population
  | reachMaxFitness population = return population
  | otherwise = do
      printf "generation: %d highest: %d\n" generation (highestFitness population)
      gen0 <- getStdGen
      next <- createNextGeneration population gen0 crossRate
      -- outputPopulation next

      gen1 <- getStdGen
      let selected = select 20 (population ++ next) gen1
      evolve (generation - 1) crossRate selected

  where
    reachMaxFitness :: Population -> Bool
    reachMaxFitness p@(individual:_) = highestFitness p == length individual

createPopulation :: Int -> Int -> StdGen -> Population
createPopulation dim n gen = splitRecursive dim n $ take (dim * n) $ boolList gen
  where boolList :: StdGen -> [Bool]
        boolList = randoms

        splitRecursive :: Int -> Int -> [Bool] -> [[Bool]]
        splitRecursive dim 1 bs = [bs]
        splitRecursive dim n bs = let (individual, bs') = splitAt dim bs
                                  in individual:(splitRecursive dim (n - 1) bs')

fitness :: Individual -> Int
fitness = sum . map fromEnum

findElite :: Population -> Individual
findElite population = population !! maxIndex
  where (maxIndex, _) = maximumBy (comparing snd) $ zip [0..] $ map fitness population

highestFitness :: Population -> Int
highestFitness population = fitness $ findElite population

createNextGeneration :: Population -> StdGen -> Int -> IO Population
createNextGeneration population gen crossRate = do
  let seeds = take 20 $ randomRs (1, 100) gen
  return $ foldl (createChild population) [] $ map mkStdGen seeds
  where
    createChild :: Population -> Population -> StdGen -> Population
    createChild population acc gen = let (ratio, gen') = randomRatio gen
                                         child = if ratio < crossRate then cross population gen' else mutate population gen'
                                     in child:acc
    randomRatio :: StdGen -> (Int, StdGen)
    randomRatio = randomR (1, 100)

select :: Int -> Population -> StdGen -> Population
select n population gen = map (population !!) indexes
  where
    fitnesses = map fitness population
    fitnessTotal = fromIntegral $ sum fitnesses
    thresholds = take n $ randomRs (0, fitnessTotal) gen 
    cumlativeSum = scanl1 (+) fitnesses
    indexes = map (\t -> fst $ head $ dropWhile (\(i, b) -> b < t) $ zip [0..] cumlativeSum) thresholds

cross :: Population -> StdGen -> Individual
cross population gen0 = child
  where
    (index1, gen1) = randomR (0, length population - 1) gen0
    (index2, gen2) = randomR (0, length population - 1) gen1
    parent1 = population !! index1
    parent2 = population !! index2

    dim = length parent1
    (index3, gen3) = randomR (0, dim - 1) gen2
    (index4, gen4) = randomR (0, dim - 1) gen3
    (min, max) = if index3 < index4 then (index3, index4) else (index4, index3)
    child = slice 0 min parent1 ++ slice min max parent2 ++ slice max dim parent1

mutate :: Population -> StdGen -> Individual
mutate population gen0 = child
  where
    (index1, gen1) = randomR (0, length population - 1) gen0
    parent = population !! index1

    dim = length parent
    (index2, gen2) = randomR (0, dim - 1) gen1
    gene = parent !! index2
    child = slice 0 index2 parent ++ [not gene] ++ slice (index2 + 1) dim parent

slice :: Int -> Int -> [a] -> [a]
slice from to xs = take (to - from) $ drop from xs

outputPopulation :: Population -> IO ()
outputPopulation population = do
    print "------------------------------"
    mapM (print . map fromEnum) population
    print "------------------------------"


data Options = Options
  { optDim :: Int
  , optEpochs :: Int
  , optIndividuals :: Int
  , optCrossRate :: Int
  } deriving Show

defaultOptions = Options
  { optDim = 10
  , optEpochs = 20
  , optIndividuals = 50
  , optCrossRate = 95
  }

options :: [OptDescr (Options -> Options)]
options =
  [ Option [] ["dim"] (OptArg 
      ((\f opts -> opts { optDim = f }) . read . fromJust) "int") ""
  , Option [] ["epochs"] (OptArg
      ((\f opts -> opts { optEpochs = f }) . read . fromJust) "int") ""
  , Option [] ["individuals"] (OptArg
      ((\f opts -> opts { optIndividuals = f }) . read . fromJust) "int") ""
  , Option [] ["cross_rate"] (OptArg
      ((\f opts -> opts { optCrossRate = f }) . read . fromJust) "int") ""
  ]
  where func = (\f opts -> opts { optDim = f }) . read . fromJust

compileOpts :: [String] -> IO (Options, [String])
compileOpts args =
  case getOpt Permute options args of
    (opts, rest, []) -> return (foldl (flip id) defaultOptions opts, rest)
    (_, _, errs) -> ioError $ userError $ concat errs ++ usageInfo "Usage: " options

main :: IO ()
main = do
    args <- getArgs
    print args
    (opts, rest) <- compileOpts args
    print opts

    print "start"
    gen <- getStdGen
    finalPopulation <- evolve (optEpochs opts) (optCrossRate opts) $ createPopulation (optDim opts) (optIndividuals opts) gen
    print $ map fitness finalPopulation
    -- outputPopulation finalPopulation
    print "end"






