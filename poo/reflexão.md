# Reflexão - Etapa 04

**Tag:** `P4-ETAPA-04`

**Como meu modelo mudou ao passar do paradigma imperativo para o orientado a objetos?**

No C (imperativo/labirinto.c), organizei o código pelo que ele **faz**: diversas funções que recebem structs e passam o estado de uma para outra. No C# (poo/), organizei pelo que o problema **é**: cada conceito do README virou uma classe que guarda os próprios dados e responde por eles. O contrato, o algoritmo (BFS) e a saída são os mesmos; as duas versões imprimem exatamente o mesmo texto nos 15 casos.

## Representação do estado

- **Imperativo:** o estado ficava em variáveis locais e era passado por ponteiro. O caminho era um vetor e um contador separados, que o chamador precisava manter coerentes.
- **Orientado a objetos:** o estado fica dentro do objeto. A fila e a matriz de antecessores são atributos de BuscaEmLargura; Caminho guarda as posições e calcula Movimentos(), então não há como ficar inconsistente.
- Quase tudo é imutável depois de criado. O único estado que muda é o da busca (_fila e _anterior), e só dentro de BuscarCaminho.

## Responsabilidades

- **Imperativo:** a lógica ficava centralizada em funções como validar_entrada e resolver_labirinto, que conheciam todos os dados.
- **Orientado a objetos:** cada classe tem uma responsabilidade. Labirinto valida a grade, BuscaEmLargura valida origem e destino e busca o caminho, cada Resultado sabe escrever o próprio texto e CasoTeste cuida da conferência. O domínio não imprime nada.
- A validação saiu de uma função única e foi para o construtor do objeto dono do dado: um objeto inválido nem chega a existir.

## Relacionamento entre componentes

- **Imperativo:** funções chamando funções, ligadas pelos dados que recebiam.
- **Orientado a objetos:** os objetos colaboram por chamadas de método. Há três tipos de relação:
  - **herança:** CaminhoEncontrado, SemCaminho e EntradaInvalida são tipos de Resultado;
  - **composição:** Caminho tem sua lista, Labirinto tem sua matriz, CaminhoEncontrado tem um Caminho;
  - **agregação:** BuscaEmLargura usa um Labirinto que existe fora dela.
- Usei herança só onde há "é um" de verdade. Caminho tem uma lista, mas não é uma lista: herdar de List exporia Add e Remove, e um caminho pronto não pode mudar.

## Reutilização

- **Imperativo:** reutilização por chamada de função (dentro_dos_limites e celula_livre serviam à validação e à busca), mas a fila e o mapa foram escritos à mão.
- **Orientado a objetos:**
  - por chamada: CelulaLivre serve à validação da busca e à vizinhança;
  - por herança: as três subclasses usam o ToString() de Resultado, e a exceção usa o Message de Exception;
  - pela biblioteca: Queue substituiu as cinco funções de fila; a string cresce conforme a necessidade, e o vetor de linhas de cada caso tem o tamanho dos dados, o que eliminou os limites fixos (TAM_SAIDA, MAX_LINHAS_CASO).

## Encapsulamento

- **Imperativo:** qualquer função podia ler e alterar os campos de uma struct, e as pré-condições dependiam da ordem das chamadas: buscar_caminho confiava que validar_entrada já tinha sido chamada, e celula_livre, que os limites já tinham sido testados.
- **Orientado a objetos:** atributos private, propriedades com set privado e métodos públicos só onde é útil. Quem usa o Labirinto pergunta CelulaLivre(posicao) sem saber que ele é uma matriz de bool. Como ninguém de fora altera uma Posicao depois da validação, a garantia do construtor continua valendo durante a busca.

## Extensão do sistema

- **Imperativo:** um novo motivo de entrada inválida mexia no enum Motivo, no switch de texto_do_motivo e em validar_entrada; um novo tipo de resultado mexia no if/else de resolver_labirinto.
- **Orientado a objetos:** um novo motivo é mais um throw no construtor do objeto dono do dado. Um novo tipo de resultado é uma nova subclasse de Resultado, e CasoTeste não muda, porque só chama ToString() (polimorfismo).

## Conclusão

O problema e a solução continuam os mesmos; o que mudou foi onde cada coisa mora. No imperativo, dados e comportamento eram separados e eu garantia a coerência pela ordem das chamadas. No orientado a objetos, cada objeto garante a própria coerência. O custo é ter mais arquivos e classes para um problema pequeno; o ganho é que cada parte pode ser entendida e alterada sozinha.