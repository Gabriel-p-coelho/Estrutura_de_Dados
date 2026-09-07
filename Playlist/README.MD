# Gerenciador de Playlist com Lista Encadeada

Aplicação em C que armazena e manipula músicas de uma playlist usando uma
**lista simplesmente encadeada implementada manualmente** (sem usar nenhuma
estrutura pronta da linguagem para o armazenamento principal).

## Estrutura de dados

```c
typedef struct {
    int  id;
    char titulo[100];
    char artista[100];
    char album[100];
    int  duracao;      /* em segundos */
} Musica;

typedef struct No {
    Musica musica;
    struct No *proximo;
} No;

typedef struct {
    No  *primeiro;
    int  quantidade;
} Lista;
```

Cada música fica guardada em um nó alocado dinamicamente (`malloc`), e os nós
se conectam entre si através do ponteiro `proximo`. A `Lista` guarda apenas o
endereço do primeiro nó e a quantidade de elementos — todo o resto é
alcançado percorrendo a cadeia de ponteiros.

## Operações da lista

| Função | O que faz |
|---|---|
| `inicializar_lista` | Zera a lista (`primeiro = NULL`, `quantidade = 0`) |
| `inserir(lista, musica, posicao)` | Insere na posição indicada (0 = início). Usada para inserir no início (`posicao = 0`), no final (`posicao = quantidade`) e em qualquer posição intermediária |
| `imprimir` | Percorre e exibe todas as músicas |
| `buscar(lista, id)` | Busca por ID (chave única), retorna o nó ou `NULL` |
| `remover(lista, id)` | Remove a música com o ID informado |

Funções complementares da aplicação (não fazem parte da estrutura da lista
em si): `buscar_por_artista`, `duracao_total`, `cadastrar_musica`.

## Como compilar e executar

```bash
gcc -Wall -Wextra -std=c11 -o playlist playlist.c
./playlist
```

Compila sem nenhum warning com `-Wall -Wextra`.

## Funcionalidades do menu

1. Inserir música no início
2. Inserir música no final
3. Inserir música em posição específica
4. Remover música por ID
5. Buscar música por ID
6. Buscar músicas por artista
7. Exibir playlist completa
8. Quantidade de músicas na playlist
9. Duração total da playlist
0. Sair

## Documentação dos testes

Os testes abaixo foram executados sobre uma lista de testes isolada (não a
playlist do usuário), cobrindo todas as funcionalidades pedidas no
enunciado e os casos de borda mais comuns de lista encadeada: lista vazia,
inserção no início/meio/fim, busca com e sem sucesso, remoção do primeiro
elemento (caso especial de ponteiro) e remoção até esvaziar a lista.

| # | Funcionalidade testada | Ação / entrada | Resultado esperado | Resultado obtido | Status |
|---|---|---|---|---|---|
| 01 | `inicializar_lista` | Lista recém-criada | `quantidade = 0` | `quantidade = 0` | OK |
| 02 | `inserir` no início (x3) | Insere Bohemian Rhapsody, Imagine, Billie Jean, todas com `posicao = 0` | Ordem final invertida: Billie Jean, Imagine, Bohemian Rhapsody | Billie Jean, Imagine, Bohemian Rhapsody | OK |
| 03 | `inserir` no final | Insere Hey Jude com `posicao = quantidade` | Hey Jude aparece na última posição | Hey Jude na 4ª posição (última) | OK |
| 04 | `inserir` em posição intermediária | Insere Smells Like Teen Spirit com `posicao = 2` | Nova música ocupa o índice 2 (3ª posição) | Ocupou a 3ª posição, entre Imagine e Bohemian Rhapsody | OK |
| 05 | `buscar` por ID existente | `buscar(id=3)` | Retorna o nó de Billie Jean | Billie Jean encontrada | OK |
| 06 | `buscar` por ID inexistente | `buscar(id=99)` | Retorna `NULL` | `NULL` | OK |
| 07 | `buscar_por_artista` | Busca por `"queen"` (minúsculo, de propósito) | Encontra Bohemian Rhapsody mesmo com caixa diferente | Encontrada (comparação ignora maiúsc./minúsc.) | OK |
| 08 | Quantidade de músicas | `lista.quantidade` após as inserções | `5` | `5` | OK |
| 09 | `duracao_total` | Soma da duração das 5 músicas | `1564` segundos (`26:04`) | `1564` segundos (`26:04`) | OK |
| 10 | `remover` por ID existente | `remover(id=2)` (Imagine) | Remoção com sucesso, lista com 4 músicas | Sucesso, lista com 4 músicas | OK |
| 11 | `remover` por ID inexistente | `remover(id=99)` | Retorna 0 (falha), lista inalterada | Rejeitada corretamente, lista inalterada | OK |
| 12 | `remover` o primeiro elemento (caso especial) | Remove o nó apontado por `lista.primeiro` | `lista.primeiro` passa a apontar para o antigo segundo nó | Atualizado corretamente, lista com 3 músicas | OK |
| 13 | Esvaziar a lista por completo | Remove todos os nós em laço, até `primeiro == NULL` | `quantidade = 0`, `imprimir` mostra "Playlist vazia." | `quantidade = 0`, "Playlist vazia." | OK |

