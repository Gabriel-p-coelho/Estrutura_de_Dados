#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_CORES 4

typedef enum {
    VERDE,
    VERMELHO,
    AZUL,
    AMARELO
} Cor;

/*Estrutura de dados - Fila*/
typedef struct No {
    Cor cor;
    struct No *proximo;
} No;

typedef struct {
    No *inicio;
    No *fim;
    int quantidade;
} Fila;

void inicializar_fila(Fila *fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
    fila->quantidade = 0;
}

void enfileirar(Fila *fila, Cor cor) {
    No *novo = (No *) malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: memoria insuficiente.\n");
        exit(1);
    }
    novo->cor = cor;
    novo->proximo = NULL;

    if (fila->fim == NULL) {
        fila->inicio = novo;
        fila->fim = novo;
    } else {
        fila->fim->proximo = novo;
        fila->fim = novo;
    }
    fila->quantidade++;
}

Cor desenfileirar(Fila *fila) {
    if (fila->inicio == NULL) {
        printf("Erro: tentativa de desenfileirar fila vazia.\n");
        exit(1);
    }

    No *removido = fila->inicio;
    Cor cor = removido->cor;

    fila->inicio = fila->inicio->proximo;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    free(removido);
    fila->quantidade--;
    return cor;
}

Cor frente(Fila *fila) {
    if (fila->inicio == NULL) {
        printf("Erro: fila vazia, nao ha frente.\n");
        exit(1);
    }
    return fila->inicio->cor;
}

const char *cor_para_texto(Cor cor) {
    switch (cor) {
        case VERDE:    return "VERDE";
        case VERMELHO: return "VERMELHO";
        case AZUL:     return "AZUL";
        case AMARELO:  return "AMARELO";
        default:       return "?";
    }
}

void imprimir(Fila *fila) {
    No *atual = fila->inicio;
    int primeiro = 1;

    while (atual != NULL) {
        if (!primeiro) {
            printf(" -> ");
        }
        printf("%s", cor_para_texto(atual->cor));
        primeiro = 0;
        atual = atual->proximo;
    }
    printf("\n");
}

void liberar_fila(Fila *fila) {
    while (fila->inicio != NULL) {
        desenfileirar(fila);
    }
}

Cor sortear_cor(void) {
    return (Cor)(rand() % NUM_CORES);
}

Cor ler_cor_jogador(void) {
    char entrada[20];

    while (1) {
        printf("Cor (V=Verde, R=Vermelho, A=Azul, M=Amarelo): ");
        if (scanf("%19s", entrada) != 1) {
            printf("\nEntrada encerrada. Fechando o jogo.\n");
            exit(0);
        }

        switch (entrada[0]) {
            case 'V': case 'v': return VERDE;
            case 'R': case 'r': return VERMELHO;
            case 'A': case 'a': return AZUL;
            case 'M': case 'm': return AMARELO;
            default:
                printf("Cor invalida. Tente novamente.\n");
        }
    }
}

int verificar_sequencia(Fila *fila, Cor *respostas, int qtd_respostas) {
    int quantidade_original = fila->quantidade;
    int correto = 1;

    for (int i = 0; i < quantidade_original; i++) {
        Cor cor_esperada = frente(fila);
        desenfileirar(fila);
        enfileirar(fila, cor_esperada); 
        if (i >= qtd_respostas || respostas[i] != cor_esperada) {
            correto = 0;
        }
    }
    return correto;
}

void jogar_partida(void) {
    Fila fila;
    inicializar_fila(&fila);
    int pontuacao = 0;
    int jogo_ativo = 1;
    printf("\n=== Nova partida iniciada! ===\n");
    while (jogo_ativo) {
        Cor nova_cor = sortear_cor();
        enfileirar(&fila, nova_cor);
        printf("\n--- Rodada %d ---\n", fila.quantidade);
        printf("Sequencia: %s\n", cor_para_texto(nova_cor));
        printf("Repita a sequencia:\n");
        Cor *respostas = (Cor *) malloc(sizeof(Cor) * fila.quantidade);
        if (respostas == NULL) {
            printf("Erro: memoria insuficiente.\n");
            exit(1);
        }
        for (int i = 0; i < fila.quantidade; i++) {
            respostas[i] = ler_cor_jogador();
        }
        int acertou = verificar_sequencia(&fila, respostas, fila.quantidade);
        free(respostas);
        if (acertou) {
            pontuacao++;
            printf("Correto! Pontuacao atual: %d\n", pontuacao);
        } else {
            printf("\nSequencia incorreta! Fim de jogo.\n");
            printf("A sequencia correta era: ");
            imprimir(&fila);
            printf("Pontuacao final: %d\n", pontuacao);
            jogo_ativo = 0;
        }
    }
    liberar_fila(&fila);
}

int main(void) {
    srand((unsigned int) time(NULL));
    int opcao;
    do {
        printf("\n===== JOGO GENIUS =====\n");
        printf("1 - Jogar (nova partida)\n");
        printf("2 - Sair\n");
        printf("Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {}
            opcao = -1;
            continue;
        }
        if (opcao == 1) {
            jogar_partida();
        } else if (opcao != 2) {
            printf("Opcao invalida.\n");
        }
    } while (opcao != 2);
    printf("Encerrando o jogo. Ate a proxima!\n");
    return 0;
}