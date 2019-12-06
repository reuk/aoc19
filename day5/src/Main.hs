module Main where

import Data.List as L
import Data.Vector.Unboxed as V

data State = State { memory :: Vector Int
                   , ip :: Int } deriving Show

data ProgramOutput = Success Int | Failure deriving Show
data Result =  Done ProgramOutput | Ongoing State deriving Show

intcodeOp State { memory = m, ip = ip } fn = 
    let new = fn (m ! (m ! (ip + 1))) (m ! (m ! (ip + 2))) in
    State { memory = m // [(m ! (ip + 3), new)], ip = ip + 4 }

increment s@State { memory = memory, ip = ip } = case memory ! ip of
    1 -> Ongoing $ intcodeOp s (+)
    2 -> Ongoing $ intcodeOp s (*)
    99 -> Done $ Success $ memory ! 0
    _ -> Done Failure

runProgram s = case increment s of
    Done p -> p
    Ongoing s -> runProgram s

run vec noun verb = let modified = vec // [(1, noun), (2, verb)] in
    runProgram State { memory = modified, ip = 0}

main = do
    input <- getContents
    let ints = V.fromList $ Prelude.map read $ L.Split.splitOn "," input
    print $ run ints 12 2
    print $ L.find (\(x, y) -> run ints x y == 19690720) [(x, y) | x <- [0..100], y <- [0..100]]