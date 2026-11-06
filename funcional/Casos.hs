{-# OPTIONS_GHC -Wall -Werror #-}

-- Os casos, a conferência e o texto impresso, tudo puro: o main só imprime o que sai daqui
module Casos
  ( casosEtapa02
  , textoDoCaso
  , textoDoResumo
  , todosAprovados
  ) where

import Data.List (intercalate)
import Labirinto (Posicao, resolverLabirinto, textoPosicao, textoResultado)

data CasoTeste = CasoTeste
  { casoId :: String
  , casoTitulo :: String
  , casoLinhas :: [String]
  , casoOrigem :: Posicao
  , casoDestino :: Posicao
  , casoSaidaEsperada :: String
  }

juntarLinhas :: [String] -> String
juntarLinhas = intercalate "\n"

-- Os 15 casos de testes/casos.md, na mesma ordem
casosEtapa02 :: [CasoTeste]
casosEtapa02 =
  [ CasoTeste
      { casoId = "CN-01"
      , casoTitulo = "Caminho mínimo único"
      , casoLinhas = ["..###", "#...#", "###.#", "....."]
      , casoOrigem = (0, 0)
      , casoDestino = (3, 4)
      , casoSaidaEsperada =
          juntarLinhas
            [ "Resultado: Caminho encontrado"
            , "Caminho: (0,0) → (0,1) → (1,1) → (1,2) → (1,3) → (2,3) → (3,3) → (3,4)"
            , "Movimentos: 7"
            ]
      }
  , CasoTeste
      { casoId = "CN-02"
      , casoTitulo = "Vários caminhos mínimos"
      , casoLinhas = ["...", "...", "..."]
      , casoOrigem = (0, 0)
      , casoDestino = (2, 2)
      , casoSaidaEsperada =
          juntarLinhas
            [ "Resultado: Caminho encontrado"
            , "Caminho: (0,0) → (0,1) → (0,2) → (1,2) → (2,2)"
            , "Movimentos: 4"
            ]
      }
  , CasoTeste
      { casoId = "CN-03"
      , casoTitulo = "Desvio por uma única passagem"
      , casoLinhas = ["....", "##.#", "...."]
      , casoOrigem = (0, 0)
      , casoDestino = (2, 0)
      , casoSaidaEsperada =
          juntarLinhas
            [ "Resultado: Caminho encontrado"
            , "Caminho: (0,0) → (0,1) → (0,2) → (1,2) → (2,2) → (2,1) → (2,0)"
            , "Movimentos: 6"
            ]
      }
  , CasoTeste
      { casoId = "CN-04"
      , casoTitulo = "Percurso no sentido inverso"
      , casoLinhas = ["..###", "#...#", "###.#", "....."]
      , casoOrigem = (3, 4)
      , casoDestino = (0, 0)
      , casoSaidaEsperada =
          juntarLinhas
            [ "Resultado: Caminho encontrado"
            , "Caminho: (3,4) → (3,3) → (2,3) → (1,3) → (1,2) → (1,1) → (0,1) → (0,0)"
            , "Movimentos: 7"
            ]
      }
  , CasoTeste
      { casoId = "CN-05"
      , casoTitulo = "Labirinto em serpentina"
      , casoLinhas = [".....", "####.", ".....", ".####", "....."]
      , casoOrigem = (0, 0)
      , casoDestino = (4, 4)
      , casoSaidaEsperada =
          juntarLinhas
            [ "Resultado: Caminho encontrado"
            , "Caminho: (0,0) → (0,1) → (0,2) → (0,3) → (0,4) → (1,4) → (2,4) → (2,3)"
                ++ " → (2,2) → (2,1) → (2,0) → (3,0) → (4,0) → (4,1) → (4,2) → (4,3) → (4,4)"
            , "Movimentos: 16"
            ]
      }
  , CasoTeste
      { casoId = "CN-06"
      , casoTitulo = "Escolha do menor entre dois percursos"
      , casoLinhas = [".......", ".#####.", "......."]
      , casoOrigem = (0, 1)
      , casoDestino = (2, 1)
      , casoSaidaEsperada =
          juntarLinhas
            [ "Resultado: Caminho encontrado"
            , "Caminho: (0,1) → (0,0) → (1,0) → (2,0) → (2,1)"
            , "Movimentos: 4"
            ]
      }
  , CasoTeste
      { casoId = "CN-07"
      , casoTitulo = "Contorno de obstáculo"
      , casoLinhas = [".....", "..#..", "....."]
      , casoOrigem = (1, 0)
      , casoDestino = (1, 4)
      , casoSaidaEsperada =
          juntarLinhas
            [ "Resultado: Caminho encontrado"
            , "Caminho: (1,0) → (0,0) → (0,1) → (0,2) → (0,3) → (0,4) → (1,4)"
            , "Movimentos: 6"
            ]
      }
  , CasoTeste
      { casoId = "CN-08"
      , casoTitulo = "Labirinto com becos sem saída"
      , casoLinhas =
          [ "..#....."
          , "#.#.###."
          , "#...#..."
          , "###.#.##"
          , "#...#..."
          , "#.###.#."
          , "#....##."
          ]
      , casoOrigem = (0, 0)
      , casoDestino = (6, 7)
      , casoSaidaEsperada =
          juntarLinhas
            [ "Resultado: Caminho encontrado"
            , "Caminho: (0,0) → (0,1) → (1,1) → (2,1) → (2,2) → (2,3) → (1,3) → (0,3)"
                ++ " → (0,4) → (0,5) → (0,6) → (0,7) → (1,7) → (2,7) → (2,6) → (2,5)"
                ++ " → (3,5) → (4,5) → (4,6) → (4,7) → (5,7) → (6,7)"
            , "Movimentos: 21"
            ]
      }
  , CasoTeste
      { casoId = "CN-09"
      , casoTitulo = "Destino inalcançável"
      , casoLinhas = ["..#", "###", "#.."]
      , casoOrigem = (0, 0)
      , casoDestino = (2, 2)
      , casoSaidaEsperada = juntarLinhas ["Resultado: Sem caminho"]
      }
  , CasoTeste
      { casoId = "CN-10"
      , casoTitulo = "Destino cercado por paredes"
      , casoLinhas = [".....", ".###.", ".#.#.", ".###.", "....."]
      , casoOrigem = (0, 0)
      , casoDestino = (2, 2)
      , casoSaidaEsperada = juntarLinhas ["Resultado: Sem caminho"]
      }
  , CasoTeste
      { casoId = "CL-01"
      , casoTitulo = "Origem igual ao destino"
      , casoLinhas = ["...", "##.", "..."]
      , casoOrigem = (0, 0)
      , casoDestino = (0, 0)
      , casoSaidaEsperada =
          juntarLinhas
            [ "Resultado: Caminho encontrado"
            , "Caminho: (0,0)"
            , "Movimentos: 0"
            ]
      }
  , CasoTeste
      { casoId = "CL-02"
      , casoTitulo = "Labirinto de uma única linha"
      , casoLinhas = ["....."]
      , casoOrigem = (0, 0)
      , casoDestino = (0, 4)
      , casoSaidaEsperada =
          juntarLinhas
            [ "Resultado: Caminho encontrado"
            , "Caminho: (0,0) → (0,1) → (0,2) → (0,3) → (0,4)"
            , "Movimentos: 4"
            ]
      }
  , CasoTeste
      { casoId = "CL-03"
      , casoTitulo = "Ligação apenas pela diagonal"
      , casoLinhas = [".#", "#."]
      , casoOrigem = (0, 0)
      , casoDestino = (1, 1)
      , casoSaidaEsperada = juntarLinhas ["Resultado: Sem caminho"]
      }
  , CasoTeste
      { casoId = "CI-01"
      , casoTitulo = "Origem bloqueada"
      , casoLinhas = ["#.", ".."]
      , casoOrigem = (0, 0)
      , casoDestino = (1, 1)
      , casoSaidaEsperada =
          juntarLinhas
            [ "Resultado: Entrada inválida"
            , "Motivo: Origem bloqueada"
            ]
      }
  , CasoTeste
      { casoId = "CI-02"
      , casoTitulo = "Destino fora dos limites"
      , casoLinhas = ["...", "..."]
      , casoOrigem = (0, 0)
      , casoDestino = (2, 0)
      , casoSaidaEsperada =
          juntarLinhas
            [ "Resultado: Entrada inválida"
            , "Motivo: Destino fora dos limites"
            ]
      }
  ]

saidaObtida :: CasoTeste -> String
saidaObtida caso =
  textoResultado (resolverLabirinto (casoLinhas caso) (casoOrigem caso) (casoDestino caso))

-- Conferência por texto exato com a saída esperada
casoAprovado :: CasoTeste -> Bool
casoAprovado caso = saidaObtida caso == casoSaidaEsperada caso

contarAprovados :: [CasoTeste] -> Int
contarAprovados = length . filter casoAprovado

todosAprovados :: [CasoTeste] -> Bool
todosAprovados casos = all casoAprovado casos

separador :: Char -> String
separador simbolo = replicate 50 simbolo ++ "\n"

alinharADireita :: Int -> String -> String
alinharADireita largura texto = replicate (largura - length texto) ' ' ++ texto

linhaDeIndices :: [String] -> String
linhaDeIndices [] = "    \n"
linhaDeIndices (primeira : _) =
  "    " ++ concatMap (\coluna -> show (coluna `mod` 10)) [0 .. length primeira - 1] ++ "\n"

linhaNumerada :: (Int, String) -> String
linhaNumerada (numero, linha) = alinharADireita 3 (show numero) ++ " " ++ linha ++ "\n"

-- Usa os dados do caso, e não o labirinto, porque um labirinto inválido nem chega a existir
textoDaEntrada :: CasoTeste -> String
textoDaEntrada caso =
  linhaDeIndices (casoLinhas caso)
    ++ concatMap linhaNumerada (zip [0 ..] (casoLinhas caso))
    ++ "Origem: "
    ++ textoPosicao (casoOrigem caso)
    ++ "   Destino: "
    ++ textoPosicao (casoDestino caso)
    ++ "\n"

textoDaConferencia :: CasoTeste -> String
textoDaConferencia caso
  | casoAprovado caso = "Conferência com testes/casos.md: OK\n\n"
  | otherwise =
      "Conferência com testes/casos.md: FALHOU\nSaída esperada:\n"
        ++ casoSaidaEsperada caso
        ++ "\n\n"

-- O texto inteiro do caso, pronto: quem imprime é o main
textoDoCaso :: CasoTeste -> String
textoDoCaso caso =
  separador '='
    ++ casoId caso
    ++ " - "
    ++ casoTitulo caso
    ++ "\n"
    ++ separador '-'
    ++ "Entrada:\n"
    ++ textoDaEntrada caso
    ++ "\nSaída obtida:\n"
    ++ saidaObtida caso
    ++ "\n\n"
    ++ textoDaConferencia caso

textoDoResumo :: [CasoTeste] -> String
textoDoResumo casos =
  separador '='
    ++ "Resumo: "
    ++ show (contarAprovados casos)
    ++ " de "
    ++ show (length casos)
    ++ " casos conferem com testes/casos.md\n"