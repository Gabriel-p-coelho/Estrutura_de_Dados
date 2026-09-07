#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_TITULO   100
#define TAM_ARTISTA  100
#define TAM_ALBUM    100

/*Estrutura de dados - Lista encadeada*/
typedef struct {
    int  id;
    char titulo[TAM_TITULO];
    char artista[TAM_ARTISTA];
    char album[TAM_ALBUM];
    int  duracao;
} Musica;

typedef struct No {
    Musica musica;
    struct No *proximo;
} No;

typedef struct {
    No  *primeiro;
    int  quantidade;
} Lista;

void inicializar_lista(Lista *lista) {
    lista->primeiro  = NULL;
    lista->quantidade = 0;
}

static No* criar_no(Musica m) {
    No *novo = malloc(sizeof(No));
    if (novo == NULL) {
        printf("Erro: memoria insuficiente.\n");
        exit(1);
    }
    novo->musica   = m;
    novo->proximo  = NULL;
    return novo;
}

int inserir(Lista *lista, Musica m, int posicao) {
    if (posicao < 0) {
        return 0;
    }
    No *novo = criar_no(m);
    if (posicao == 0 || lista->primeiro == NULL) {
        novo->proximo = lista->primeiro;
        lista->primeiro = novo;
    } else {
        No *atual = lista->primeiro;
        int i = 0;
        while (i < posicao - 1 && atual->proximo != NULL) {
            atual = atual->proximo;
            i++;
        }
        novo->proximo = atual->proximo;
        atual->proximo = novo;
    }
    lista->quantidade++;
    return 1;
}

void imprimir(Lista *lista) {
    if (lista->primeiro == NULL) {
        printf("Playlist vazia.\n");
        return;
    }

    No *atual = lista->primeiro;
    int pos = 1;
    printf("\n----- Playlist (%d musica(s)) -----\n", lista->quantidade);
    while (atual != NULL) {
        printf("%d) [ID %d] %s - %s (%s) - %d:%02d\n",
               pos,
               atual->musica.id,
               atual->musica.titulo,
               atual->musica.artista,
               atual->musica.album,
               atual->musica.duracao / 60,
               atual->musica.duracao % 60);
        atual = atual->proximo;
        pos++;
    }
    printf("-----------------------------------\n");
}

