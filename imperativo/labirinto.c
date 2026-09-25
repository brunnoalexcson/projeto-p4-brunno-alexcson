// Projeto P4 - Caminho mínimo em labirinto - Implementação imperativa [P4-ETAPA-03]
// Executa os 15 casos de testes/casos.md, declarados no próprio código.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
#include <windows.h>
#endif

#define LIVRE           '.'
#define BLOQUEADA       '#'
#define NAO_VISITADA    (-1)
#define TAM_SAIDA       4096
#define MAX_LINHAS_CASO 10

typedef struct {
    int linha;
    int coluna;
} Posicao;

// A ordem dos valores é a ordem de exploração da BFS
typedef enum {
    CIMA,
    DIREITA,
    BAIXO,
    ESQUERDA
} Direcao;

// A ordem segue a tabela 4.3 do README
typedef enum {
    MOTIVO_NENHUM,
    MOTIVO_LABIRINTO_VAZIO,
    MOTIVO_LINHAS_IRREGULARES,
    MOTIVO_CELULA_DESCONHECIDA,
    MOTIVO_ORIGEM_FORA,
    MOTIVO_DESTINO_FORA,
    MOTIVO_ORIGEM_BLOQUEADA,
    MOTIVO_DESTINO_BLOQUEADO
} Motivo;

// O labirinto é estático: só é lido, nunca alterado
typedef struct {
    const char **linhas;
    int total_linhas;
    int total_colunas;
} Labirinto;

// Estado da busca para cada célula
typedef struct {
    int distancia;       // NAO_VISITADA enquanto a busca não chegou
    Posicao anterior;    // de onde a busca veio (para reconstruir o caminho)
} InfoBusca;

// Fila em vetor: entra na posição fim, sai da posição inicio
typedef struct {
    Posicao *itens;
    int inicio;
    int fim;
} Fila;

typedef struct {
    const char *id;
    const char *titulo;
    const char *linhas[MAX_LINHAS_CASO];
    int total_linhas;
    Posicao origem;
    Posicao destino;
    const char *saida_esperada;
} CasoTeste;

// Memória
void *alocar_memoria(size_t bytes);

// Fila em vetor
Fila criar_fila(int capacidade);
bool fila_vazia(const Fila *fila);
void enfileirar(Fila *fila, Posicao posicao);
Posicao desenfileirar(Fila *fila);
void liberar_fila(Fila *fila);

// Mapa da busca
InfoBusca **criar_mapa(int total_linhas, int total_colunas);
void liberar_mapa(InfoBusca **mapa, int total_linhas);

// Labirinto e validação
Labirinto montar_labirinto(const char *linhas[], int total_linhas);
bool labirinto_vazio(const Labirinto *lab);
bool linhas_regulares(const Labirinto *lab);
bool celulas_conhecidas(const Labirinto *lab);
bool dentro_dos_limites(const Labirinto *lab, Posicao posicao);
bool celula_livre(const Labirinto *lab, Posicao posicao);
Motivo validar_entrada(const Labirinto *lab, Posicao origem, Posicao destino);
const char *texto_do_motivo(Motivo motivo);

// Busca do caminho (BFS)
bool mesma_posicao(Posicao a, Posicao b);
Posicao mover(Posicao posicao, Direcao direcao);
bool buscar_caminho(const Labirinto *lab, Posicao origem, Posicao destino, Posicao caminho[], int *movimentos);
void reconstruir_caminho(InfoBusca **mapa, Posicao destino, Posicao caminho[]);

// Montagem da saída
void anexar_texto(char saida[], int capacidade, const char texto[]);
void escrever_caminho(const Posicao caminho[], int movimentos, char saida[], int capacidade);
void resolver_labirinto(const Labirinto *lab, Posicao origem, Posicao destino, char saida[], int capacidade);

