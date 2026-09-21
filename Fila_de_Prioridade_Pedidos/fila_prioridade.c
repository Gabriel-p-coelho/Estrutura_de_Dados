#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_DESCRICAO 100

/*Estrutura de dados - Max-Heap*/
typedef struct {
    int id;
    char descricao[TAM_DESCRICAO];
    int prioridade;
} Pedido;

typedef struct {
    Pedido *dados;
    int tamanho;
    int capacidade;
} Heap;

static int pai(int i) {
    return (i - 1) / 2;
}
static int esquerdo(int i) {
    return 2 * i + 1;
}
static int direito(int i) {
    return 2 * i + 2;
}

static void trocar(Pedido *a, Pedido *b) {
    Pedido tmp = *a;
    *a = *b;
    *b = tmp;
}

static void redimensionar_heap(Heap *h) {
    int nova_capacidade = h->capacidade * 2;
    Pedido *novo_dados = realloc(h->dados, nova_capacidade * sizeof(Pedido));

    if (novo_dados == NULL) {
        printf("Erro: falha ao alocar memoria para o heap.\n");
        exit(EXIT_FAILURE);
    }

    h->dados = novo_dados;
    h->capacidade = nova_capacidade;
}

void inicializar_heap(Heap *h, int capacidade_inicial) {
    if (capacidade_inicial <= 0) {
        capacidade_inicial = 1;
    }
    h->dados = malloc(capacidade_inicial * sizeof(Pedido));
    if (h->dados == NULL) {
        printf("Erro: falha ao alocar memoria para o heap.\n");
        exit(EXIT_FAILURE);
    }
    h->tamanho = 0;
    h->capacidade = capacidade_inicial;
}

void inserir(Heap *h, Pedido p) {
    if (h->tamanho == h->capacidade) {
        redimensionar_heap(h);
    }
    int i = h->tamanho;
    h->dados[i] = p;
    h->tamanho++;
    while (i > 0 && h->dados[pai(i)].prioridade < h->dados[i].prioridade) {
        trocar(&h->dados[pai(i)], &h->dados[i]);
        i = pai(i);
    }
}

void max_heapfy(Heap *h, int i) {
    int maior = i;
    int esq = esquerdo(i);
    int dir = direito(i);

    if (esq < h->tamanho && h->dados[esq].prioridade > h->dados[maior].prioridade) {
        maior = esq;
    }
    if (dir < h->tamanho && h->dados[dir].prioridade > h->dados[maior].prioridade) {
        maior = dir;
    }

    if (maior != i) {
        trocar(&h->dados[i], &h->dados[maior]);
        max_heapfy(h, maior);
    }
}

Pedido remover(Heap *h) {
    if (h->tamanho == 0) {
        printf("Erro: heap vazio, nao ha pedidos para atender.\n");
        exit(EXIT_FAILURE);
    }
    Pedido removido = h->dados[0];
    h->tamanho--;
    h->dados[0] = h->dados[h->tamanho];
    max_heapfy(h, 0);
    return removido;
}

void construir(Heap *h, Pedido *vetor, int n) {
    while (h->capacidade < n) {
        redimensionar_heap(h);
    }
    for (int i = 0; i < n; i++) {
        h->dados[i] = vetor[i];
    }
    h->tamanho = n;
    for (int i = (n / 2) - 1; i >= 0; i--) {
        max_heapfy(h, i);
    }
}

void print_heap(Heap *h) {
    if (h->tamanho == 0) {
        printf("Nenhum pedido cadastrado.\n");
        return;
    }
    printf("Pedidos:\n");
    for (int i = 0; i < h->tamanho; i++) {
        printf("ID: %d | Descricao: %s | Prioridade: %d\n",
               h->dados[i].id, h->dados[i].descricao, h->dados[i].prioridade);
    }
}

void liberar_heap(Heap *h) {
    free(h->dados);
    h->dados = NULL;
    h->tamanho = 0;
    h->capacidade = 0;
}

static void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }
}

static void cadastrar_pedido(Heap *h) {
    Pedido p;

    printf("\nID: ");
    scanf("%d", &p.id);
    limpar_buffer();

    printf("Descricao: ");
    fgets(p.descricao, TAM_DESCRICAO, stdin);
    p.descricao[strcspn(p.descricao, "\n")] = '\0'; 

    printf("Prioridade: ");
    scanf("%d", &p.prioridade);
    limpar_buffer();

    inserir(h, p);
    printf("Pedido cadastrado com sucesso!\n");
}

static void construir_heap_inicial(Heap *h) {
    int n;

    printf("\nQuantos pedidos deseja informar para o conjunto inicial? ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        limpar_buffer();
        printf("Quantidade invalida.\n");
        return;
    }
    limpar_buffer();

    Pedido *vetor = malloc(n * sizeof(Pedido));
    if (vetor == NULL) {
        printf("Erro: falha ao alocar memoria.\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("\n-- Pedido %d de %d --\n", i + 1, n);

        printf("ID: ");
        scanf("%d", &vetor[i].id);
        limpar_buffer();

        printf("Descricao: ");
        fgets(vetor[i].descricao, TAM_DESCRICAO, stdin);
        vetor[i].descricao[strcspn(vetor[i].descricao, "\n")] = '\0';

        printf("Prioridade: ");
        scanf("%d", &vetor[i].prioridade);
        limpar_buffer();
    }
    construir(h, vetor, n);
    free(vetor);
    printf("\nHeap construido com sucesso a partir de %d pedidos!\n", n);
    print_heap(h);
}

static void atender_pedido(Heap *h) {
    if (h->tamanho == 0) {
        printf("\nNao ha pedidos para atender.\n");
        return;
    }
    Pedido atendido = remover(h);
    printf("\nPedido atendido:\n");
    printf("ID: %d\n", atendido.id);
    printf("Descricao: %s\n", atendido.descricao);
    printf("Prioridade: %d\n", atendido.prioridade);
    printf("\nPedidos restantes:\n");
    print_heap(h);
}

int main(void) {
    Heap h;
    inicializar_heap(&h, 10);

    int opcao;

    do {
        printf("\n===== SISTEMA DE PEDIDOS =====\n");
        printf("1 - Cadastrar pedido\n");
        printf("2 - Atender pedido\n");
        printf("3 - Exibir pedidos\n");
        printf("4 - Exibir quantidade de pedidos\n");
        printf("5 - Construir heap a partir de um conjunto inicial de pedidos\n");
        printf("6 - Sair\n");
        printf("\nEscolha: ");

        if (scanf("%d", &opcao) != 1) {
            limpar_buffer();
            printf("Entrada invalida.\n");
            continue;
        }
        limpar_buffer();

        switch (opcao) {
            case 1:
                cadastrar_pedido(&h);
                break;
            case 2:
                atender_pedido(&h);
                break;
            case 3:
                printf("\n");
                print_heap(&h);
                break;
            case 4:
                printf("\nQuantidade de pedidos aguardando: %d\n", h.tamanho);
                break;
            case 5:
                construir_heap_inicial(&h);
                break;
            case 6:
                printf("\nEncerrando o sistema.\n");
                break;
            default:
                printf("\nOpcao invalida.\n");
        }

    } while (opcao != 6);

    liberar_heap(&h);
    return 0;
}