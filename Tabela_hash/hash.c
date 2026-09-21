#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 7

typedef struct Node {
    int key;
    struct Node *next;
} Node;

typedef struct {
    Node *buckets[TABLE_SIZE];
    int total_elements;
} HashTable;

void initTable(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++)
        table->buckets[i] = NULL;
    table->total_elements = 0;
}

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

void insert(HashTable *table, int key) {
    int index = hashFunction(key);
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->key = key;
    newNode->next = NULL;

    if (table->buckets[index] == NULL) {
        table->buckets[index] = newNode;
    } else {
        Node *current = table->buckets[index];
        while (current->next != NULL)
            current = current->next;
        current->next = newNode;
    }
    table->total_elements++;
}

int search(HashTable *table, int key) {
    int index = hashFunction(key);
    Node *current = table->buckets[index];
    while (current != NULL) {
        if (current->key == key)
            return index;
        current = current->next;
    }
    return -1;
}

int remove_key(HashTable *table, int key) {
    int index = hashFunction(key);
    Node *current = table->buckets[index];
    Node *prev = NULL;

    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL)
                table->buckets[index] = current->next;
            else
                prev->next = current->next;
            free(current);
            table->total_elements--;
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

void printTable(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("[%d]: ", i);
        Node *current = table->buckets[i];
        if (current == NULL) {
            printf("(vazio)");
        }
        while (current != NULL) {
            printf("%d", current->key);
            if (current->next != NULL) printf(" -> ");
            current = current->next;
        }
        printf("\n");
    }
}

double loadFactor(HashTable *table) {
    return (double) table->total_elements / TABLE_SIZE;
}

void freeTable(HashTable *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node *current = table->buckets[i];
        while (current != NULL) {
            Node *temp = current;
            current = current->next;
            free(temp);
        }
    }
}

int main() {
    HashTable table;
    initTable(&table);

    int keys[] = {190, 322, 172, 89, 13, 4, 769, 61, 15, 76};
    int n = sizeof(keys) / sizeof(keys[0]);

    printf("=== Insercao ===\n");
    for (int i = 0; i < n; i++) {
        insert(&table, keys[i]);
        printf("Inserido %d (h=%d)\n", keys[i], hashFunction(keys[i]));
    }

    printf("\n=== Tabela apos insercoes ===\n");
    printTable(&table);
    printf("Fator de carga: %.2f\n", loadFactor(&table));

    printf("\n=== Busca ===\n");
    int testKey = 769;
    int idx = search(&table, testKey);
    if (idx != -1)
        printf("Chave %d encontrada no bucket %d\n", testKey, idx);
    else
        printf("Chave %d nao encontrada\n", testKey);

    printf("\n=== Remocao ===\n");
    int toRemove[] = {4, 190};
    for (int i = 0; i < 2; i++) {
        if (remove_key(&table, toRemove[i]))
            printf("Removido %d\n", toRemove[i]);
        else
            printf("%d nao encontrado\n", toRemove[i]);
    }

    printf("\n=== Tabela apos remocoes ===\n");
    printTable(&table);
    printf("Fator de carga final: %.2f\n", loadFactor(&table));

    freeTable(&table);
    return 0;
}
