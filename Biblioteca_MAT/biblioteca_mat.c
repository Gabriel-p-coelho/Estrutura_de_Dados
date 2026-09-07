#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_VETORES 10

/*Estrutura de dados - Arrays*/
typedef struct {
    float *dados;
    int tamanho;
    int capacidade;
} Vetor;

void inicializar_array(Vetor *v, int capacidade) {
    v->dados = malloc(capacidade * sizeof(float));
    v->tamanho = 0;
    v->capacidade = capacidade;
}

int inserir(Vetor *v, float valor) {
    if (v->tamanho >= v->capacidade) {
        printf("Erro: vetor cheio (capacidade %d), nao e possivel inserir.\n", v->capacidade);
        return 0;
    }
    v->dados[v->tamanho] = valor;
    v->tamanho++;
    return 1;
}

void imprimir(Vetor *v) {
    printf("[");
    for (int i = 0; i < v->tamanho; i++) {
        printf("%.2f", v->dados[i]);
        if (i < v->tamanho - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int buscar(Vetor *v, float valor) {
    for (int i = 0; i < v->tamanho; i++) {
        if (v->dados[i] == valor) {
            return i;
        }
    }
    return -1;
}

int remover(Vetor *v, int indice) {
    if (indice < 0 || indice >= v->tamanho) {
        printf("Erro: indice %d invalido.\n", indice);
        return 0;
    }
    for (int i = indice; i < v->tamanho - 1; i++) {
        v->dados[i] = v->dados[i + 1];
    }
    v->tamanho--;
    return 1;
}

void liberar_array(Vetor *v) {
    free(v->dados);
    v->dados = NULL;
    v->tamanho = 0;
    v->capacidade = 0;
}

/*Operações matematicas*/
void multiplicar_escalar(Vetor *v, float escalar, Vetor *resultado) {
    inicializar_array(resultado, v->tamanho);
    for (int i = 0; i < v->tamanho; i++) {
        inserir(resultado, v->dados[i] * escalar);
    }
}

int somar_vetores(Vetor *v1, Vetor *v2, Vetor *resultado) {
    if (v1->tamanho != v2->tamanho) {
        printf("Erro: os vetores precisam ter o mesmo tamanho para serem somados.\n");
        return 0;
    }
    inicializar_array(resultado, v1->tamanho);
    for (int i = 0; i < v1->tamanho; i++) {
        inserir(resultado, v1->dados[i] + v2->dados[i]);
    }
    return 1;
}

float produto_escalar(Vetor *v1, Vetor *v2) {
    if (v1->tamanho != v2->tamanho) {
        printf("Erro: os vetores precisam ter o mesmo tamanho para o produto escalar.\n");
        return 0;
    }
    float soma = 0;
    for (int i = 0; i < v1->tamanho; i++) {
        soma += v1->dados[i] * v2->dados[i];
    }
    return soma;
}

float norma_vetor(Vetor *v) {
    float soma_quadrados = 0;
    for (int i = 0; i < v->tamanho; i++) {
        soma_quadrados += v->dados[i] * v->dados[i];
    }
    return sqrtf(soma_quadrados);
}

float similaridade_cosseno(Vetor *v1, Vetor *v2) {
    if (v1->tamanho != v2->tamanho) {
        printf("Erro: os vetores precisam ter o mesmo tamanho.\n");
        return -2;
    }
    float produto = produto_escalar(v1, v2);
    float norma1 = norma_vetor(v1);
    float norma2 = norma_vetor(v2);
    if (norma1 == 0 || norma2 == 0) {
        printf("Erro: vetor com norma zero.\n");
        return -2;
    }
    return produto / (norma1 * norma2);
}

int vetor_mais_similar(Vetor *consulta, Vetor conjunto[], int quantidade, int indice_ignorar) {
    int melhor_indice = -1;
    float melhor_similaridade = -2.0f;
    for (int i = 0; i < quantidade; i++) {
        if (i == indice_ignorar) continue;
        float sim = similaridade_cosseno(consulta, &conjunto[i]);
        printf("  -> Similaridade com vetor %d: %.4f\n", i, sim);
        if (sim > melhor_similaridade) {
            melhor_similaridade = sim;
            melhor_indice = i;
        }
    }
    return melhor_indice;
}

/*Funções de apoio*/
Vetor vetores[MAX_VETORES];
int total_vetores = 0;

void listar_vetores(void) {
    if (total_vetores == 0) {
        printf("Nenhum vetor armazenado ainda.\n");
        return;
    }
    for (int i = 0; i < total_vetores; i++) {
        printf("Vetor %d: ", i);
        imprimir(&vetores[i]);
    }
}

int escolher_vetor(const char *mensagem) {
    if (total_vetores == 0) {
        printf("Nenhum vetor armazenado ainda.\n");
        return -1;
    }
    listar_vetores();
    printf("%s", mensagem);
    int indice;
    scanf("%d", &indice);
    if (indice < 0 || indice >= total_vetores) {
        printf("Indice invalido.\n");
        return -1;
    }
    return indice;
}

void criar_vetor(void) {
    if (total_vetores >= MAX_VETORES) {
        printf("Limite de %d vetores atingido.\n", MAX_VETORES);
        return;
    }
    int tamanho;
    printf("Informe o tamanho do novo vetor: ");
    scanf("%d", &tamanho);
    if (tamanho <= 0) {
        printf("Tamanho invalido.\n");
        return;
    }
    inicializar_array(&vetores[total_vetores], tamanho);
    printf("Informe os %d valores reais do vetor %d:\n", tamanho, total_vetores);
    for (int i = 0; i < tamanho; i++) {
        float valor;
        printf("  posicao %d: ", i);
        scanf("%f", &valor);
        inserir(&vetores[total_vetores], valor);
    }
    total_vetores++;
    printf("Vetor criado com sucesso!\n");
}

/*MENU*/
void exibir_menu(void) {
    printf("\n===== MENU =====\n");
    printf("1  - Criar novo vetor\n");
    printf("2  - Exibir vetores armazenados\n");
    printf("3  - Multiplicar vetor por escalar\n");
    printf("4  - Somar dois vetores\n");
    printf("5 - Produto escalar entre dois vetores\n");
    printf("6 - Calcular norma de um vetor\n");
    printf("7 - Similaridade de cosseno entre dois vetores\n");
    printf("8 - Determinar o vetor mais similar a um vetor de consulta\n");
    printf("0 - Sair\n");
    printf("Escolha uma opcao: ");
}

int main(void) {
    int opcao;
    do {
        exibir_menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                criar_vetor();
                break;

            case 2:
                listar_vetores();
                break;

            case 3: {
                int idx = escolher_vetor("Escolha o vetor a multiplicar: ");
                if (idx == -1) break;
                float escalar;
                printf("Informe o escalar: ");
                scanf("%f", &escalar);
                Vetor resultado;
                multiplicar_escalar(&vetores[idx], escalar, &resultado);
                printf("Resultado: ");
                imprimir(&resultado);
                if (total_vetores < MAX_VETORES) {
                    vetores[total_vetores] = resultado;
                    total_vetores++;
                    printf("Resultado armazenado como vetor %d.\n", total_vetores - 1);
                } else {
                    liberar_array(&resultado);
                }
                break;
            }

            case 4: {
                int idx1 = escolher_vetor("Escolha o primeiro vetor: ");
                if (idx1 == -1) break;
                int idx2 = escolher_vetor("Escolha o segundo vetor: ");
                if (idx2 == -1) break;
                Vetor resultado;
                if (somar_vetores(&vetores[idx1], &vetores[idx2], &resultado)) {
                    printf("Resultado: ");
                    imprimir(&resultado);
                    if (total_vetores < MAX_VETORES) {
                        vetores[total_vetores] = resultado;
                        total_vetores++;
                        printf("Resultado armazenado como vetor %d.\n", total_vetores - 1);
                    } else {
                        liberar_array(&resultado);
                    }
                }
                break;
            }

            case 5: {
                int idx1 = escolher_vetor("Escolha o primeiro vetor: ");
                if (idx1 == -1) break;
                int idx2 = escolher_vetor("Escolha o segundo vetor: ");
                if (idx2 == -1) break;
                float resultado = produto_escalar(&vetores[idx1], &vetores[idx2]);
                printf("Produto escalar: %.4f\n", resultado);
                break;
            }

            case 6: {
                int idx = escolher_vetor("Escolha o vetor: ");
                if (idx == -1) break;
                printf("Norma: %.4f\n", norma_vetor(&vetores[idx]));
                break;
            }

            case 7: {
                int idx1 = escolher_vetor("Escolha o primeiro vetor: ");
                if (idx1 == -1) break;
                int idx2 = escolher_vetor("Escolha o segundo vetor: ");
                if (idx2 == -1) break;
                float sim = similaridade_cosseno(&vetores[idx1], &vetores[idx2]);
                printf("Similaridade de cosseno: %.4f\n", sim);
                break;
            }

            case 8: {
                int idx = escolher_vetor("Escolha o vetor de consulta: ");
                if (idx == -1) break;
                printf("Comparando vetor %d com os demais:\n", idx);
                int melhor = vetor_mais_similar(&vetores[idx], vetores, total_vetores, idx);
                if (melhor == -1) {
                    printf("Nao ha outros vetores para comparar.\n");
                } else {
                    printf("O vetor mais similar ao vetor %d e o vetor %d.\n", idx, melhor);
                }
                break;
            }

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }

    } while (opcao != 0);

    for (int i = 0; i < total_vetores; i++) {
        liberar_array(&vetores[i]);
    }

    return 0;
}