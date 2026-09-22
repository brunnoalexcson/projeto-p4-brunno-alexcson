# Etapa 02 - Contrato semântico e testes

**Tag:** `[P4-ETAPA-02]`

Os casos são independentes de linguagem e de paradigma. Os mesmos casos serão usados para validar as quatro implementações.

Os casos definem o que o sistema deve produzir, não como.

Cada caso possui, nesta ordem: **Identificador**, **Entrada**, **Saída esperada** e **Descrição**. Os identificadores seguem o padrão `CN-xx` (casos normais), `CL-xx` (casos-limite) e `CI-xx` (entrada inválida).

## Casos normais

### CN-01 - Caminho mínimo único

**Identificador:** `CN-01`

**Entrada**
```
    01234
  0 ..###
  1 #...#
  2 ###.#
  3 .....
Origem: (0,0)   Destino: (3,4)
```

**Saída esperada**
```
Resultado: Caminho encontrado
Caminho: (0,0) → (0,1) → (1,1) → (1,2) → (1,3) → (2,3) → (3,3) → (3,4)
Movimentos: 7
```

**Descrição:** único caminho de comprimento mínimo entre cantos opostos.

### CN-02 - Vários caminhos mínimos

**Identificador:** `CN-02`

**Entrada**
```
    012
  0 ...
  1 ...
  2 ...
Origem: (0,0)   Destino: (2,2)
```

**Saída esperada**
```
Resultado: Caminho encontrado
Caminho: (0,0) → (0,1) → (0,2) → (1,2) → (2,2)
Movimentos: 4
```

**Descrição:** grade sem paredes, com 6 caminhos mínimos. Qualquer um é aceito.

### CN-03 - Desvio por uma única passagem

**Identificador:** `CN-03`

**Entrada**
```
    0123
  0 ....
  1 ##.#
  2 ....
Origem: (0,0)   Destino: (2,0)
```

**Saída esperada**
```
Resultado: Caminho encontrado
Caminho: (0,0) → (0,1) → (0,2) → (1,2) → (2,2) → (2,1) → (2,0)
Movimentos: 6
```

**Descrição:** a parede da linha 1 obriga o percurso a se afastar do destino e passar pela abertura em `(1,2)`.

### CN-04 - Percurso no sentido inverso

**Identificador:** `CN-04`

**Entrada**
```
    01234
  0 ..###
  1 #...#
  2 ###.#
  3 .....
Origem: (3,4)   Destino: (0,0)
```

**Saída esperada**
```
Resultado: Caminho encontrado
Caminho: (3,4) → (3,3) → (2,3) → (1,3) → (1,2) → (1,1) → (0,1) → (0,0)
Movimentos: 7
```

**Descrição:** mesmo labirinto do CN-01 com origem e destino trocados. O caminho usa movimentos para cima e para a esquerda.

### CN-05 - Labirinto em serpentina

**Identificador:** `CN-05`

**Entrada**
```
    01234
  0 .....
  1 ####.
  2 .....
  3 .####
  4 .....
Origem: (0,0)   Destino: (4,4)
```

**Saída esperada**
```
Resultado: Caminho encontrado
Caminho: (0,0) → (0,1) → (0,2) → (0,3) → (0,4) → (1,4) → (2,4) → (2,3) → (2,2) → (2,1) → (2,0) → (3,0) → (4,0) → (4,1) → (4,2) → (4,3) → (4,4)
Movimentos: 16
```

**Descrição:** as paredes forçam um percurso longo, que atravessa a grade de um lado a outro várias vezes.

### CN-06 - Escolha do menor entre dois percursos

**Identificador:** `CN-06`

**Entrada**
```
    0123456
  0 .......
  1 .#####.
  2 .......
Origem: (0,1)   Destino: (2,1)
```

**Saída esperada**
```
Resultado: Caminho encontrado
Caminho: (0,1) → (0,0) → (1,0) → (2,0) → (2,1)
Movimentos: 4
```

**Descrição:** a parede central pode ser contornada pela esquerda (4 movimentos) ou pela direita (12 movimentos). Deve ser retornado o percurso mais curto.

### CN-07 - Contorno de obstáculo

**Identificador:** `CN-07`

