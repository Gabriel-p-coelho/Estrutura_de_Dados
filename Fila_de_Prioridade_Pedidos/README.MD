# Sistema de Gerenciamento de Pedidos com Max-Heap em C

Programa em C (`fila_prioridade.c`) que gerencia pedidos de uma empresa
utilizando um Max-Heap armazenado em vetor, sem uso de bibliotecas externas
para as operações da estrutura de dados. O pedido de maior prioridade fica
sempre na raiz (posição 0) do vetor.

## Requisitos

- GCC (ou outro compilador C compatível com C99)

## Compilação

```
gcc -Wall -Wextra -std=c99 -o fila_prioridade fila_prioridade.c
```

## Execução

```
./fila_prioridade
```

O programa exibe um menu numerado e aguarda a opção do usuário via teclado,
repetindo até que `6` seja escolhido.

```
===== SISTEMA DE PEDIDOS =====
1 - Cadastrar pedido
2 - Atender pedido
3 - Exibir pedidos
4 - Exibir quantidade de pedidos
5 - Construir heap a partir de um conjunto inicial de pedidos
6 - Sair

Escolha:
```

---

## Descrição das operações do Heap

Todas as operações abaixo trabalham sobre o vetor `dados` do `Heap`,
usando as relações de índice `pai = (i-1)/2`, `esquerdo = 2i+1` e
`direito = 2i+2` para navegar pela árvore sem usar ponteiros de nó.

- **`inicializar_heap(h, capacidade_inicial)`** — aloca o vetor `dados` com
a capacidade inicial informada e zera `tamanho`. É chamada uma única vez,
no início do `main`, para criar o Heap vazio.

- **`inserir(h, p)`** — insere um novo pedido. O pedido é colocado na
última posição do vetor (`dados[tamanho]`) e então "sobe" (*sift-up*),
sendo comparado com o pai e trocado de posição enquanto sua prioridade for
maior, até restaurar a propriedade de Max-Heap.

- **`remover(h)`** — remove e retorna o pedido de maior prioridade (a
raiz). O último elemento do vetor assume a posição da raiz, `tamanho` é
decrementado, e `max_heapfy` é chamado a partir do índice 0 para
reorganizar a árvore.

- **`max_heapfy(h, i)`** — verifica se o elemento no índice `i` é menor que
algum de seus filhos; se for, troca com o maior filho e chama a si mesma
recursivamente na nova posição (*sift-down*), até restaurar a propriedade
de Max-Heap a partir daquele ponto.

- **`construir(h, vetor, n)`** — constrói um Max-Heap a partir de um vetor
de pedidos já existente. Copia os `n` pedidos para `dados` e aplica
`max_heapfy` de trás para frente, começando no último nó com filhos
(`n/2 - 1`) até a raiz (índice 0) — abordagem *bottom-up*, mais eficiente
que inserir um a um.

- **`print_heap(h)`** — exibe todos os pedidos atualmente armazenados no
vetor, na ordem interna do Heap (não em ordem de prioridade "achatada",
apenas com a raiz sempre à frente).

- **`redimensionar_heap(h)`** *(auxiliar, não exigida pela lista de
operações do enunciado)* — dobra a capacidade do vetor com `realloc`
quando `inserir` ou `construir` precisam de mais espaço do que o
disponível.

- **`liberar_heap(h)`** *(auxiliar)* — libera a memória alocada pelo Heap
ao encerrar o programa.

---

## Exemplos de execução

### 1. Cadastrar pedido (opção 1)

```
Escolha: 1

ID: 104
Descricao: Pedido urgente
Prioridade: 8
Pedido cadastrado com sucesso!
```

### 2. Exibir pedidos (opção 3)

Após cadastrar os pedidos 101 (prioridade 2), 102 (prioridade 5), 103
(prioridade 3) e 104 (prioridade 8), nessa ordem:

```
Escolha: 3

Pedidos:
ID: 104 | Descricao: Pedido urgente | Prioridade: 8
ID: 102 | Descricao: Pedido de 5 produtos | Prioridade: 5
ID: 103 | Descricao: Pedido de 20 produtos | Prioridade: 3
ID: 101 | Descricao: Pedido de 10 produtos | Prioridade: 2
```

### 3. Atender pedido (opção 2)

```
Escolha: 2

Pedido atendido:
ID: 104
Descricao: Pedido urgente
Prioridade: 8

Pedidos restantes:
Pedidos:
ID: 102 | Descricao: Pedido de 5 produtos | Prioridade: 5
ID: 101 | Descricao: Pedido de 10 produtos | Prioridade: 2
ID: 103 | Descricao: Pedido de 20 produtos | Prioridade: 3
```

### 4. Exibir quantidade de pedidos (opção 4)

```
Escolha: 4

Quantidade de pedidos aguardando: 3
```

### 5. Construir heap a partir de um conjunto inicial (opção 5)

Usando o exemplo de pedidos do próprio enunciado (A=2, B=5, C=3, D=8, E=1):

