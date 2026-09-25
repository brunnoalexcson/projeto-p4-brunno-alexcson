# Decisões de implementação

Etapa 03 - Implementação imperativa

**Tag:** `P4-ETAPA-03`

A implementação está em `imperativo/labirinto.c`, escrita em C. O programa resolve o problema da Etapa 01 (caminho mínimo em labirinto) com busca em largura (BFS) e valida a solução com os 15 casos de `testes/casos.md` (Etapa 02).

Os comentários no código são curtos e ficam só nos pontos de decisão. As explicações completas estão neste documento.

### Decisões principais

- **C:** comandos, variáveis e memória ficam explícitos, como pede o paradigma imperativo.
- **Busca em largura (BFS):** explora o labirinto em camadas de distância, então a primeira vez que chega ao destino é por um caminho mínimo.
- **Ordem dos vizinhos (cima, direita, baixo, esquerda):** qualquer ordem daria um caminho mínimo. Esta foi escolhida para reproduzir exatamente os caminhos de `testes/casos.md` nos casos com mais de um caminho mínimo.
- **Validação na ordem da tabela 4.3 do README:** para no primeiro erro. Essa ordem também evita acessos inválidos, porque os limites são testados antes de olhar a célula.
- **Labirinto só de leitura (`const`):** o problema define o labirinto como estático.
- **Fila em vetor:** um vetor com dois índices, `inicio` e `fim`. Cada célula é marcada ao entrar na fila e, por isso, entra no máximo uma vez. Então M × N posições bastam (M linhas e N colunas).
- **Mapa da busca alocado em execução:** o tamanho do labirinto só é conhecido quando o programa roda.
- **Casos declarados no código:** quem avalia só executa o programa, sem digitar nada.
- **Resultado montado em texto antes de ser impresso:** assim ele pode ser comparado com a saída esperada usando `strcmp`. A função `anexar_texto` impede que o texto ultrapasse o tamanho do vetor.
- **Console em UTF-8 no Windows:** sem isso, a seta `→` e os acentos aparecem embaralhados.

### Estados mantidos

| Estado | Onde | O que guarda |
|---|---|---|
| `mapa` | `buscar_caminho` | distância de cada célula até a origem e de qual célula a busca veio |
| `fila` | `buscar_caminho` | posições que ainda serão exploradas |
| `encontrou` | `buscar_caminho` | se o destino já foi alcançado |
| `caminho` | `resolver_labirinto` | posições do caminho encontrado |
| `saida` | `executar_caso` | texto do resultado de um caso |
| `aprovados` | `main` | quantos casos conferem |

O labirinto não é estado mutável: ele só é lido.

### Operações que modificam estado

- `criar_mapa` marca todas as células como não visitadas.
- `buscar_caminho` marca a origem com distância 0 e cada vizinha alcançada com a distância da célula atual + 1 e a célula de onde veio. Ao chegar ao destino, muda `encontrou` para verdadeiro.
- `enfileirar` grava a posição no vetor e avança `fim`; `desenfileirar` avança `inicio`.
- `reconstruir_caminho` preenche o vetor `caminho`.
- `anexar_texto` acrescenta texto ao fim de `saida`.
- `main` soma 1 em `aprovados` a cada caso que confere.

Todas essas mudanças são atribuições explícitas.

### Efeitos colaterais

Pela Aula 8, um subprograma tem efeito colateral quando altera algo fora dele, além de devolver um valor: variáveis globais, parâmetros por referência ou entrada/saída.

- **Variáveis globais:** nenhuma. Todo estado é passado por parâmetro. A tabela de casos é `static const` dentro de `obter_casos_etapa02`: só leitura e visível só ali.
- **Escrita em parâmetros por ponteiro:** `enfileirar` e `desenfileirar` (`fila`), `buscar_caminho` (`movimentos`), `reconstruir_caminho` (`caminho`), `anexar_texto`, `escrever_caminho` e `resolver_labirinto` (`saida`), `obter_casos_etapa02` (`total_casos`).
- **Impressão na tela (`printf`):** só em `main`, `executar_caso` e `imprimir_entrada`. Validação, busca e montagem do texto não imprimem nada.
- **Memória:** `mapa`, `fila` e `caminho` ficam no heap. Cada um é criado e liberado dentro da mesma função (`mapa` e `fila` em `buscar_caminho`, `caminho` em `resolver_labirinto`) e só é acessado durante essa chamada.
- **Encerramento:** se faltar memória, `alocar_memoria` mostra um erro e encerra o programa.
- **Console:** no Windows, `configurar_console` muda a codificação do console para UTF-8.