**Resultado: 13/13 testes passaram.**

### Log real de execução

Saída obtida ao rodar a bateria de testes (gerada automaticamente pelo
programa antes da remoção do menu de testes, para fins de evidência):

```
========================================
      BATERIA DE TESTES AUTOMATICOS
========================================

[Teste 01] Lista recem-inicializada deve estar vazia
Esperado: 0 | Obtido: 0 (OK)

[Teste 02] Inserir 3 musicas no inicio, uma de cada vez
Esperado (ordem invertida): Billie Jean, Imagine, Bohemian Rhapsody

----- Playlist (3 musica(s)) -----
1) [ID 3] Billie Jean - Michael Jackson (Thriller) - 4:54
2) [ID 2] Imagine - John Lennon (Imagine) - 3:03
3) [ID 1] Bohemian Rhapsody - Queen (A Night at the Opera) - 5:55
-----------------------------------

[Teste 03] Inserir musica no final (posicao = quantidade)

----- Playlist (4 musica(s)) -----
1) [ID 3] Billie Jean - Michael Jackson (Thriller) - 4:54
2) [ID 2] Imagine - John Lennon (Imagine) - 3:03
3) [ID 1] Bohemian Rhapsody - Queen (A Night at the Opera) - 5:55
4) [ID 4] Hey Jude - The Beatles (The Beatles (White Album)) - 7:11
-----------------------------------

[Teste 04] Inserir musica na posicao 2 (indice 0-based)
Esperado: a nova musica deve ficar na 3a posicao da lista

----- Playlist (5 musica(s)) -----
1) [ID 3] Billie Jean - Michael Jackson (Thriller) - 4:54
2) [ID 2] Imagine - John Lennon (Imagine) - 3:03
3) [ID 5] Smells Like Teen Spirit - Nirvana (Nevermind) - 5:01
4) [ID 1] Bohemian Rhapsody - Queen (A Night at the Opera) - 5:55
5) [ID 4] Hey Jude - The Beatles (The Beatles (White Album)) - 7:11
-----------------------------------

[Teste 05] Buscar por ID existente (3 = Billie Jean)
Encontrada: Billie Jean - Michael Jackson (OK)

[Teste 06] Buscar por ID inexistente (99)
Resultado: nao encontrada (OK)

[Teste 07] Buscar musicas por artista ("queen", minusculo de proposito)

--- Musicas de "queen" ---
[ID 1] Bohemian Rhapsody - Queen (A Night at the Opera)

[Teste 08] Quantidade de musicas armazenadas
Esperado: 5 | Obtido: 5

[Teste 09] Duracao total da playlist
Duracao total: 26:04  (1564 segundos)

[Teste 10] Remover musica por ID existente (2 = Imagine)
Remocao: sucesso (OK)

----- Playlist (4 musica(s)) -----
1) [ID 3] Billie Jean - Michael Jackson (Thriller) - 4:54
2) [ID 5] Smells Like Teen Spirit - Nirvana (Nevermind) - 5:01
3) [ID 1] Bohemian Rhapsody - Queen (A Night at the Opera) - 5:55
4) [ID 4] Hey Jude - The Beatles (The Beatles (White Album)) - 7:11
-----------------------------------

[Teste 11] Tentar remover ID inexistente (99)
Resultado: rejeitada corretamente (OK)

[Teste 12] Remover o PRIMEIRO elemento da lista (caso especial)

----- Playlist (3 musica(s)) -----
1) [ID 5] Smells Like Teen Spirit - Nirvana (Nevermind) - 5:01
2) [ID 1] Bohemian Rhapsody - Queen (A Night at the Opera) - 5:55
3) [ID 4] Hey Jude - The Beatles (The Beatles (White Album)) - 7:11
-----------------------------------

[Teste 13] Esvaziar a lista por completo
Esperado: 0 | Obtido: 0
Playlist vazia.

========================================
      FIM DA BATERIA DE TESTES
========================================
```

## Decisões de projeto

- **Indexação de `inserir` é 0-based**: `posicao = 0` insere no início. Valores
  negativos ou maiores que `quantidade` são tratados de forma segura
  (inserem no início ou no final, respectivamente).
- **`buscar` é por ID** (chave única, um único resultado). A busca por
  artista, que pode retornar vários resultados, foi implementada como uma
  função separada (`buscar_por_artista`) em vez de sobrecarregar a mesma
  assinatura.
- **`comparar_ignorando_case`** foi escrita manualmente em vez de usar
  `strcasecmp`, que não faz parte do C padrão (evita depender de uma
  extensão específica de plataforma).
- Toda música alocada com `malloc` é devidamente liberada com `free`, seja
  na remoção individual (`remover`) ou ao final da execução
  (`liberar_lista`).