# Jogo Genius em C (Fila Dinâmica Encadeada)

Programa em C (`genius.c`) que implementa o jogo de memória **Genius**. A sequência de cores da partida é
armazenada em uma **fila dinâmica** (`struct No` + `struct Fila`),
implementada com nós encadeados e ponteiros, sem uso de nenhuma
estrutura pronta de biblioteca (nada de `array`, `list`, `deque` etc.
para o armazenamento principal).

## Requisitos

- GCC (ou outro compilador C compatível com C11)
- Nenhuma biblioteca externa além da biblioteca padrão do C
  (`stdio.h`, `stdlib.h`, `time.h`)

## Compilação

```
gcc -Wall -Wextra -std=c11 -o genius genius.c
```

## Execução

```
./genius
```

O programa exibe um menu e aguarda a opção do usuário via teclado,
repetindo até que `2` (Sair) seja escolhido.

```
===== JOGO GENIUS =====
1 - Jogar (nova partida)
2 - Sair
Escolha:
```

Ao escolher `1`, uma nova partida começa: a cada rodada uma cor é
sorteada e **adicionada ao fim da fila** (`enfileirar`); só a cor
nova da rodada é mostrada na tela, e o jogador deve digitar, na
ordem, a sequência completa desde a rodada 1 (de cabeça).

### Observação sobre a operação `frente`

A operação `frente` faz parte das **operações da estrutura de dados**
exigidas pelo enunciado e está implementada e testada isoladamente
(veja a seção de testes). Ela não aparece como uma ação separada no
menu porque, no fluxo do jogo, `frente` é usada **internamente** pela
conferência da sequência (`verificar_sequencia`) — o jogo usa a
estrutura, mas não precisa expor essa consulta diretamente ao
jogador.

---

## Descrição das operações da fila

| Operação | Assinatura | O que faz |
| --- | --- | --- |
| `inicializar_fila` | `void inicializar_fila(Fila *fila)` | Zera `inicio`, `fim` e `quantidade`. Deve ser chamada antes de qualquer outro uso da fila. |
| `enfileirar` | `void enfileirar(Fila *fila, Cor cor)` | Cria um novo nó e o insere **no fim** da fila, religando o ponteiro `proximo` do antigo último nó (ou `inicio`/`fim`, se a fila estava vazia). |
| `desenfileirar` | `Cor desenfileirar(Fila *fila)` | Remove o nó do **início** da fila, libera sua memória (`free`) e retorna a cor removida. Atualiza `fim` para `NULL` se a fila ficar vazia. |
| `frente` | `Cor frente(Fila *fila)` | Retorna a cor do início da fila **sem removê-la** (consulta). |
| `imprimir` | `void imprimir(Fila *fila)` | Percorre a fila do início ao fim usando um ponteiro auxiliar (`atual->proximo`), **sem remover nenhum nó**, imprimindo as cores separadas por `->`. |

No jogo, a conferência da resposta do jogador usa as quatro
operações de manipulação em conjunto: para cada cor da sequência, o
programa consulta com `frente`, remove com `desenfileirar` e devolve
imediatamente ao fim com `enfileirar`. Depois de percorrer a fila
inteira uma única vez, ela volta a ficar exatamente como estava —
usando somente as operações permitidas, sem acessar o meio da
estrutura por fora.

---

## Exemplos de execução

### 1. Menu principal

```
===== JOGO GENIUS =====
1 - Jogar (nova partida)
2 - Sair
Escolha:
```

### 2. Iniciar partida e progredir corretamente (opção 1)

```
Escolha: 1

=== Nova partida iniciada! ===

--- Rodada 1 ---
Sequencia: AZUL
Repita a sequencia:
Cor (V=Verde, R=Vermelho, A=Azul, M=Amarelo): A
Correto! Pontuacao atual: 1

--- Rodada 2 ---
Sequencia: VERDE
Repita a sequencia:
Cor (V=Verde, R=Vermelho, A=Azul, M=Amarelo): A
Cor (V=Verde, R=Vermelho, A=Azul, M=Amarelo): V
Correto! Pontuacao atual: 2

--- Rodada 3 ---
Sequencia: VERMELHO
Repita a sequencia:
Cor (V=Verde, R=Vermelho, A=Azul, M=Amarelo): A
Cor (V=Verde, R=Vermelho, A=Azul, M=Amarelo): V
Cor (V=Verde, R=Vermelho, A=Azul, M=Amarelo): R
Correto! Pontuacao atual: 3
```

