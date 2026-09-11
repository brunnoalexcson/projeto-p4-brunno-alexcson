# Etapa 01 - Proposta e especificação do problema

**Tag:** `[P4-ETAPA-01]`

Este documento cobre os itens 1, 2, 9 e 10 da Etapa 01

## 1. Descrição do problema

O problema escolhido para ser trabalhado durante o semestre foi o de encontrar um caminho em um labirinto.

O labirinto é uma grade retangular de células, e cada célula pode ser livre ou bloqueada. Dadas uma célula de origem e uma célula de destino, deseja-se saber se é possível ir da origem ao destino percorrendo apenas células livres e, em caso afirmativo, qual é o percurso mais curto.

O problema pertence à classe de problemas de busca de caminho em espaço discreto.

## 2. Objetivo

O sistema deverá ser capaz de:

1. **Receber** a descrição de um labirinto, uma posição de origem e uma posição de destino.
2. **Validar** essa entrada, rejeitando descrições inconsistentes.
3. **Determinar** se existe ao menos um percurso da origem até o destino que respeite as regras de movimentação.
4. **Produzir**, quando o percurso existir, o percurso de menor número de movimentos.
5. **Informar** explicitamente quando não existir percurso possível, distinguindo esse resultado de uma entrada inválida.

## 9. Principais conceitos do domínio

Os conceitos abaixo são descritos como elementos do problema.

### Labirinto
A grade retangular de células, com `M` linhas e `N` colunas, `M` >= 1 e `N` >= 1. Todas as linhas têm o mesmo comprimento. O labirinto é estático: não se altera durante a execução.

### Célula
A unidade indivisível do labirinto. Uma célula está em exatamente um de dois estados: livre ou bloqueada. Não há estados intermediários, custos ou propriedades adicionais.

### Posição
A identificação de uma célula dentro do labirinto, dada por um par ordenado (linha, coluna). A posição localiza.

### Origem e destino
Duas posições designadas na entrada. A origem é onde o percurso começa e o destino é onde deve terminar. Não há exigência de que sejam distintas.

### Movimento
A transição de uma posição para outra. São permitidos quatro movimentos, correspondentes às direções cima, baixo, esquerda e direita. 

### Vizinhança
O conjunto de posições alcançáveis a partir de uma posição por um único movimento. Uma posição na borda tem vizinhança menor, pois movimentos que sairiam da grade não existem.

### Caminho
Uma sequência de posições em que a primeira é a origem, a última é o destino, cada posição é livre, e cada par consecutivo está relacionado por um movimento válido. O comprimento de um caminho é o número de movimentos que ele teve.

### Caminho mínimo
Um caminho cujo comprimento é menor ou igual ao de qualquer outro caminho entre as mesmas origem e destino. Pode haver vários caminhos mínimos distintos para o mesmo par de posições.

### Resultado
O desfecho de uma execução, que assume exatamente um de três valores: caminho encontrado, caminho inexistente ou entrada inválida. Os três são mutuamente exclusivos e cobrem todos os casos

## 10. Adequação aos quatro paradigmas
O problema permite comparar diferentes formas de representar o labirinto, controlar a exploração das posições e construir o caminho mínimo.  
- Imperativo: permite trabalhar com estado explícito e atualização das informações de busca.
- Orientado a Objetos: permite organizar os conceitos e as responsabilidades relacionados ao labirinto.
- Funcional: permite expressar a exploração por funções e estruturas imutáveis, produzindo novos estados a partir dos anteriores.
- Lógico: permite representar células livres, movimentos válidos e caminhos por fatos e regras.

As quatro versões deverão respeitar as mesmas entradas, saídas e regras, embora possam organizar a solução de maneiras diferentes. A modelagem nos paradigmas funcional e lógico será aprofundada conforme o avanço da disciplina.