// Casos de teste
void configurar_console(void);
const CasoTeste *obter_casos_etapa02(int *total_casos);
void imprimir_entrada(const Labirinto *lab, Posicao origem, Posicao destino);
bool executar_caso(CasoTeste caso);

int main(void) {
    const CasoTeste *casos;
    int total_casos = 0;
    int aprovados = 0;
    int i;

    configurar_console();
    casos = obter_casos_etapa02(&total_casos);

    for (i = 0; i < total_casos; i++) {
        if (executar_caso(casos[i])) {
            aprovados = aprovados + 1;
        }
    }

    printf("==================================================\n");
    printf("Resumo: %d de %d casos conferem com testes/casos.md\n",
           aprovados, total_casos);

    if (aprovados == total_casos) {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}

// Memória

// Único ponto de alocação: se faltar memória, encerra o programa
void *alocar_memoria(size_t bytes) {
    void *bloco;

    bloco = malloc(bytes);
    if (bloco == NULL) {
        fprintf(stderr, "Erro: memória insuficiente.\n");
        exit(EXIT_FAILURE);
    }
    return bloco;
}

// Fila em vetor

Fila criar_fila(int capacidade) {
    Fila fila;

    fila.itens = (Posicao *) alocar_memoria((size_t) capacidade * sizeof(Posicao));
    fila.inicio = 0;
    fila.fim = 0;
    return fila;
}

bool fila_vazia(const Fila *fila) {
    return fila->inicio == fila->fim;
}

// Inserir no fim da fila
void enfileirar(Fila *fila, Posicao posicao) {
    fila->itens[fila->fim] = posicao;
    fila->fim = fila->fim + 1;
}

// Remove do início da fila; só é chamada com a fila não vazia
Posicao desenfileirar(Fila *fila) {
    Posicao removida;

    removida = fila->itens[fila->inicio];
    fila->inicio = fila->inicio + 1;
    return removida;
}

void liberar_fila(Fila *fila) {
    free(fila->itens);
}

// Mapa da busca: matriz M x N alocada em execução

InfoBusca **criar_mapa(int total_linhas, int total_colunas) {
    InfoBusca **mapa;
    int linha;
    int coluna;

    mapa = (InfoBusca **) alocar_memoria((size_t) total_linhas * sizeof(InfoBusca *));
    for (linha = 0; linha < total_linhas; linha++) {
        mapa[linha] = (InfoBusca *) alocar_memoria((size_t) total_colunas * sizeof(InfoBusca));
        for (coluna = 0; coluna < total_colunas; coluna++) {
            mapa[linha][coluna].distancia = NAO_VISITADA;
            mapa[linha][coluna].anterior.linha = -1;
            mapa[linha][coluna].anterior.coluna = -1;
        }
    }
    return mapa;
}

// Libera as linhas antes do vetor de ponteiros
void liberar_mapa(InfoBusca **mapa, int total_linhas) {
    int linha;

    for (linha = 0; linha < total_linhas; linha++) {
        free(mapa[linha]);
    }
    free(mapa);
}

// Labirinto e validação

// O labirinto só aponta para as linhas, não as copia
Labirinto montar_labirinto(const char *linhas[], int total_linhas) {
    Labirinto lab;

    lab.linhas = linhas;
    lab.total_linhas = total_linhas;
    if (total_linhas > 0) {
        lab.total_colunas = (int) strlen(linhas[0]);
    } else {
        lab.total_colunas = 0;
    }
    return lab;
}

bool labirinto_vazio(const Labirinto *lab) {
    bool vazio = true;
    int linha;

    for (linha = 0; linha < lab->total_linhas; linha++) {
        if ((int) strlen(lab->linhas[linha]) > 0) {
            vazio = false;
        }
    }
    return vazio;
}

bool linhas_regulares(const Labirinto *lab) {
    bool regulares = true;
    int linha;

    for (linha = 0; linha < lab->total_linhas; linha++) {
        if ((int) strlen(lab->linhas[linha]) != lab->total_colunas) {
            regulares = false;
        }
    }
    return regulares;
}

bool celulas_conhecidas(const Labirinto *lab) {
    bool conhecidas = true;
    int linha;
    int coluna;
    char celula;

    for (linha = 0; linha < lab->total_linhas; linha++) {
        for (coluna = 0; coluna < lab->total_colunas; coluna++) {
            celula = lab->linhas[linha][coluna];
            if (celula != LIVRE && celula != BLOQUEADA) {
                conhecidas = false;
            }
        }
    }
    return conhecidas;
}

bool dentro_dos_limites(const Labirinto *lab, Posicao posicao) {
    return posicao.linha >= 0 && posicao.linha < lab->total_linhas
        && posicao.coluna >= 0 && posicao.coluna < lab->total_colunas;
}

bool celula_livre(const Labirinto *lab, Posicao posicao) {
    return lab->linhas[posicao.linha][posicao.coluna] == LIVRE;
}

// Devolve o primeiro motivo de invalidade, na ordem da tabela 4.3 do README.
// A ordem também evita acessos inválidos: limites são testados antes das células.
Motivo validar_entrada(const Labirinto *lab, Posicao origem, Posicao destino) {
    Motivo motivo;

    if (labirinto_vazio(lab)) {
        motivo = MOTIVO_LABIRINTO_VAZIO;
    } else if (!linhas_regulares(lab)) {
        motivo = MOTIVO_LINHAS_IRREGULARES;
    } else if (!celulas_conhecidas(lab)) {
        motivo = MOTIVO_CELULA_DESCONHECIDA;
    } else if (!dentro_dos_limites(lab, origem)) {
        motivo = MOTIVO_ORIGEM_FORA;
    } else if (!dentro_dos_limites(lab, destino)) {
        motivo = MOTIVO_DESTINO_FORA;
    } else if (!celula_livre(lab, origem)) {
        motivo = MOTIVO_ORIGEM_BLOQUEADA;
    } else if (!celula_livre(lab, destino)) {
        motivo = MOTIVO_DESTINO_BLOQUEADO;
    } else {
        motivo = MOTIVO_NENHUM;
    }
    return motivo;
}

const char *texto_do_motivo(Motivo motivo) {
    switch (motivo) {
        case MOTIVO_LABIRINTO_VAZIO:     
            return "Labirinto vazio";
        case MOTIVO_LINHAS_IRREGULARES:  
            return "Linhas irregulares";
        case MOTIVO_CELULA_DESCONHECIDA: 
            return "Célula desconhecida";
        case MOTIVO_ORIGEM_FORA:         
            return "Origem fora dos limites";
        case MOTIVO_DESTINO_FORA:        
            return "Destino fora dos limites";
        case MOTIVO_ORIGEM_BLOQUEADA:    
            return "Origem bloqueada";
        case MOTIVO_DESTINO_BLOQUEADO:   
            return "Destino bloqueado";
        default:                         
            return "";
    }
}

// Busca do caminho (BFS)

bool mesma_posicao(Posicao a, Posicao b) {
    return a.linha == b.linha && a.coluna == b.coluna;
}

Posicao mover(Posicao posicao, Direcao direcao) {
    Posicao vizinha;

    vizinha = posicao;
    switch (direcao) {
        case CIMA:
            vizinha.linha = vizinha.linha - 1;
            break;
        case DIREITA:
            vizinha.coluna = vizinha.coluna + 1;
            break;
        case BAIXO:
            vizinha.linha = vizinha.linha + 1;
            break;
        case ESQUERDA:
            vizinha.coluna = vizinha.coluna - 1;
            break;
    }
    return vizinha;
}

// BFS: explora em camadas de distância, então o primeiro caminho que chega ao destino é mínimo.
bool buscar_caminho(const Labirinto *lab, Posicao origem, Posicao destino,
                    Posicao caminho[], int *movimentos) {
    InfoBusca **mapa;
    Fila fila;
    Posicao atual;
    Posicao vizinha;
    Direcao direcao;
    bool encontrou = false;

    mapa = criar_mapa(lab->total_linhas, lab->total_colunas);
    // M x N posições bastam: cada célula entra na fila no máximo uma vez
    fila = criar_fila(lab->total_linhas * lab->total_colunas);

    mapa[origem.linha][origem.coluna].distancia = 0;
    mapa[origem.linha][origem.coluna].anterior = origem;
    enfileirar(&fila, origem);

    while (!encontrou && !fila_vazia(&fila)) {
        atual = desenfileirar(&fila);

        if (mesma_posicao(atual, destino)) {
            encontrou = true;
        } else {
            // Ordem cima, direita, baixo, esquerda: qualquer ordem daria um caminho mínimo
            for (direcao = CIMA; direcao <= ESQUERDA; direcao++) {
                vizinha = mover(atual, direcao);
                // Célula marcada ao entrar na fila, para entrar uma única vez
                if (dentro_dos_limites(lab, vizinha)
                    && celula_livre(lab, vizinha)
                    && mapa[vizinha.linha][vizinha.coluna].distancia == NAO_VISITADA) {
                    mapa[vizinha.linha][vizinha.coluna].distancia =
                        mapa[atual.linha][atual.coluna].distancia + 1;
                    mapa[vizinha.linha][vizinha.coluna].anterior = atual;
                    enfileirar(&fila, vizinha);
                }
            }
        }
    }

    if (encontrou) {
        *movimentos = mapa[destino.linha][destino.coluna].distancia;
        reconstruir_caminho(mapa, destino, caminho);
    }

    liberar_fila(&fila);
    liberar_mapa(mapa, lab->total_linhas);
    return encontrou;
}

// Volta do destino até a origem preenchendo o vetor de trás para frente
void reconstruir_caminho(InfoBusca **mapa, Posicao destino, Posicao caminho[]) {
    Posicao atual;
    int indice;

    atual = destino;
    for (indice = mapa[destino.linha][destino.coluna].distancia; indice >= 0; indice--) {
        caminho[indice] = atual;
        atual = mapa[atual.linha][atual.coluna].anterior;
    }
}

// Montagem da saída: o texto é montado num vetor para ser comparado com strcmp

// Concatena sem ultrapassar a capacidade do vetor
void anexar_texto(char saida[], int capacidade, const char texto[]) {
    int usado;
    int livre;

    usado = (int) strlen(saida);
    livre = capacidade - usado - 1;
    if (livre > 0) {
        strncat(saida, texto, (size_t) livre);
    }
}

void escrever_caminho(const Posicao caminho[], int movimentos, char saida[], int capacidade) {
    char texto[32];
    int i;

    anexar_texto(saida, capacidade, "Resultado: Caminho encontrado\nCaminho: ");
    for (i = 0; i <= movimentos; i++) {
        if (i > 0) {
            anexar_texto(saida, capacidade, " → ");
        }
        snprintf(texto, sizeof(texto), "(%d,%d)", caminho[i].linha, caminho[i].coluna);
        anexar_texto(saida, capacidade, texto);
    }
    snprintf(texto, sizeof(texto), "\nMovimentos: %d", movimentos);
    anexar_texto(saida, capacidade, texto);
}

// Valida a entrada e, se for válida, busca o caminho
void resolver_labirinto(const Labirinto *lab, Posicao origem, Posicao destino,
                        char saida[], int capacidade) {
    Motivo motivo;
    Posicao *caminho;
    int movimentos;

    saida[0] = '\0';
    movimentos = 0;

    motivo = validar_entrada(lab, origem, destino);
    if (motivo != MOTIVO_NENHUM) {
        anexar_texto(saida, capacidade, "Resultado: Entrada inválida\nMotivo: ");
        anexar_texto(saida, capacidade, texto_do_motivo(motivo));
    } else {
        // Um caminho mínimo nunca repete célula, então M x N posições bastam
        caminho = (Posicao *) alocar_memoria((size_t) lab->total_linhas
                                             * (size_t) lab->total_colunas
                                             * sizeof(Posicao));
        if (buscar_caminho(lab, origem, destino, caminho, &movimentos)) {
            escrever_caminho(caminho, movimentos, saida, capacidade);
        } else {
            anexar_texto(saida, capacidade, "Resultado: Sem caminho");
        }
        free(caminho);
    }
}

// Casos de teste

// Sem isso o console do Windows mostra "→" e os acentos embaralhados
void configurar_console(void) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
}

