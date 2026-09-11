# Etapa 01 - Proposta e especificação do problema

**Tag:** `[P4-ETAPA-01]`

Este documento cobre os itens 3 a 8 da Etapa 01

## 3. Entradas

O sistema recebe três dados:

### 3.1 O labirinto

Uma grade retangular de M linhas por N colunas, com M >= 1 e N >= 1. Cada célula assume exatamente um de dois valores:

`.` - Célula livre  
`#` - Célula bloqueada

Todas as linhas têm exatamente N células. O labirinto não se altera durante a execução.

```
..###
#...#
###.#
.....
```

### 3.2 A posição de origem

Um par ordenado (linha, coluna) indicando onde o percurso começa.

### 3.3 A posição de destino

Um par ordenado (linha, coluna) indicando onde o percurso deve terminar.

## 4. Saídas

Toda execução produz exatamente um de três resultados possíveis:

### 4.1 Caminho encontrado

Existe ao menos um caminho válido da origem ao destino. A saída contém:

**Caminho** | A sequência completa e ordenada de posições visitadas, da origem ao destino, ambas inclusive.  
**Número de movimentos** | A quantidade de transições realizadas

Exemplo de saída (A forma de apresentar esses dados poderá variar):
```
Resultado: Caminho encontrado
Caminho: (0,0) → (0,1) → (1,1) → (1,2) → (1,3) → (2,3) → (3,3) → (3,4)
Movimentos: 7
```

### 4.2 Sem caminho

A entrada é válida, mas não existe nenhum caminho que ligue a origem ao destino respeitando as regras. A saída não contém caminho nem número de movimentos.

```
Resultado: Sem caminho
```

### 4.3 Entrada inválida

A entrada viola alguma das condições de validade definidas. A saída deve indicar o motivo da rejeição:

`Labirinto vazio` | O labirinto não possui dados  
`Linhas irregulares` | Nem todas as linhas possuem o mesmo número de células  
`Célula desconhecida` | Alguma célula tem valor diferente de livre ou bloqueada  
`Origem fora dos limites` | A posição de origem não corresponde a nenhuma célula do labirinto  
`Destino fora dos limites` | A posição de destino não corresponde a nenhuma célula do labirinto  
`Origem bloqueada` | A posição de origem corresponde a uma célula bloqueada  
`Destino bloqueado` | A posição de destino corresponde a uma célula bloqueada  

## 5. Regras do problema

### Movimentação
A partir de uma posição, são permitidos movimentos para as células vizinhas acima, abaixo, à esquerda e à direita. Movimentos diagonais não são permitidos.

Um movimento só é válido se a posição de destino estiver dentro dos limites do
labirinto e corresponder a uma célula livre. Todos os movimentos têm o mesmo custo,
de modo que o comprimento de um caminho é simplesmente o número de movimentos que
o compõem.

### Validade de entrada

A entrada é considerada válida quando o labirinto possui ao menos uma linha e uma
coluna, todas as linhas têm o mesmo número de células, e cada célula é livre ou
bloqueada. Além disso, as posições de origem e destino devem estar dentro dos
limites do labirinto e corresponder a células livres.

### Caminho

Um caminho é uma sequência de posições que começa na origem, termina no destino,
passa somente por células livres, e na qual cada posição consecutiva é alcançada
a partir da anterior por um movimento válido. Seu comprimento é o número de
movimentos.

### Caminho mínimo

Havendo caminho, o sistema retorna um caminho de comprimento mínimo, isto é, nenhum
outro caminho entre a mesma origem e o mesmo destino possui comprimento menor.

Pode existir mais de um caminho de comprimento mínimo para o mesmo par de posições.
Nesse caso, qualquer um deles é considerado uma resposta correta, desde que respeite
as regras de movimentação e possua o comprimento mínimo.

## 6. Casos de exemplo

### Exemplo 1 — Caminho único de comprimento mínimo
 
**Entrada**
 
```
Labirinto (4 x 5):
 
    01234
  0 ..###
  1 #...#
  2 ###.#
  3 .....
 
Origem:  (0,0)
Destino: (3,4)
```
 
**Saída esperada**
 
```
Resultado: Caminho encontrado
Caminho: (0,0) → (0,1) → (1,1) → (1,2) → (1,3) → (2,3) → (3,3) → (3,4)
Movimentos: 7
```
 