No* buscar(Lista *lista, int id) {
    No *atual = lista->primeiro;
    while (atual != NULL) {
        if (atual->musica.id == id) {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

int remover(Lista *lista, int id) {
    No *atual    = lista->primeiro;
    No *anterior = NULL;

    while (atual != NULL && atual->musica.id != id) {
        anterior = atual;
        atual    = atual->proximo;
    }

    if (atual == NULL) {
        return 0;
    }

    if (anterior == NULL) {
        lista->primeiro = atual->proximo;
    } else {
        anterior->proximo = atual->proximo;
    }

    free(atual);
    lista->quantidade--;
    return 1;
}

void liberar_lista(Lista *lista) {
    No *atual = lista->primeiro;
    while (atual != NULL) {
        No *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }
    lista->primeiro   = NULL;
    lista->quantidade = 0;
}

static int comparar_ignorando_case(const char *a, const char *b) {
    while (*a && *b) {
        char ca = (char)tolower((unsigned char)*a);
        char cb = (char)tolower((unsigned char)*b);
        if (ca != cb) {
            return ca - cb;
        }
        a++;
        b++;
    }
    return (unsigned char)*a - (unsigned char)*b;
}

int buscar_por_artista(Lista *lista, const char *artista) {
    No *atual = lista->primeiro;
    int encontrados = 0;

    printf("\n--- Musicas de \"%s\" ---\n", artista);
    while (atual != NULL) {
        if (comparar_ignorando_case(atual->musica.artista, artista) == 0) {
            printf("[ID %d] %s - %s (%s)\n",
                   atual->musica.id, atual->musica.titulo,
                   atual->musica.artista, atual->musica.album);
            encontrados++;
        }
        atual = atual->proximo;
    }
    if (encontrados == 0) {
        printf("Nenhuma musica encontrada para este artista.\n");
    }
    return encontrados;
}

int duracao_total(Lista *lista) {
    No *atual = lista->primeiro;
    int total = 0;
    while (atual != NULL) {
        total += atual->musica.duracao;
        atual  = atual->proximo;
    }
    return total;
}

void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}
void ler_string(char *destino, int tamanho) {
    fgets(destino, tamanho, stdin);
    destino[strcspn(destino, "\n")] = '\0';
}
Musica cadastrar_musica(Lista *lista) {
    Musica m;
    int id;
    int min, seg;

    do {
        printf("ID da musica: ");
        scanf("%d", &id);
        limpar_buffer();

        if (buscar(lista, id) != NULL) {
            printf("Ja existe uma musica com este ID. Escolha outro.\n");
        } else {
            break;
        }
    } while (1);
    m.id = id;

    printf("Titulo: ");
    ler_string(m.titulo, TAM_TITULO);

    printf("Artista: ");
    ler_string(m.artista, TAM_ARTISTA);

    printf("Album: ");
    ler_string(m.album, TAM_ALBUM);

    printf("Duracao - minutos: ");
    scanf("%d", &min);
    printf("Duracao - segundos: ");
    scanf("%d", &seg);
    limpar_buffer();
    m.duracao = min * 60 + seg;

    return m;
}

static void exibir_menu(void) {
    printf("\n===== PLAYLIST - MENU =====\n");
    printf("1. Inserir musica no inicio\n");
    printf("2. Inserir musica no final\n");
    printf("3. Inserir musica em posicao especifica\n");
    printf("4. Remover musica por ID\n");
    printf("5. Buscar musica por ID\n");
    printf("6. Buscar musicas por artista\n");
    printf("7. Exibir playlist completa\n");
    printf("8. Quantidade de musicas na playlist\n");
    printf("9. Duracao total da playlist\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main(void) {
    Lista playlist;
    inicializar_lista(&playlist);

    int opcao;
    do {
        exibir_menu();
        if (scanf("%d", &opcao) != 1) {
            /* entrada invalida (nao numerica) -> limpa e ignora */
            limpar_buffer();
            printf("Entrada invalida.\n");
            continue;
        }
        limpar_buffer();

        switch (opcao) {
            case 1: {
                Musica m = cadastrar_musica(&playlist);
                inserir(&playlist, m, 0);
                printf("Musica inserida no inicio.\n");
                break;
            }
            case 2: {
                Musica m = cadastrar_musica(&playlist);
                inserir(&playlist, m, playlist.quantidade);
                printf("Musica inserida no final.\n");
                break;
            }
            case 3: {
                Musica m = cadastrar_musica(&playlist);
                int pos;
                printf("Posicao para insercao (0 = inicio): ");
                scanf("%d", &pos);
                limpar_buffer();
                inserir(&playlist, m, pos);
                printf("Musica inserida na posicao %d.\n", pos);
                break;
            }
            case 4: {
                int id;
                printf("ID da musica a remover: ");
                scanf("%d", &id);
                limpar_buffer();
                if (remover(&playlist, id))
                    printf("Musica removida com sucesso.\n");
                else
                    printf("Musica nao encontrada.\n");
                break;
            }
            case 5: {
                int id;
                printf("ID da musica a buscar: ");
                scanf("%d", &id);
                limpar_buffer();
                No *n = buscar(&playlist, id);
                if (n != NULL)
                    printf("Encontrada: %s - %s (%s)\n",
                           n->musica.titulo, n->musica.artista, n->musica.album);
                else
                    printf("Musica nao encontrada.\n");
                break;
            }
            case 6: {
                char artista[TAM_ARTISTA];
                printf("Nome do artista: ");
                ler_string(artista, TAM_ARTISTA);
                buscar_por_artista(&playlist, artista);
                break;
            }
            case 7:
                imprimir(&playlist);
                break;
            case 8:
                printf("Quantidade de musicas: %d\n", playlist.quantidade);
                break;
            case 9: {
                int total = duracao_total(&playlist);
                printf("Duracao total: %d:%02d  (%d segundos)\n",
                       total / 60, total % 60, total);
                break;
            }
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberar_lista(&playlist);
    return 0;
}