// Os 15 casos de testes/casos.md. static: a tabela existe durante todo o programa
const CasoTeste *obter_casos_etapa02(int *total_casos) {
    static const CasoTeste casos[] = {
        { "CN-01", "Caminho mínimo único",
          { "..###", "#...#", "###.#", "....." }, 4,
          { 0, 0 }, { 3, 4 },
          "Resultado: Caminho encontrado\n"
          "Caminho: (0,0) → (0,1) → (1,1) → (1,2) → (1,3) → (2,3) → (3,3) → (3,4)\n"
          "Movimentos: 7" },
        { "CN-02", "Vários caminhos mínimos",
          { "...", "...", "..." }, 3,
          { 0, 0 }, { 2, 2 },
          "Resultado: Caminho encontrado\n"
          "Caminho: (0,0) → (0,1) → (0,2) → (1,2) → (2,2)\n"
          "Movimentos: 4" },
        { "CN-03", "Desvio por uma única passagem",
          { "....", "##.#", "...." }, 3,
          { 0, 0 }, { 2, 0 },
          "Resultado: Caminho encontrado\n"
          "Caminho: (0,0) → (0,1) → (0,2) → (1,2) → (2,2) → (2,1) → (2,0)\n"
          "Movimentos: 6" },
        { "CN-04", "Percurso no sentido inverso",
          { "..###", "#...#", "###.#", "....." }, 4,
          { 3, 4 }, { 0, 0 },
          "Resultado: Caminho encontrado\n"
          "Caminho: (3,4) → (3,3) → (2,3) → (1,3) → (1,2) → (1,1) → (0,1) → (0,0)\n"
          "Movimentos: 7" },
        { "CN-05", "Labirinto em serpentina",
          { ".....", "####.", ".....", ".####", "....." }, 5,
          { 0, 0 }, { 4, 4 },
          "Resultado: Caminho encontrado\n"
          "Caminho: (0,0) → (0,1) → (0,2) → (0,3) → (0,4) → (1,4) → (2,4) → (2,3)"
          " → (2,2) → (2,1) → (2,0) → (3,0) → (4,0) → (4,1) → (4,2) → (4,3) → (4,4)\n"
          "Movimentos: 16" },
        { "CN-06", "Escolha do menor entre dois percursos",
          { ".......", ".#####.", "......." }, 3,
          { 0, 1 }, { 2, 1 },
          "Resultado: Caminho encontrado\n"
          "Caminho: (0,1) → (0,0) → (1,0) → (2,0) → (2,1)\n"
          "Movimentos: 4" },
        { "CN-07", "Contorno de obstáculo",
          { ".....", "..#..", "....." }, 3,
          { 1, 0 }, { 1, 4 },
          "Resultado: Caminho encontrado\n"
          "Caminho: (1,0) → (0,0) → (0,1) → (0,2) → (0,3) → (0,4) → (1,4)\n"
          "Movimentos: 6" },
        { "CN-08", "Labirinto com becos sem saída",
          { "..#.....", "#.#.###.", "#...#...", "###.#.##",
            "#...#...", "#.###.#.", "#....##." }, 7,
          { 0, 0 }, { 6, 7 },
          "Resultado: Caminho encontrado\n"
          "Caminho: (0,0) → (0,1) → (1,1) → (2,1) → (2,2) → (2,3) → (1,3) → (0,3)"
          " → (0,4) → (0,5) → (0,6) → (0,7) → (1,7) → (2,7) → (2,6) → (2,5)"
          " → (3,5) → (4,5) → (4,6) → (4,7) → (5,7) → (6,7)\n"
          "Movimentos: 21" },
        { "CN-09", "Destino inalcançável",
          { "..#", "###", "#.." }, 3,
          { 0, 0 }, { 2, 2 },
          "Resultado: Sem caminho" },
        { "CN-10", "Destino cercado por paredes",
          { ".....", ".###.", ".#.#.", ".###.", "....." }, 5,
          { 0, 0 }, { 2, 2 },
          "Resultado: Sem caminho" },
        { "CL-01", "Origem igual ao destino",
          { "...", "##.", "..." }, 3,
          { 0, 0 }, { 0, 0 },
          "Resultado: Caminho encontrado\n"
          "Caminho: (0,0)\n"
          "Movimentos: 0" },
        { "CL-02", "Labirinto de uma única linha",
          { "....." }, 1,
          { 0, 0 }, { 0, 4 },
          "Resultado: Caminho encontrado\n"
          "Caminho: (0,0) → (0,1) → (0,2) → (0,3) → (0,4)\n"
          "Movimentos: 4" },
        { "CL-03", "Ligação apenas pela diagonal",
          { ".#", "#." }, 2,
          { 0, 0 }, { 1, 1 },
          "Resultado: Sem caminho" },
        { "CI-01", "Origem bloqueada",
          { "#.", ".." }, 2,
          { 0, 0 }, { 1, 1 },
          "Resultado: Entrada inválida\n"
          "Motivo: Origem bloqueada" },
        { "CI-02", "Destino fora dos limites",
          { "...", "..." }, 2,
          { 0, 0 }, { 2, 0 },
          "Resultado: Entrada inválida\n"
          "Motivo: Destino fora dos limites" }
    };

    *total_casos = (int) (sizeof(casos) / sizeof(casos[0]));
    return casos;
}

