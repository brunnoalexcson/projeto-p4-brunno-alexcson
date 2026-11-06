{-# OPTIONS_GHC -Wall -Werror #-}

-- Núcleo puro (nenhuma função tem IO); fora daqui, só a caixa-preta e o texto ficam visíveis
module Labirinto
  ( Posicao
  , resolverLabirinto
  , textoPosicao
  , textoResultado
  ) where

import Data.List (intercalate)
import qualified Data.Set as Set

-- (linha, coluna): a tupla já compara por valor e tem ordem, por isso cabe num Set
type Posicao = (Int, Int)

-- O labirinto é só o conjunto das posições livres: fora dele, é parede ou fora da grade
type Labirinto = Set.Set Posicao

-- Os três desfechos possíveis; cada um carrega só os seus dados
data Resultado
  = CaminhoEncontrado [Posicao]
  | SemCaminho
  | EntradaInvalida String

livre :: Char
livre = '.'

bloqueada :: Char
bloqueada = '#'

labirintoVazio :: [String] -> Bool
labirintoVazio linhas = all null linhas

linhasRegulares :: [String] -> Bool
linhasRegulares [] = True
linhasRegulares (primeira : outras) =
  all (\linha -> length linha == length primeira) outras

celulaConhecida :: Char -> Bool
celulaConhecida celula = celula == livre || celula == bloqueada

celulasConhecidas :: [String] -> Bool
celulasConhecidas linhas = all (all celulaConhecida) linhas

contarColunas :: [String] -> Int
contarColunas [] = 0
contarColunas (primeira : _) = length primeira

dentroDosLimites :: [String] -> Posicao -> Bool
dentroDosLimites linhas (linha, coluna) =
  linha >= 0
    && linha < length linhas
    && coluna >= 0
    && coluna < contarColunas linhas

posicoesLivres :: [String] -> Labirinto
posicoesLivres linhas =
  Set.fromList
    [ (numeroLinha, numeroColuna)
    | (numeroLinha, linha) <- zip [0 ..] linhas
    , (numeroColuna, celula) <- zip [0 ..] linha
    , celula == livre
    ]

-- Uma posição fora da grade não está no conjunto: nunca há acesso inválido
celulaLivre :: Labirinto -> Posicao -> Bool
celulaLivre labirinto posicao = Set.member posicao labirinto

-- A ordem segue a tabela 4.3 do README: vale o primeiro motivo que falhar
validarEntrada :: [String] -> Posicao -> Posicao -> Either String Labirinto
validarEntrada linhas origem destino
  | labirintoVazio linhas = Left "Labirinto vazio"
  | not (linhasRegulares linhas) = Left "Linhas irregulares"
  | not (celulasConhecidas linhas) = Left "Célula desconhecida"
  | not (dentroDosLimites linhas origem) = Left "Origem fora dos limites"
  | not (dentroDosLimites linhas destino) = Left "Destino fora dos limites"
  | not (celulaLivre labirinto origem) = Left "Origem bloqueada"
  | not (celulaLivre labirinto destino) = Left "Destino bloqueado"
  | otherwise = Right labirinto
  where
    labirinto :: Labirinto
    labirinto = posicoesLivres linhas

-- A ordem cima, direita, baixo, esquerda é a ordem de exploração da BFS
vizinhas :: Posicao -> [Posicao]
vizinhas (linha, coluna) =
  [(linha - 1, coluna), (linha, coluna + 1), (linha + 1, coluna), (linha, coluna - 1)]

vizinhasLivres :: Labirinto -> Posicao -> [Posicao]
vizinhasLivres labirinto = filter (celulaLivre labirinto) . vizinhas

-- BFS: explora em camadas de distância, então o primeiro caminho que chega ao destino é mínimo
-- Recursão de cauda: a fila e o labirinto restante são acumuladores, novos a cada chamada
-- Cada item da fila leva o caminho até ele, ao contrário (o reverse acerta a ordem no fim)
buscar :: Posicao -> [(Posicao, [Posicao])] -> Labirinto -> Maybe [Posicao]
buscar _ [] _ = Nothing
buscar destino ((atual, caminho) : resto) restantes
  | atual == destino = Just (reverse caminho)
  -- Posição marcada ao entrar na fila (sai do conjunto restante), para entrar uma única vez
  | otherwise = buscar destino (resto ++ proximas) (foldr Set.delete restantes novas)
  where
    novas :: [Posicao]
    novas = vizinhasLivres restantes atual
    proximas :: [(Posicao, [Posicao])]
    proximas = map (\vizinha -> (vizinha, vizinha : caminho)) novas

-- A origem começa marcada: é o único item da fila e já sai do conjunto restante
buscarCaminho :: Labirinto -> Posicao -> Posicao -> Maybe [Posicao]
buscarCaminho labirinto origem destino =
  buscar destino [(origem, [origem])] (Set.delete origem labirinto)

-- Valida a entrada e, se for válida, busca o caminho
resolverLabirinto :: [String] -> Posicao -> Posicao -> Resultado
resolverLabirinto linhas origem destino =
  case validarEntrada linhas origem destino of
    Left motivo -> EntradaInvalida motivo
    Right labirinto ->
      case buscarCaminho labirinto origem destino of
        Nothing -> SemCaminho
        Just caminho -> CaminhoEncontrado caminho

textoPosicao :: Posicao -> String
textoPosicao (linha, coluna) = "(" ++ show linha ++ "," ++ show coluna ++ ")"

textoCaminho :: [Posicao] -> String
textoCaminho = intercalate " → " . map textoPosicao

-- Calculado a partir do caminho, para nunca ficar inconsistente
movimentos :: [Posicao] -> Int
movimentos caminho = length caminho - 1

-- O texto não termina em \n: a conferência compara o texto exato
textoResultado :: Resultado -> String
textoResultado (CaminhoEncontrado caminho) =
  "Resultado: Caminho encontrado\nCaminho: "
    ++ textoCaminho caminho
    ++ "\nMovimentos: "
    ++ show (movimentos caminho)
textoResultado SemCaminho = "Resultado: Sem caminho"
textoResultado (EntradaInvalida motivo) =
  "Resultado: Entrada inválida\nMotivo: " ++ motivo