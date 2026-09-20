# Torre de Hanói — Pilha Dinâmica em C

Programa em C (`hanoi.c`) que implementa o jogo Torre de Hanói usando
**pilhas dinâmicas** (nós encadeados alocados com `malloc`), sem uso
de estruturas prontas da linguagem (nada de arrays, `Stack` etc. para
armazenar os discos). Cada uma das três torres é uma pilha própria.

## Requisitos

- GCC (ou outro compilador C compatível com C11)
- Nenhuma biblioteca externa além da padrão (`stdio.h`, `stdlib.h`)

## Compilação

```bash
gcc -Wall -Wextra -std=c11 -o torre_hanoi torre_hanoi.c
```

## Execução

```bash
./torre_hanoi
```

O programa não tem um menu numerado como em outros exercícios — ele
pede diretamente a torre de origem e a torre de destino a cada
jogada, e trata `0` e `-1` como comandos especiais:

```
Torre de origem (1-3) | 0 = reiniciar | -1 = sair:
Torre de destino (1-3):
```

### Observação sobre as operações da pilha

`inicializar_pilha`, `empilhar`, `desempilhar`, `topo` e `imprimir`
são as **operações da estrutura de dados** exigidas pelo enunciado.
`topo` é chamada duas vezes a cada jogada (para espiar o disco de origem e o de destino
sem removê-los) antes de qualquer `desempilhar`/`empilhar` ser
executado — é essa checagem que impede os movimentos inválidos.

---

## Exemplos de execução

### 1. Estado inicial

```
Torre 1 (topo -> base): [1] [2] [3] [4]
Torre 2 (topo -> base): vazia
Torre 3 (topo -> base): vazia
-------------------------------------------
Movimentos realizados: 0
```

### 2. Movimento válido (opção 1 -> 2)

```
Torre de origem (1-3) | 0 = reiniciar | -1 = sair: 1
Torre de destino (1-3): 2
Movimento realizado: Torre 1 -> Torre 2
```

### 3. Movimento inválido — torre de origem vazia

```
Torre de origem (1-3) | 0 = reiniciar | -1 = sair: 2
Torre de destino (1-3): 3
Movimento invalido: a torre de origem esta vazia.
```

### 4. Movimento inválido — disco maior sobre disco menor

```
Torre de origem (1-3) | 0 = reiniciar | -1 = sair: 1
Torre de destino (1-3): 2
Movimento invalido: nao e possivel colocar o disco 2 sobre o disco 1.
```

### 5. Vitória

```
Torre 1 (topo -> base): vazia
Torre 2 (topo -> base): vazia
Torre 3 (topo -> base): [1] [2] [3] [4]
-------------------------------------------

*** PARABENS! Voce venceu em 15 movimentos! ***

Jogar novamente? (1 = Sim / 0 = Nao):
```

### Entrada inválida

```
Torre de origem (1-3) | 0 = reiniciar | -1 = sair: abc
Entrada invalida.
```

---

## Conjunto de testes realizados

Todos os testes abaixo foram executados de fato (via redirecionamento
de entrada padrão, `./hanoi < entrada_teste.txt`), simulando a
sequência exata de jogadas que um jogador digitaria.

| # | Cenário testado | Entrada / ação | Resultado obtido | Resultado esperado | Status |
|---|---|---|---|---|---|
| 1 | Estado inicial | Início de uma nova partida | Torre 1 = `[1][2][3][4]`, Torres 2 e 3 vazias | Maior disco na base, menor no topo, conforme regra do enunciado | ✅ |
| 2 | Movimento válido | Origem `1`, destino `2` | `"Movimento realizado: Torre 1 -> Torre 2"`, disco 1 passa ao topo da Torre 2 | Disco do topo (menor) se move livremente para torre vazia | ✅ |
| 3 | Torre de origem vazia | Origem `2` (vazia), destino `3` | `"Movimento invalido: a torre de origem esta vazia."` | `topo()` retorna 0 para pilha vazia, movimento deve ser bloqueado | ✅ |
| 4 | Origem e destino iguais | Origem `1`, destino `1` | `"Movimento invalido: origem e destino sao a mesma torre."` | Regra de negócio bloqueia antes de chamar `mover_disco` | ✅ |
| 5 | Disco maior sobre disco menor | Torre 2 com disco `1` no topo; tentativa de mover disco `2` da Torre 1 para a Torre 2 | `"Movimento invalido: nao e possivel colocar o disco 2 sobre o disco 1."` | Comparação `discoDestino < discoOrigem` deve rejeitar o movimento | ✅ |
| 6 | Contador de movimentos | 1 movimento válido + 3 tentativas inválidas | `Movimentos realizados: 1` | Contador só incrementa quando `mover_disco` retorna sucesso | ✅ |
| 7 | Partida completa (solução ótima) | Sequência ótima recursiva para 4 discos (origem 1, auxiliar 2, destino 3) | `"PARABENS! Voce venceu em 15 movimentos!"`, Torre 3 = `[1][2][3][4]` | Número mínimo de movimentos para *n* discos é `2ⁿ − 1`; para `n=4`, `2⁴−1 = 15` | ✅ |
| 8 | Entrada não numérica | Digitar `abc` no prompt de origem | `"Entrada invalida."`, jogo continua sem travar nem repetir a jogada anterior | `scanf` falha, buffer é limpo (`limpar_buffer`) e o loop pede a jogada novamente | ✅ |
| 9 | Reiniciar partida (opção `0`) | Um movimento válido, depois `0` | Pilhas antigas liberadas (`liberar_torres`); nova partida mostra `[1][2][3][4]` na Torre 1 e contador zerado | Estado deve voltar ao inicial, sem vazamento dos nós da partida anterior | ✅ |
| 10 | Sair no meio do jogo (opção `-1`) | Um movimento válido, depois `-1` | Programa encerra imediatamente com `"Obrigado por jogar!"`, sem pedir "jogar novamente" | `-1` deve interromper a partida a qualquer momento, mesmo sem vitória | ✅ |

### Como os testes foram executados

Cada cenário foi reproduzido enviando ao programa, via `stdin`, a
sequência exata de números que um jogador digitaria (torre de
origem, torre de destino, e comandos `0`/`-1` quando aplicável). O
teste 7 usa a sequência ótima gerada pela recursão clássica do Hanói
(`mover(n-1, origem, aux, destino); mover 1 disco; mover(n-1, aux, origem, destino)`),
o que também serve como verificação indireta de que a pilha nunca
deixa um movimento inválido passar mesmo em uma sequência longa.

### Compilação sem warnings

O programa foi compilado com `-Wall -Wextra -std=c11` sem nenhum
warning gerado.