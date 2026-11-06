-- Projeto P4 - Caminho mínimo em labirinto - Implementação funcional [P4-ETAPA-06]
-- Executa os 15 casos de testes/casos.md, declarados em Casos.hs.
{-# OPTIONS_GHC -Wall -Werror #-}

module Main (main) where

import Casos (casosEtapa02, textoDoCaso, textoDoResumo, todosAprovados)
import System.Exit (exitFailure, exitSuccess)
import System.IO (hSetEncoding, stdout, utf8)

-- Único ponto que conversa com o mundo externo: codificação da saída, tela e código de saída
main :: IO ()
main = do
  -- Saída em UTF-8 por causa da seta e dos acentos
  hSetEncoding stdout utf8
  -- putStr, e não putStrLn: o texto de cada caso já vem com as quebras de linha
  mapM_ (putStr . textoDoCaso) casosEtapa02
  putStr (textoDoResumo casosEtapa02)
  if todosAprovados casosEtapa02
    then exitSuccess
    else exitFailure