```
Escolha: 5

Quantos pedidos deseja informar para o conjunto inicial? 5

-- Pedido 1 de 5 --
ID: 1
Descricao: Pedido A
Prioridade: 2

-- Pedido 2 de 5 --
ID: 2
Descricao: Pedido B
Prioridade: 5

-- Pedido 3 de 5 --
ID: 3
Descricao: Pedido C
Prioridade: 3

-- Pedido 4 de 5 --
ID: 4
Descricao: Pedido D
Prioridade: 8

-- Pedido 5 de 5 --
ID: 5
Descricao: Pedido E
Prioridade: 1

Heap construido com sucesso a partir de 5 pedidos!
Pedidos:
ID: 4 | Descricao: Pedido D | Prioridade: 8
ID: 2 | Descricao: Pedido B | Prioridade: 5
ID: 3 | Descricao: Pedido C | Prioridade: 3
ID: 1 | Descricao: Pedido A | Prioridade: 2
ID: 5 | Descricao: Pedido E | Prioridade: 1
```

O resultado bate exatamente com a representação do enunciado: `[8, 5, 3, 2, 1]`.

### 6. Opção inválida / entrada inválida

```
Escolha: 99

Opcao invalida.
```

```
Escolha: abc
Entrada invalida.
```

### 7. Sair (opção 6)

```
Escolha: 6

Encerrando o sistema.
```

---

## Conjunto de testes realizados

Todos os testes abaixo foram executados de fato (via automação de entrada
padrão, `./sistema_pedidos < entrada_teste.txt`), simulando exatamente a
sequência de opções e valores que um usuário digitaria no menu.

| # | Cenário testado | Entrada / ação | Resultado obtido | Resultado esperado | Status |
|---|---|---|---|---|---|
| 1 | Exemplo do enunciado | Cadastrar pedidos 101(2), 102(5), 103(3), 104(8); exibir | Raiz = ID 104 (prioridade 8), seguido de 102(5), 103(3), 101(2) | Igual à representação do enunciado | ✅ |
| 2 | Atendimento de pedido | Atender após o cadastro acima | Remove ID 104 (prioridade 8); heap reorganizado com 102(5) na raiz | Sempre atende o de maior prioridade | ✅ |
| 3 | Construir heap a partir de conjunto inicial | Opção 5 com os 5 pedidos do enunciado (A=2, B=5, C=3, D=8, E=1) | `[8, 5, 3, 2, 1]` (IDs 4,2,3,1,5) | Igual à representação do enunciado | ✅ |
| 4 | Cadastrar após construção | Após construir com 5 pedidos, cadastrar um 6º com prioridade 9 (maior que todas) | Novo pedido sobe até a raiz via sift-up | Heap permanece consistente ao combinar `construir` + `inserir` | ✅ |
| 5 | Atender até esvaziar após construção | Atender repetidamente os 6 pedidos (9, 8, 5, 3, 2, 1) até o heap ficar vazio | Pedidos atendidos exatamente nessa ordem; heap vazio ao final | Sempre atende o de maior prioridade; encerra sem erro ao esvaziar | ✅ |
| 6 | Atender com heap vazio | Opção 2 sem nenhum pedido cadastrado | `"Nao ha pedidos para atender."`, sem travar o programa | Tratamento de erro, sem crash | ✅ |
| 7 | Exibir com heap vazio | Opção 3 sem nenhum pedido cadastrado | `"Nenhum pedido cadastrado."` | Mensagem informativa, sem acesso a vetor vazio | ✅ |
| 8 | Opção de menu inválida | Digitar `99` | `"Opcao invalida."`, retorna ao menu | Mensagem de erro, sem travar | ✅ |
| 9 | Entrada não numérica no menu | Digitar `abc` | `"Entrada invalida."`, retorna ao menu | Tratamento de erro de `scanf`, sem loop infinito | ✅ |
| 10 | Quantidade inválida em "Construir" | Opção 5, informar `0` pedidos | `"Quantidade invalida."`, retorna ao menu | Rejeita `n <= 0` sem crash | ✅ |
| 11 | Redimensionamento automático | Cadastrar 15 pedidos (capacidade inicial é 10) com prioridades variadas | Heap cresce automaticamente para capacidade 20; 15 pedidos armazenados; raiz com a maior prioridade (20) | Nenhuma perda de dados; `realloc` dobra a capacidade quando necessário | ✅ |
| 12 | Propriedade de Max-Heap após várias inserções | Os 15 pedidos do teste 11, verificados por script externo (todo pai ≥ filhos) | Propriedade respeitada em 100% dos nós do vetor | Max-Heap válido em qualquer ponto após `inserir` | ✅ |

### Como os testes foram executados

- **Testes 1–11:** automatizados via redirecionamento de entrada padrão
(`./sistema_pedidos < entrada_teste.txt`), simulando a sequência exata de
opções e valores digitados no menu.
- **Teste 12:** a saída bruta do vetor (opção 3) foi conferida
externamente por um script que percorre cada índice `i` e valida
`dados[i] >= dados[esquerdo(i)]` e `dados[i] >= dados[direito(i)]`.

## Resultados dos testes

Todos os 12 cenários testados passaram sem exceção — nenhum crash, nenhuma
violação da propriedade de Max-Heap, e todos os pedidos foram sempre
atendidos na ordem correta de prioridade (maior primeiro).

O programa foi compilado com `-Wall -Wextra -std=c99` em todas as versões
testadas, sem nenhum warning gerado.