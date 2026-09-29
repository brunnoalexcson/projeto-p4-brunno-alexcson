# Comparação entre imperativo e POO - Etapa 05

**Tag:** `P4-ETAPA-05`

Comparação entre a versão imperativa, em C (imperativo/labirinto.c), e a orientada a objetos, em C# (poo/). As duas usam a mesma busca em largura, executam os mesmos 15 casos e imprimem o mesmo texto (15 de 15). O que muda é a modelagem.

## Aspectos

| Aspecto | Imperativo (C) | Orientado a objetos (C#) |
|---|---|---|
| Representação do estado | Structs só com dados e variáveis locais passadas por ponteiro. O estado da busca (mapa, fila e encontrou) é local de buscar_caminho, e o caminho é um vetor com um contador separado. | Atributos privados dentro dos objetos. A BuscaEmLargura guarda a fila e a matriz _anterior, e o Caminho guarda as posições e calcula os movimentos. |
| Mutabilidade | O mapa, a fila, o caminho e o texto da saída mudam por atribuição. Só o labirinto e a tabela de casos são const. | Os objetos não mudam depois de criados (set privado e readonly). Só _fila e _anterior mudam, dentro de BuscarCaminho. |
| Fluxo de controle | Explícito: cadeia de if/else if em validar_entrada, while e for na busca e um único ponto de saída para liberar a memória. | Os mesmos laços, mais exceção (throw no construtor, catch no Solucionador), polimorfismo (ToString) e retorno assim que o destino é encontrado. |
| Decomposição do problema | Por função, pelo que o programa faz: main e 27 funções em 7 grupos. | Por entidade, pelo que o problema é: 13 classes, uma por conceito. |
| Reutilização | Por chamada de função (dentro_dos_limites e celula_livre servem à validação e à busca). A fila e o mapa foram feitos à mão. | Por chamada, por herança (o ToString de Resultado e o Message de Exception) e pela biblioteca (Queue e List). |
| Manutenção | Depende da ordem das chamadas (buscar_caminho supõe que validar_entrada já rodou) e de cada malloc ter o seu free. | A mudança fica na classe dona do dado, e o compilador impede o acesso indevido (private e set privado). |
| Facilidade de extensão | Novo motivo: enum Motivo, validar_entrada e texto_do_motivo. Novo resultado: o if/else de resolver_labirinto. | Novo motivo: um throw no construtor. Novo resultado: uma subclasse de Resultado, sem mudar o CasoTeste. |
| Tratamento de erros | Código de retorno (enum Motivo), testado com if. A falta de memória encerra o programa. | Exceção lançada no construtor e tratada num único catch, no Solucionador, que devolve EntradaInvalida. |
| Efeitos colaterais | Sem variáveis globais. Escrita em parâmetros por ponteiro, printf em 3 funções e exit por falta de memória. | Parâmetros só de entrada e Console só em Programa e CasoTeste. O que muda fica dentro do objeto (_fila e _anterior). |
| Facilidade para testar | As funções puras (validação, mover) são fáceis de testar; as outras exigem preparar ponteiros e vetores. | Cada classe pode ser testada sozinha, e o Solucionador é uma caixa-preta (entrada → Resultado). |
| Organização do código | 1 arquivo (labirinto.c), com 622 linhas: tipos, protótipos, main e funções. | 13 arquivos, um por classe, nas pastas Dominio e Conferencia, com 578 linhas no total. |
| Complexidade | Poucas peças, mas com ponteiros, memória manual e vetores de tamanho fixo. | Mais peças e conceitos (herança, exceções, propriedades), mas sem ponteiros nem memória manual. Em troca, cria mais objetos no heap. |

Única diferença de comportamento encontrada, fora dos 15 casos: com um caractere acentuado numa linha (por exemplo, ".é" e ".."), o C responde "Linhas irregulares" e o C# responde "Célula desconhecida". Isso vem da linguagem, não do paradigma: strlen conta bytes, e Length conta caracteres.

## Perguntas

### 1. Qual problema ficou mais fácil de expressar de forma imperativa?

A busca em largura: em buscar_caminho, o algoritmo inteiro fica numa função, com while, for e atribuições. A validação em ordem também, numa única cadeia de if/else if.

### 2. Qual problema ficou mais fácil de expressar utilizando orientação a objetos?

Os três resultados: cada subclasse de Resultado escreve o próprio texto. Também a garantia de entrada válida (um objeto inválido nem é criado) e a memória, liberada pelo coletor de lixo.

### 3. Onde a orientação a objetos realmente trouxe vantagem?

Na segurança (os construtores validam, e o set privado impede alterar uma Posicao), no polimorfismo (CasoTeste só chama ToString, sem if sobre o tipo) e no código que deixou de existir (funções de fila e de mapa, malloc, free e limites fixos).

### 4. Em quais situações a utilização de objetos acrescentou complexidade desnecessária?

Solucionador e CasosEtapa02 são classes com um único método static, SemCaminho é uma classe só para um texto fixo, a entrada inválida precisou de duas classes (a exceção e o resultado) e cada passo da busca cria objetos novos no heap.

### 5. Que partes do problema praticamente não mudaram entre as duas implementações?

O contrato (entradas, saídas e ordem dos 7 motivos), o algoritmo (a mesma BFS, na mesma ordem de vizinhos), os 15 casos com conferência por texto e o código dentro dos métodos, que continua imperativo.

### 6. Que partes precisaram ser completamente remodeladas?

A validação (de código de retorno para exceção), a saída (de if/else num vetor de caracteres para a hierarquia Resultado), o labirinto (de struct para classe que se valida), a fila e o mapa (de malloc e free para Queue e coletor de lixo) e o caminho (de vetor e contador para o objeto Caminho).