---
 
### Exemplo 2 — Múltiplos caminhos mínimos
 
**Entrada**
 
```
Labirinto (3 x 3):
 
    012
  0 ...
  1 ...
  2 ...
 
Origem:  (0,0)
Destino: (2,2)
```
 
**Saída esperada**
 
```
Resultado: Caminho encontrado
Caminho: (0,0) → (0,1) → (0,2) → (1,2) → (2,2)
Movimentos: 4
```
 
*Observação:* existem seis caminhos distintos de comprimento 4. Qualquer caminho mínimo válido é aceito como resposta.
 
---
 
### Exemplo 3 — Caminho com desvio 
 
**Entrada**
 
```
Labirinto (3 x 4):
 
    0123
  0 ....
  1 ##.#
  2 ....
 
Origem:  (0,0)
Destino: (2,0)
```
 
**Saída esperada**
 
```
Resultado: Caminho encontrado
Caminho: (0,0) → (0,1) → (0,2) → (1,2) → (2,2) → (2,1) → (2,0)
Movimentos: 6
```
 
---
 
### Exemplo 4 — Origem coincide com o destino
 
**Entrada**
 
```
Labirinto (3 x 3):
 
    012
  0 ...
  1 ##.
  2 ...
 
Origem:  (0,0)
Destino: (0,0)
```
 
**Saída esperada**
 
```
Resultado: Caminho encontrado
Caminho: (0,0)
Movimentos: 0
```
 
---
 
### Exemplo 5 — Destino inalcançável
 
**Entrada**
 
```
Labirinto (3 x 3):
 
    012
  0 ..#
  1 ###
  2 #..
 
Origem:  (0,0)
Destino: (2,2)
```
 
**Saída esperada**
 
```
Resultado: Sem caminho
```
 
---
 
### Exemplo 6 — Labirinto de uma única linha
 
**Entrada**
 
```
Labirinto (1 x 5):
 
    01234
  0 .....
 
Origem:  (0,0)
Destino: (0,4)
```
 
**Saída esperada**
 
```
Resultado: Caminho encontrado
Caminho: (0,0) → (0,1) → (0,2) → (0,3) → (0,4)
Movimentos: 4
```

## 7. Casos-limite

### Origem ou destino em célula bloqueada

Labirinto (2 x 2):

    01
  0 #.
  1 ..

Origem:  (0,0)
Destino: (1,1)

Resultado: Entrada invalida
Motivo: Origem bloqueada

A origem está em célula bloqueada, então a entrada é inválida — o sistema não deve
tentar buscar um caminho. O mesmo vale para o destino, com motivo "Destino Bloqueado".

---

### Coordenada fora dos limites

Labirinto (2 x 3):

    012
  0 ...
  1 ...

Origem:  (0,0)
Destino: (2,0)

Resultado: Entrada inválida
Motivo: Destino fora dos limites

A linha [2] não existe nesse labirinto. Coordenadas negativas seguem a mesma regra.

---

### Origem isolada por paredes

Labirinto (3 x 3):

    012
  0 .#.
  1 ##.
  2 ...

Origem:  (0,0)
Destino: (2,2)

Resultado: Sem caminho

A entrada é válida, mas a origem está cercada de paredes. Não há caminho possível,
o que é diferente de entrada inválida.

## 8. Restrições

Estão fora do escopo do projeto:

- **Leitura da entrada.** A forma como o labirinto e as posições chegam ao sistema
  (arquivo, entrada padrão ou dado declarado no próprio código) não faz parte do
  problema.
- **Interface gráfica.** Não haverá visualização interativa nem animação do
  percurso. A saída é textual.
- **Variações no modelo do labirinto.** Não haverá movimentos diagonais, custos ou
  pesos por célula, portais, chaves, nem mais de uma origem ou destino por execução.
- **Resultados adicionais.** O sistema retorna um único caminho. Não enumera nem
  conta todos os caminhos possíveis, e não gera labirintos.
- **Desempenho.** Não são estabelecidas metas de tempo de execução ou consumo de memória.

Esta especificação descreve o que o sistema deve produzir, e não como produzi-lo.
Nenhuma estratégia de busca ou estrutura de dados é prescrita ou proibida.