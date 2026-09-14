#include <stdio.h>
#include <stdlib.h>

#define NUM_DISCOS 4
#define NUM_TORRES 3

/*Estrutura de dados - Pilha*/
typedef struct No {
    int disco;
    struct No *proximo;
} No;

typedef struct {
    No *topo;
    int quantidade;
} Pilha;

void inicializar_pilha(Pilha *p) {
    p->topo = NULL;
    p->quantidade = 0;
}

int empilhar(Pilha *p, int disco) {
    No *novo = malloc(sizeof(No));
    if (novo == NULL) {
        return 0;
    }
    novo->disco = disco;
    novo->proximo = p->topo;
    p->topo = novo;
    p->quantidade++;
    return 1;
}

int desempilhar(Pilha *p, int *disco) {
    if (p->topo == NULL) {
        return 0;
    }
    No *removido = p->topo;
    *disco = removido->disco;
    p->topo = removido->proximo;
    p->quantidade--;
    free(removido);
    return 1;
}

int topo(Pilha *p, int *disco) {
    if (p->topo == NULL) {
        return 0;
    }
    *disco = p->topo->disco;
    return 1;
}

void imprimir(Pilha *p, int numero_torre) {
    printf("Torre %d (topo -> base): ", numero_torre);
    if (p->topo == NULL) {
        printf("vazia");
    } else {
        No *atual = p->topo;
        while (atual != NULL) {
            printf("[%d] ", atual->disco);
            atual = atual->proximo;
        }
    }
    printf("\n");
}

void liberar_pilha(Pilha *p) {
    int disco;
    while (desempilhar(p, &disco)) {
        /* apenas libera os nos */
    }
}

int mover_disco(Pilha *origem, Pilha *destino) {
    int discoOrigem, discoDestino;

    if (!topo(origem, &discoOrigem)) {
        printf("Movimento invalido: a torre de origem esta vazia.\n");
        return 0;
    }

    if (topo(destino, &discoDestino) && discoDestino < discoOrigem) {
        printf("Movimento invalido: nao e possivel colocar o disco %d sobre o disco %d.\n",
               discoOrigem, discoDestino);
        return 0;
    }

    int disco;
    desempilhar(origem, &disco);
    empilhar(destino, disco);
    return 1;
}

void configurar_jogo(Pilha torres[NUM_TORRES]) {
    int i;
    for (i = 0; i < NUM_TORRES; i++) {
        inicializar_pilha(&torres[i]);
    }
    for (i = NUM_DISCOS; i >= 1; i--) {
        empilhar(&torres[0], i);
    }
}

void exibir_torres(Pilha torres[NUM_TORRES]) {
    int i;
    printf("-------------------------------------------\n");
    for (i = 0; i < NUM_TORRES; i++) {
        imprimir(&torres[i], i + 1);
    }
    printf("-------------------------------------------\n");
}

void liberar_torres(Pilha torres[NUM_TORRES]) {
    int i;
    for (i = 0; i < NUM_TORRES; i++) {
        liberar_pilha(&torres[i]);
    }
}

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta */
    }
}

typedef enum { REINICIAR, SAIR } ResultadoJogo;

ResultadoJogo jogar(void) {
    Pilha torres[NUM_TORRES];
    int movimentos = 0;
    int origem, destino, resp;

    configurar_jogo(torres);

    printf("\n=== NOVA PARTIDA ===\n");
    printf("Objetivo: mover os %d discos da Torre 1 para a Torre 3.\n", NUM_DISCOS);
    printf("Regras: so o disco do topo se move; disco maior nao fica sobre disco menor.\n");

    while (torres[2].quantidade != NUM_DISCOS) {
        exibir_torres(torres);
        printf("Movimentos realizados: %d\n\n", movimentos);

        printf("Torre de origem (1-3) | 0 = reiniciar | -1 = sair: ");
        if (scanf("%d", &origem) != 1) {
            limpar_buffer();
            printf("Entrada invalida.\n\n");
            continue;
        }

        if (origem == 0) {
            liberar_torres(torres);
            return REINICIAR;
        }
        if (origem == -1) {
            liberar_torres(torres);
            return SAIR;
        }
        if (origem < 1 || origem > NUM_TORRES) {
            printf("Torre invalida! Escolha entre 1 e %d.\n\n", NUM_TORRES);
            continue;
        }

        printf("Torre de destino (1-3): ");
        if (scanf("%d", &destino) != 1) {
            limpar_buffer();
            printf("Entrada invalida.\n\n");
            continue;
        }
        if (destino < 1 || destino > NUM_TORRES) {
            printf("Torre invalida! Escolha entre 1 e %d.\n\n", NUM_TORRES);
            continue;
        }
        if (origem == destino) {
            printf("Movimento invalido: origem e destino sao a mesma torre.\n\n");
            continue;
        }

        if (mover_disco(&torres[origem - 1], &torres[destino - 1])) {
            movimentos++;
            printf("Movimento realizado: Torre %d -> Torre %d\n\n", origem, destino);
        } else {
            printf("\n");
        }
    }

    exibir_torres(torres);
    printf("\n*** PARABENS! Voce venceu em %d movimentos! ***\n\n", movimentos);
    liberar_torres(torres);

    printf("Jogar novamente? (1 = Sim / 0 = Nao): ");
    if (scanf("%d", &resp) != 1) {
        limpar_buffer();
        return SAIR;
    }
    return (resp == 1) ? REINICIAR : SAIR;
}

int main(void) {
    ResultadoJogo r = REINICIAR;

    printf("=============================================\n");
    printf("           JOGO DA TORRE DE HANOI\n");
    printf("=============================================\n");

    while (r == REINICIAR) {
        r = jogar();
    }

    printf("Obrigado por jogar! Ate a proxima.\n");
    return 0;
}