**Funções sem efeito colateral:** `mesma_posicao`, `mover`, `montar_labirinto`, `texto_do_motivo` e as de validação (`validar_entrada`, `labirinto_vazio`, `linhas_regulares`, `celulas_conhecidas`, `dentro_dos_limites`, `celula_livre`) só calculam e devolvem um valor. Como o labirinto nunca muda, a mesma entrada dá sempre a mesma resposta. `fila_vazia` também não altera nada, mas não é pura: a resposta depende do estado atual da fila.

**Comando e consulta juntos :** `desenfileirar`, `buscar_caminho` e `obter_casos_etapa02` alteram algo e também devolvem um valor.

### Estruturas de controle

- **`if / else if`:** `validar_entrada` testa as 7 regras em ordem e para na primeira que falhar.
- **`switch`:** `mover` (direção → deslocamento) e `texto_do_motivo` (motivo → texto).
- **`while`:** laço principal da BFS, repetido enquanto o destino não foi encontrado e a fila não está vazia.
- **`for`:** percorre as 4 direções, as linhas e colunas do labirinto, o caminho (de trás para frente) e os casos de teste.

Não há recursão: a busca é feita só com laços.

### Organização dos subprogramas

O arquivo segue a ordem: constantes e tipos, protótipos, `main` e as funções. São 27 funções, cada uma com uma tarefa só, agrupadas assim:

| Grupo | Funções |
|---|---|
| Memória | `alocar_memoria` |
| Fila | `criar_fila`, `fila_vazia`, `enfileirar`, `desenfileirar`, `liberar_fila` |
| Mapa da busca | `criar_mapa`, `liberar_mapa` |
| Labirinto e validação | `montar_labirinto`, `labirinto_vazio`, `linhas_regulares`, `celulas_conhecidas`, `dentro_dos_limites`, `celula_livre`, `validar_entrada`, `texto_do_motivo` |
| Busca (BFS) | `mesma_posicao`, `mover`, `buscar_caminho`, `reconstruir_caminho` |
| Montagem da saída | `anexar_texto`, `escrever_caminho`, `resolver_labirinto` |
| Casos de teste | `configurar_console`, `obter_casos_etapa02`, `imprimir_entrada`, `executar_caso` |

### Parâmetros

- **Entrada por valor** (a função recebe uma cópia): `Posicao`, `Direcao`, `Motivo` e `CasoTeste`.
- **Entrada por ponteiro `const`** (só leitura, sem copiar a estrutura): `const Labirinto *lab`.
- **Saída** (a função escreve no endereço recebido): `int *movimentos`, `Posicao caminho[]` e `int *total_casos`.
- **Entrada e saída** (a função lê e altera): `Fila *fila` em `enfileirar` e `char saida[]` em `anexar_texto`.

### Por que a solução é predominantemente imperativa

- O programa é uma sequência de comandos que mudam variáveis por atribuição.
- O estado da busca (`mapa` e `fila`) é criado, alterado passo a passo e liberado manualmente.
- O fluxo é controlado por laços (`while`, `for`) e desvios (`if`, `switch`), sem recursão.
- Os dados ficam em `struct` (só registros) e o comportamento em funções separadas, que recebem o estado por parâmetro. Não há classes, métodos nem variáveis globais.
- A memória é gerenciada à mão, com `malloc` e `free`.

### Validação com os casos da Etapa 02

- Os 15 casos de `testes/casos.md` estão na tabela de `obter_casos_etapa02`, com a entrada e a saída esperada.
- Para cada caso, o programa calcula a saída, mostra na tela e compara com a esperada, texto a texto. A saída esperada só é usada para comparar (e é mostrada quando um caso falha).
- Os 7 motivos de entrada inválida estão implementados
- Resultado: **15 de 15 casos conferem** e o programa termina com código 0 (ou 1, se algum caso falhar).