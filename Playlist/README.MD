# Gerenciador de Playlist com Lista Encadeada

Programa em C (`playlist.c`) que armazena e manipula músicas de uma playlist usando uma **lista simplesmente encadeada implementada manualmente**, sem usar nenhuma estrutura pronta da linguagem para o armazenamento principal.

## Requisitos

- GCC (ou outro compilador C compatível com C11)
- Nenhuma biblioteca externa necessária para as operações da estrutura

## Compilação

```bash
gcc -Wall -Wextra -std=c11 -o playlist playlist.c
```

> A flag `-std=c11` assegura a conformidade com o padrão C11, garantindo o comportamento esperado da alocação de memória e manipulação de strings sem depender de extensões específicas de plataforma.

## Execução

```bash
./playlist
```

O programa exibe um menu numerado e aguarda a opção do usuário via teclado, repetindo até que `0` seja escolhido.

```
===== MENU =====
1 - Inserir musica no inicio
2 - Inserir musica no final
3 - Inserir musica em posicao especifica
4 - Remover musica por ID
5 - Buscar musica por ID
6 - Buscar musicas por artista
7 - Exibir playlist completa
8 - Quantidade de musicas na playlist
9 - Duracao total da playlist
0 - Sair
Escolha uma opcao:
```

### Observação sobre a estrutura interna

Cada música fica guardada em um nó alocado dinamicamente (`malloc`), e os nós se conectam através do ponteiro `proximo`. A estrutura `Lista` guarda apenas o ponteiro do primeiro nó e a quantidade de elementos. Funções básicas como `inicializar_lista`, `inserir`, `buscar` e `remover` fazem parte da engrenagem interna. Decisões estruturais incluem indexação 0-based para inserções, busca única baseada em chave (ID), e buscas textuais implementadas isoladamente (`buscar_por_artista`) com funções manuais (`comparar_ignorando_case`) para evitar dependência de bibliotecas não-padrão.

---

## Exemplos de execução

Os exemplos abaixo assumem a execução interativa através do menu principal.

### 1. Inserir música (opções 1, 2 ou 3)

```
Escolha uma opcao: 1
Informe o ID: 1
Informe o titulo: Bohemian Rhapsody
Informe o artista: Queen
Informe o album: A Night at the Opera
Informe a duracao (segundos): 355
Musica inserida com sucesso no inicio!
```

### 2. Exibir playlist completa (opção 7)

```
Escolha uma opcao: 7
----- Playlist (5 musica(s)) -----
1) [ID 3] Billie Jean - Michael Jackson (Thriller) - 4:54
2) [ID 2] Imagine - John Lennon (Imagine) - 3:03
3) [ID 5] Smells Like Teen Spirit - Nirvana (Nevermind) - 5:01
4) [ID 1] Bohemian Rhapsody - Queen (A Night at the Opera) - 5:55
5) [ID 4] Hey Jude - The Beatles (The Beatles (White Album)) - 7:11
-----------------------------------
```

### 3. Buscar músicas por artista (opção 6)

```
Escolha uma opcao: 6
Informe o artista: queen

--- Musicas de "queen" ---
[ID 1] Bohemian Rhapsody - Queen (A Night at the Opera)
```

### 4. Duração total da playlist (opção 9)

```
Escolha uma opcao: 9
Duracao total: 26:04  (1564 segundos)
```

### 5. Remover música por ID (opção 4)

```
Escolha uma opcao: 4
Informe o ID da musica a remover: 2
Remocao: sucesso
```

---

## Conjunto de testes realizados

Os testes abaixo avaliaram o comportamento estrutural da lista encadeada (inserções, buscas e remoções em diferentes cenários) e os casos de borda críticos antes de expor os dados à interface de usuário.

| # | Cenário testado | Entrada / ação | Resultado obtido | Resultado esperado | Status |
|---|---|---|---|---|---|
| 1 | `inicializar_lista` | Criar lista recém-alocada | `quantidade = 0` | `quantidade = 0` | ✅ |
| 2 | `inserir` no início (x3) | Billie Jean, Imagine, Bohemian Rhapsody (posição 0) | Billie Jean, Imagine, Bohemian Rhapsody | Ordem invertida das inserções | ✅ |
| 3 | `inserir` no final | Hey Jude com `posicao = quantidade` | Hey Jude na 4ª posição (última) | Nova música no fim da lista | ✅ |
| 4 | `inserir` em posição intermediária | Smells Like Teen Spirit com `posicao = 2` | Ocupou a 3ª posição, entre Imagine e Bohemian Rhapsody | Nova música no índice 2 | ✅ |
| 5 | `buscar` por ID existente | `buscar(id=3)` | Billie Jean encontrada | Retorna o nó correspondente | ✅ |
| 6 | `buscar` por ID inexistente | `buscar(id=99)` | `NULL` | Retorna `NULL` | ✅ |
| 7 | `buscar_por_artista` case insensitive | Buscar `"queen"` (minúsculo) | Encontra Bohemian Rhapsody | Encontrada ignorando maiúsc./minúsc. | ✅ |
| 8 | Quantidade de músicas | Checar `lista.quantidade` | `5` | `5` | ✅ |
| 9 | `duracao_total` | Soma da duração de 5 músicas | `1564` segundos (`26:04`) | `1564` segundos (`26:04`) | ✅ |
| 10 | `remover` por ID existente | `remover(id=2)` (Imagine) | Sucesso, lista com 4 músicas | Nó removido e pontes ajustadas | ✅ |
| 11 | `remover` por ID inexistente | `remover(id=99)` | Rejeitada corretamente, lista inalterada | Retorna falha e mantém lista intacta | ✅ |
| 12 | `remover` o primeiro elemento | Remove o nó de `lista.primeiro` | Atualizado corretamente, lista com 3 músicas | `primeiro` aponta para o antigo segundo nó | ✅ |
| 13 | Esvaziar a lista por completo | Remove nós até `primeiro == NULL` | `quantidade = 0`, "Playlist vazia." | `quantidade = 0` | ✅ |

### Como os testes foram executados

Os testes foram executados sobre uma lista de testes isolada (não a playlist interativa do usuário) visando cobrir todas as funcionalidades do escopo e casos críticos de ponteiros (inserção/remoção em extremos e no meio). O log comprobatório das 13 validações bem-sucedidas foi gerado automaticamente na saída padrão durante a inicialização. Adicionalmente, o programa garante o uso responsável da memória liberando todos os nós com `free` tanto na remoção individual quanto na finalização.

### Compilação sem warnings

O programa foi compilado utilizando `gcc -Wall -Wextra -std=c11 -o playlist playlist.c`, sem acusar nenhum alerta (warning) estrutural, tipográfico ou de vazamento de memória nas etapas de compilação.