### 3. Entrada de cor inválida

```
--- Rodada 1 ---
Sequencia: AZUL
Repita a sequencia:
Cor (V=Verde, R=Vermelho, A=Azul, M=Amarelo): X
Cor invalida. Tente novamente.
Cor (V=Verde, R=Vermelho, A=Azul, M=Amarelo): A
Correto! Pontuacao atual: 1
```

### 4. Sequência incorreta → fim de jogo

```
--- Rodada 4 ---
Sequencia: VERMELHO
Repita a sequencia:
Cor (V=Verde, R=Vermelho, A=Azul, M=Amarelo): A
Cor (V=Verde, R=Vermelho, A=Azul, M=Amarelo): V
Cor (V=Verde, R=Vermelho, A=Azul, M=Amarelo): R
Cor (V=Verde, R=Vermelho, A=Azul, M=Amarelo): V

Sequencia incorreta! Fim de jogo.
A sequencia correta era: AZUL -> VERDE -> VERMELHO -> VERMELHO
Pontuacao final: 3
```

### 5. Reiniciar uma partida (voltar ao menu e escolher `1` de novo)

```
===== JOGO GENIUS =====
1 - Jogar (nova partida)
2 - Sair
Escolha: 1

=== Nova partida iniciada! ===

--- Rodada 1 ---
Sequencia: VERDE
Repita a sequencia:
Cor (V=Verde, R=Vermelho, A=Azul, M=Amarelo): A

Sequencia incorreta! Fim de jogo.
A sequencia correta era: VERDE
Pontuacao final: 0
```

> A pontuação e a fila da partida anterior não têm nenhum efeito na
> nova partida: `jogar_partida` cria e inicializa uma fila nova a
> cada chamada, e a pontuação começa sempre em `0`.

### 6. Opção de menu inválida

```
Escolha: 99
Opcao invalida.
```

### 7. Encerrar o jogo (opção 2)

```
Escolha: 2
Encerrando o jogo. Ate a proxima!
```

---

## Conjunto de testes realizados

Todos os testes abaixo foram executados de fato (via automação de
entrada padrão, `./genius < entrada_teste.txt`), e não apenas
imaginados. Para tornar os resultados **reproduzíveis** nesta
documentação, a semente do gerador aleatório foi temporariamente
fixada (`srand(42)`) durante os testes automatizados — o programa
entregue usa `srand(time(NULL))` normalmente, para gerar partidas
diferentes a cada execução real.