void imprimir_entrada(const Labirinto *lab, Posicao origem, Posicao destino) {
    int linha;
    int coluna;

    printf("    ");
    for (coluna = 0; coluna < lab->total_colunas; coluna++) {
        printf("%d", coluna % 10);
    }
    printf("\n");
    for (linha = 0; linha < lab->total_linhas; linha++) {
        printf("%3d %s\n", linha, lab->linhas[linha]);
    }
    printf("Origem: (%d,%d)   Destino: (%d,%d)\n",
           origem.linha, origem.coluna, destino.linha, destino.coluna);
}

// O caso é recebido por valor: a tabela original não pode ser alterada
bool executar_caso(CasoTeste caso) {
    Labirinto lab;
    char saida[TAM_SAIDA];
    bool aprovado;

    lab = montar_labirinto(caso.linhas, caso.total_linhas);

    printf("==================================================\n");
    printf("%s - %s\n", caso.id, caso.titulo);
    printf("--------------------------------------------------\n");
    printf("Entrada:\n");
    imprimir_entrada(&lab, caso.origem, caso.destino);

    resolver_labirinto(&lab, caso.origem, caso.destino, saida, TAM_SAIDA);
    printf("\nSaída obtida:\n%s\n\n", saida);

    // Conferência por texto exato com a saída esperada
    aprovado = (strcmp(saida, caso.saida_esperada) == 0);
    if (aprovado) {
        printf("Conferência com testes/casos.md: OK\n\n");
    } else {
        printf("Conferência com testes/casos.md: FALHOU\n");
        printf("Saída esperada:\n%s\n\n", caso.saida_esperada);
    }
    return aprovado;
}
