module MyParser (main) where

import Data.Maybe
import Text.Megaparsec.Char
import Text.Megaparsec  
import Text.Megaparsec.String  
import System.Environment

main = do  
    input <- fmap head getArgs
    contents <- readFile input
    parseTest programExecutor contents


data Exp = Var String
         | Numar Int
         | Suma Exp Exp
         | Diferenta Exp Exp
         | Produs Exp Exp deriving Show

idParser :: Parser String
idParser = do
   firstCharacter <- oneOf "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
   lastCharacters <- many (oneOf "1234567890_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
   _ <- space
   return (firstCharacter:lastCharacters)

varParser :: Parser Exp
varParser = do
   id <- idParser
   return (Var id)

numParser :: Parser Exp
numParser = do
   sequence <- some digitChar
   _ <- space
   return (Numar (read sequence))

factorParser :: Parser Exp
factorParser = numParser <|> varParser <|> (do
    _ <- char '('
    _ <- space
    e <- expParser
    _ <- space
    _ <- char ')'
    _ <- space
    return e
    )
   
auxTermParser :: Exp -> Parser Exp
auxTermParser t = (do
   sign <- char '*'
   _ <- space
   factor <- factorParser 
   o <- auxExpParser (Produs t factor)
   return o) <|>  (do
       sign <- char '/'
       _ <- space
       factor <- factorParser 
       o <-auxExpParser  (Produs t factor)
       return o) <|> (do 
           _ <- space
           return t)

termParser :: Parser Exp
termParser = do
   f1 <- factorParser
   r <- auxTermParser f1
   return r

auxExpParser :: Exp -> Parser Exp
auxExpParser t = (do
   sign <- char '+'
   _ <- space
   return o) <|>  (do
       sign <- char '-'
       _ <- space
       termen <- termParser 
       o <-auxExpParser  (Diferenta t termen)
       return o) <|> (do 
           _ <- space
           return t)

expParser :: Parser Exp
expParser = do
   f1 <- termParser
   r <- auxExpParser f1
   return r

type ValuationPar = String -> Maybe Int

empty :: ValuationPar
empty _ = Nothing

update :: ValuationPar -> String -> Maybe Int -> ValuationPar
update f variabila valoare = \x -> if x == variabila then valoare else f x 

lift2 :: (a -> b -> c) -> Maybe a -> Maybe b -> Maybe c
lift2 f Nothing _ = Nothing
lift2 f _ Nothing = Nothing
lift2 f (Just x) (Just y) = Just (f x y)

sumaMaybe :: Maybe Int -> Maybe Int -> Maybe Int
sumaMaybe = lift2 (+)

diferentaMaybe :: Maybe Int -> Maybe Int -> Maybe Int
diferentaMaybe = lift2 (-)

produsMaybe :: Maybe Int -> Maybe Int -> Maybe Int
produsMaybe = lift2 (*)

evalp :: Exp -> ValuationPar -> Maybe Int
evalp (Numar x) _ = Just x
evalp (Var y) valp = valp y
evalp (Suma e1 e2) valp = sumaMaybe (evalp e1 valp) (evalp e2 valp)
evalp (Diferenta e1 e2) valp = diferentaMaybe (evalp e1 valp) (evalp e2 valp)
evalp (Produs e1 e2) valp = produsMaybe (evalp e1 valp) (evalp e2 valp)

executaInstr :: ValuationPar -> Instr -> ValuationPar
executaInstr valuatie (Atrib v e) = (update valuatie v (evalp e valuatie))
executaInstr valuatie (Cond e p1 p2) = case  (evalp e valuatie) of
    (Just 0) -> fromMaybe (executaProgram valuatie p2)
    _ -> fromMaybe(executaProgram valuatie p1)
executaInstr valuatie (Loop e p1) = case (evalp e valuatie) of
    (Just 0) -> valuatie 
    _ -> fromMaybe(executaProgram valuatie p1)

type Program = [Instr]

executaProgram :: ValuationPar -> Program -> Maybe ValuationPar
executaProgram valuatie [] = Just valuatie
executaProgram valuatie (i:is) = case executaInstr valuatie i of
                                     Nothing        -> Nothing
                                     Just valuatie' -> executaProgram valuatie' is

data Instr = Atrib String Exp
           | Cond Exp Program Program
           | Loop Exp Program
           | For Exp Program deriving Show 

instrParser :: Parser Instr
instrParser = condParser <|> loopParser  <|> atribParser

atribParser :: Parser Instr
atribParser = do
    varName <- idParser
    _ <- space
    _ <- char '='
    _ <- space
    e <- expParser
    _ <- space
    _ <- char  ';'
    _ <- space
    return (Atrib varName e)

programParser :: Parser Program
programParser = do 
   is <- many instrParser
   return is

condParser :: Parser Instr
condParser = do
   _ <- string "if"
   _ <- space
   _ <- char '('
   _ <- space
   e <- expParser
   _ <- space
   _ <- char ')'
   _ <- space
   _ <- char '{'
   _ <- space
   p1 <- programParser
   _ <- space
   _ <- char '}'
   _ <- space
   _ <- string "else"
   _ <- space
   _ <- char '{'
   _ <- space
   p2 <- programParser
   _ <- space
   _ <- char '}'
   _ <- space
   return (Cond e p1 p2)

loopParser :: Parser Instr
loopParser = do
    _ <- string "while"
    _ <- space
    _ <- char '('
    _ <- space
    e <- expParser
    _ <- space
    _ <- char ')'
    _ <- space
    _ <- char '{'
    _ <- space
    p1 <- programParser
    _ <- space
    _ <- char '}'
    _ <- space
    return (Loop e p1)

programExecutor :: Parser String
programExecutor = do
    _ <- space
    p <- programParser
    return (show (evalProgram p))

evalProgram :: Program -> Maybe Int
evalProgram prog = case (executaProgram empty prog) of
                      Just valuatie -> valuatie "result"
                      Nothing       -> Nothing


