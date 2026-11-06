# Reflexão - Etapa 06

**Tag:** `P4-ETAPA-06`

**Como mudou o raciocínio ao trocar "Que estado devo modificar?" por "Que transformação deve ser aplicada aos dados?"**

No C (imperativo/labirinto.c), cada passo da solução alterava variáveis: a fila, a matriz da busca, o contador de aprovados. No C# (poo/), o estado ficava dentro dos objetos, e só a busca o alterava. No Haskell (funcional/), nada muda: o programa é uma cadeia de funções que transformam as linhas do labirinto, a origem e o destino no texto da saída. O contrato, o algoritmo (BFS) e a saída continuam os mesmos, e as três versões imprimem o mesmo texto nos 15 casos.

## Identificação

| Item | Onde está |
|---|---|
| Funções puras | Todas as de Labirinto.hs e Casos.hs: nenhuma tem IO no tipo, e cada uma depende só dos parâmetros |
| Funções impuras | Só o main (Main.hs), a única função com IO no tipo |
| Dados imutáveis | Posicao, Labirinto (o conjunto das posições livres), Resultado, CasoTeste, livre, bloqueada e casosEtapa02; na busca, a fila e o conjunto restante nunca mudam, porque cada chamada recebe versões novas |
| Transformações de dados | posicoesLivres (texto → conjunto), validarEntrada (linhas → labirinto ou motivo), buscar (fila → caminho), resolverLabirinto (entrada → Resultado), textoResultado e textoDoCaso (valores → texto) |
| Funções de alta ordem | all, filter, map, foldr, concatMap e mapM_, no lugar dos laços; por exemplo, foldr aplica Set.delete a cada posição que entra na fila |
| Composição funcional | vizinhasLivres, textoCaminho, contarAprovados e putStr . textoDoCaso; resolverLabirinto encadeia validar → buscar → montar o resultado |
| Interação com o mundo externo | Só no main: hSetEncoding (codificação da saída), putStr (tela) e exitSuccess ou exitFailure (código de saída) |

## A busca

- **Imperativo e orientado a objetos:** um laço while alterava a fila e a matriz de antecessores, e eu precisava cuidar da ordem: marcar a célula antes de enfileirar, parar quando o destino saísse da fila e, no C, liberar a memória no fim. O caminho era reconstruído depois, de trás para frente.
- **Funcional:** o estado da busca virou parâmetro. Cada chamada de buscar recebe a fila e o labirinto restante e chama a si mesma com versões novas (recursão de cauda). Marcar uma posição é tirá-la do conjunto, e cada item da fila já leva o caminho até a sua posição: vizinha : caminho cria um caminho novo que reaproveita o anterior sem copiá-lo, o que só é seguro porque nada muda. No fim, basta inverter a lista.

## Validação e erros

- **Imperativo:** validar_entrada devolvia um código, e a busca confiava que a validação já tinha rodado.
- **Orientado a objetos:** os construtores lançavam exceção, tratada num único catch.
- **Funcional:** validarEntrada devolve um valor: Left com o motivo ou Right com o labirinto. As 7 regras viraram 7 guardas, na ordem da tabela 4.3, e a busca só recebe um labirinto que passou por elas. O erro virou um valor que o tipo obriga a tratar: sem passar pelo Right, não há labirinto para buscar.

## Efeitos e saída

- **Imperativo:** printf em 3 funções e escrita por ponteiro em 8; o texto era montado num buffer com anexar_texto.
- **Orientado a objetos:** Console em Programa e CasoTeste, e mutação da fila e da matriz dentro da busca.
- **Funcional:** até o texto da tela é montado por funções puras (Casos.hs), e o main só imprime. O compilador garante a separação: uma função sem IO no tipo não consegue imprimir.

## Laços

Os laços for e while sumiram. Onde o laço era "para cada elemento", entrou uma função de alta ordem, que diz o que fazer com cada elemento (all para validar, map para escrever o caminho, concatMap para desenhar a grade). Onde era "repetir até uma condição", entrou a recursão de cauda de buscar, que o compilador transforma num salto, como o while do C.

## O que ficou mais fácil e o que custou

- **Mais fácil:** como a mesma entrada dá sempre a mesma saída, cada caso virou uma equação. Ele é resolvido em quatro lugares (texto, conferência, resumo e código de saída), sempre com o mesmo resultado, e qualquer função pode ser testada sozinha no GHCi.
- **Custos:** a fila é uma lista, então juntar os novos itens no fim percorre a fila inteira; o conjunto responde em O(log n), contra O(1) da matriz; e resolver cada caso quatro vezes repete trabalho. Aceitei esses custos porque os casos são pequenos e o README não fixa metas de desempenho. 

## Conclusão

Pensar em "que estado modificar?" me fazia acompanhar a memória passo a passo e garantir a coerência pela ordem das alterações. Pensar em "que transformação aplicar?" me fez descrever cada etapa como uma função da entrada para a saída: linhas → labirinto → caminho → Resultado → texto. O código ficou menor, mas cada linha faz mais coisa e exige mais atenção para ler. O ganho é que nenhuma parte depende do que as outras fizeram antes: cada função pode ser entendida sozinha.