**Entrada**
```
    01234
  0 .....
  1 ..#..
  2 .....
Origem: (1,0)   Destino: (1,4)
```

**Saída esperada**
```
Resultado: Caminho encontrado
Caminho: (1,0) → (0,0) → (0,1) → (0,2) → (0,3) → (0,4) → (1,4)
Movimentos: 6
```

**Descrição:** origem e destino na mesma linha, separados pela parede em `(1,2)`. Há 8 caminhos mínimos, por cima ou por baixo. Qualquer um é aceito.

### CN-08 - Labirinto com becos sem saída

**Identificador:** `CN-08`

**Entrada**
```
    01234567
  0 ..#.....
  1 #.#.###.
  2 #...#...
  3 ###.#.##
  4 #...#...
  5 #.###.#.
  6 #....##.
Origem: (0,0)   Destino: (6,7)
```

**Saída esperada**
```
Resultado: Caminho encontrado
Caminho: (0,0) → (0,1) → (1,1) → (2,1) → (2,2) → (2,3) → (1,3) → (0,3) → (0,4) → (0,5) → (0,6) → (0,7) → (1,7) → (2,7) → (2,6) → (2,5) → (3,5) → (4,5) → (4,6) → (4,7) → (5,7) → (6,7)
Movimentos: 21
```

**Descrição:** labirinto maior com ramificações sem saída. Nenhum beco pode aparecer no caminho.

### CN-09 - Destino inalcançável

**Identificador:** `CN-09`

**Entrada**
```
    012
  0 ..#
  1 ###
  2 #..
Origem: (0,0)   Destino: (2,2)
```

**Saída esperada**
```
Resultado: Sem caminho
```

**Descrição:** entrada válida em que a linha 1 bloqueada separa origem e destino.

### CN-10 - Destino cercado por paredes

**Identificador:** `CN-10`

**Entrada**
```
    01234
  0 .....
  1 .###.
  2 .#.#.
  3 .###.
  4 .....
Origem: (0,0)   Destino: (2,2)
```

**Saída esperada**
```
Resultado: Sem caminho
```

**Descrição:** o destino é livre, mas está totalmente cercado. A entrada é válida, então o resultado é `Sem caminho`, e não entrada inválida.

## Casos-limite

### CL-01 - Origem igual ao destino

**Identificador:** `CL-01`

**Entrada**
```
    012
  0 ...
  1 ##.
  2 ...
Origem: (0,0)   Destino: (0,0)
```

**Saída esperada**
```
Resultado: Caminho encontrado
Caminho: (0,0)
Movimentos: 0
```

**Descrição:** o caminho tem uma única posição e zero movimentos.

### CL-02 - Labirinto de uma única linha

**Identificador:** `CL-02`

**Entrada**
```
    01234
  0 .....
Origem: (0,0)   Destino: (0,4)
```

**Saída esperada**
```
Resultado: Caminho encontrado
Caminho: (0,0) → (0,1) → (0,2) → (0,3) → (0,4)
Movimentos: 4
```

**Descrição:** menor altura possível (M = 1). Só existem movimentos horizontais.

### CL-03 - Ligação apenas pela diagonal

**Identificador:** `CL-03`

**Entrada**
```
    01
  0 .#
  1 #.
Origem: (0,0)   Destino: (1,1)
```

**Saída esperada**
```
Resultado: Sem caminho
```

**Descrição:** origem e destino são livres, mas só se tocam pela diagonal. Como movimentos diagonais não são permitidos, não há caminho.

## Casos de entrada inválida

### CI-01 - Origem bloqueada

**Identificador:** `CI-01`

**Entrada**
```
    01
  0 #.
  1 ..
Origem: (0,0)   Destino: (1,1)
```

**Saída esperada**
```
Resultado: Entrada inválida
Motivo: Origem bloqueada
```

**Descrição:** a origem está em uma parede. O sistema não deve procurar caminho.

### CI-02 - Destino fora dos limites

**Identificador:** `CI-02`

**Entrada**
```
    012
  0 ...
  1 ...
Origem: (0,0)   Destino: (2,0)
```

**Saída esperada**
```
Resultado: Entrada inválida
Motivo: Destino fora dos limites
```

**Descrição:** o labirinto tem as linhas 0 e 1, e o destino aponta para a linha 2, que não existe.