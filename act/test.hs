import System.IO

main = do
    putStrLn "Ingrese algo"
    test <- getLine
    let val = read test :: Int
    putStrLn show val