| # | Cenário testado | Entrada / ação | Resultado obtido | Resultado esperado | Status |
| --- | --- | --- | --- | --- | --- |
| 1 | Iniciar partida e primeira rodada | Opção `1` | Fila recebe 1 cor (`AZUL`), pontuação em 0, mensagem "Nova partida iniciada!" | Fila com 1 elemento, rodada 1 exibida | ✅ |
| 2 | Progressão de rodadas com resposta correta | Respostas corretas nas rodadas 1 a 3 | Pontuação sobe 1 → 2 → 3, fila cresce para 3 elementos, ordem preservada (`AZUL -> VERDE -> VERMELHO`) | Pontuação incrementa a cada acerto, sequência mantém a ordem de inserção | ✅ |
| 3 | Exibição da cor nova por rodada | Rodada 2 em diante | Mostra apenas a cor recém-adicionada (ex.: `Sequencia: VERDE`), não a fila inteira | Exibir só a cor nova da rodada | ✅ |
| 4 | Entrada de cor inválida | Digitar `X` no lugar de uma cor | `"Cor invalida. Tente novamente."`, volta a pedir a cor, sem avançar de rodada nem encerrar o jogo | Mensagem de erro e nova tentativa | ✅ |
| 5 | Resposta errada no meio da sequência | Rodada 4 respondida como `A V R V` (esperado `A V R R`) | `"Sequencia incorreta! Fim de jogo."`, mostra a sequência correta completa e a pontuação final (`3`) | Encerramento imediato da partida com pontuação e sequência corretas exibidas | ✅ |
| 6 | Reiniciar partida | Escolher `1` novamente após "Fim de jogo" | Nova fila vazia, pontuação volta para `0`, nova sequência começa do zero | Estado da partida anterior não deve vazar para a nova | ✅ |
| 7 | Opção de menu inválida (numérica) | Digitar `99` no menu | `"Opcao invalida."`, retorna ao menu sem travar | Mensagem de erro e retorno ao menu | ✅ |
| 8 | Entrada não numérica no menu | Digitar letras no lugar do número da opção | `scanf` falha, buffer é limpo, menu é reexibido sem travar nem mensagem duplicada | Nenhum crash, nenhum loop infinito | ✅ |
| 9 | Encerrar o jogo | Digitar `2` no menu | `"Encerrando o jogo. Ate a proxima!"`, programa termina (`exit code 0`) | Encerramento limpo do laço principal | ✅ |
| 10 | Entrada esgota no meio de uma leitura de cor (EOF) | Redirecionar entrada que termina antes do jogador responder | `"Entrada encerrada. Fechando o jogo."`, programa termina com `exit(0)` em vez de travar | Encerramento controlado, sem loop infinito | ✅ |
| 11 | `inicializar_fila` (teste unitário isolado) | Chamar `inicializar_fila` numa `Fila` recém-declarada | `quantidade == 0`, `inicio == NULL`, `fim == NULL` | Fila começa vazia | ✅ |
| 12 | `enfileirar` (teste unitário isolado) | Enfileirar `AZUL`, `VERDE`, `VERMELHO` | `quantidade == 3`, ordem impressa `AZUL -> VERDE -> VERMELHO` | Inserção sempre no fim, mantendo a ordem | ✅ |
| 13 | `frente` (teste unitário isolado) | Chamar `frente` na fila acima | Retorna `AZUL` e **não** altera `quantidade` | Consulta não deve remover elemento | ✅ |
| 14 | `desenfileirar` (teste unitário isolado) | Chamar `desenfileirar` na fila acima | Retorna `AZUL` (FIFO), `quantidade == 2`, novo `frente` passa a ser `VERDE` | Remoção sempre pelo início, respeitando FIFO | ✅ |
| 15 | Fila esvaziar corretamente | Desenfileirar todos os elementos restantes | `quantidade == 0`, `inicio == NULL` **e** `fim == NULL` | `fim` precisa ser resetado junto com `inicio` ao esvaziar, senão fica um ponteiro pendurado | ✅ |
| 16 | Vazamento de memória / uso indevido de memória | Compilação com `-fsanitize=address,leak`, execução do roteiro completo (partida, erro, reinício, saída) | Nenhum erro reportado pelo AddressSanitizer/LeakSanitizer | Todo `malloc` em `enfileirar` deve ter um `free` correspondente em `desenfileirar`/`liberar_fila` | ✅ |
| 17 | Compilação sem warnings | `gcc -Wall -Wextra -std=c11 -o genius genius.c` | Nenhum warning gerado | Código limpo, sem warnings de `-Wall -Wextra` | ✅ |

### Como os testes foram executados

- **Testes 1–10:** automatizados via redirecionamento de entrada
  padrão (`./genius < entrada_teste.txt`), simulando exatamente a
  sequência de opções e cores que um jogador digitaria no menu e nas
  rodadas.
- **Testes 11–15:** como o enunciado pede que as operações da fila
  sejam testadas como estrutura de dados (e não só "por tabela" pelo
  comportamento do jogo), foram testadas isoladamente em um `main()`
  de verificação separado (`teste_fila.c`), que chama
  `inicializar_fila`, `enfileirar`, `frente` e `desenfileirar`
  diretamente e compara o resultado (`quantidade`, conteúdo da fila,
  cor retornada) com o valor esperado, imprimindo `[OK]`/`[FALHOU]`
  para cada verificação.
- **Teste 16:** o mesmo roteiro de entrada usado nos testes 1–10 foi
  executado numa build compilada com `-fsanitize=address,leak`, para
  garantir que todo nó alocado com `malloc` em `enfileirar` é
  liberado com `free` em `desenfileirar` (ou em `liberar_fila`, ao
  final da partida), sem vazamento nem acesso inválido à memória.
- **Teste 17:** o programa foi compilado com `-Wall -Wextra -std=c11`
  em todas as versões testadas, sem nenhum warning gerado.